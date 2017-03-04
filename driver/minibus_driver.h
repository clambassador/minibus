#ifndef __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
#define __MINIBUS__DRIVER__MINIBUS_DRIVER__H__

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <ncurses.h>
#include <thread>
#include <unistd.h>

#include "minibus/io/getch_input.h"
#include "minibus/io/i_display.h"
#include "minibus/io/i_input.h"
#include "minibus/io/screen_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"

using namespace std;
using namespace std::placeholders;

namespace minibus {

class MinibusDriver;

typedef function<int(int)> FNextState;
typedef function<MinibusDriver*(IDisplay*, IInput*)> FMinibusDriverConstructor;

class MinibusDriver {
public:
	MinibusDriver() : MinibusDriver(new ScreenDisplay(stdscr),
					new GetchInput()) {
	}

	MinibusDriver(IDisplay* display, IInput* input)
		: _display(display), _input(input), _cur_state(0), _cur_state_build(0) {}

	virtual ~MinibusDriver() {
		stop();
		_input->terminate();
		_thread->join();
		endwin();
	}

	virtual void start() {
		_stop = false;
		_thread.reset(new thread(&MinibusDriver::run, this));
	}

	virtual void wait() {
		while (!_stop) sleep(1);
	}

	virtual void stop() {
		_stop = true;
	}

	virtual void add_state_widget(Widget* widget) {
		assert(!_state_to_widget.count(_cur_state_build));
		_state_to_widget[_cur_state_build].reset(widget);
		++_cur_state_build;
	}

	virtual void set_state_widget(int state, Widget* widget) {
		_state_to_widget[state].reset(widget);
	}

protected:
	virtual void render() {
		unique_ptr<RenderFinish> rd(_display->start_render());
		clear();
		Widget* widget = get_focus();
		assert(widget);
		widget->render(_display);
	}

	virtual void keypress(const Key& key) {
		Widget* widget = get_focus();
		assert(widget);
		int closed = widget->keypress(key);
		after_keypress(key, _cur_state);
		if (closed == -1) {
			_display->clear();

			int old_state = _cur_state;
			_cur_state = update_state(_cur_state, widget->close());
			if (finished()) _stop = true;

			after_close(key, old_state);
		}
	}

	virtual int update_state(int cur_state, int param) {
		return cur_state + 1;
	}

	virtual bool finished() {
		return _state_to_widget.count(_cur_state);
	}

	virtual Widget* get_focus() {
		return _state_to_widget[_cur_state].get();
	}

	virtual void run() {
		while (!_stop) {
			render();
			Key key(_input->get_key());
			if (key.eot()) break;

			keypress(key);
			if (finished()) _stop = true;
		}
	}

	virtual void after_keypress(const Key&, int) {}
	virtual void after_close(const Key&, int) {}

	IDisplay* _display;
	IInput* _input;
	bool _stop;
	unique_ptr<thread> _thread;
	int _cur_state;
	int _cur_state_build;
	map<int, unique_ptr<Widget>> _state_to_widget;
};

}  // namespace minibus

#endif  // __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
