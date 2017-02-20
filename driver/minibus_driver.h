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
		initscr();
		start_color();
		keypad(stdscr, true);
		noecho();
		cbreak();
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
		if (_cur_state_build) {
			assert(_state_to_callback.count(_cur_state_build - 1));
			_state_to_callback[_cur_state_build - 1]
			    = bind(next, _cur_state_build - 1, _1);
		}
		assert(!_state_to_widget.count(_cur_state_build));
		assert(!_state_to_callback.count(_cur_state_build));
		_state_to_widget[_cur_state_build].reset(widget);
		_state_to_callback[_cur_state_build] = bind(terminate, _1);
		++_cur_state_build;
	}

	virtual void loop_state_widget(Widget* widget) {
		if (_cur_state_build) {
			assert(_state_to_callback.count(_cur_state_build - 1));
			_state_to_callback[_cur_state_build - 1]
			    = bind(next, _cur_state_build - 1, _1);
		}
		assert(!_state_to_widget.count(_cur_state_build));
		assert(!_state_to_callback.count(_cur_state_build));
		_state_to_widget[_cur_state_build].reset(widget);
		_state_to_callback[_cur_state_build]
		    = bind(loop, _cur_state_build, _1);
		++_cur_state_build;
	}

	virtual void set_state_widget(int state, Widget* widget) {
		_state_to_widget[state].reset(widget);
		_state_to_callback[state] = bind(next, state, _1);
	}

	virtual void set_state_widget(int state, Widget* widget,
				      const FNextState& next_state) {
		_state_to_widget[state].reset(widget);
		_state_to_callback[state] = next_state;
	}

	static int next(int state, int parm) {
		return state + 1;
	}

	static int loop(int state, int parm) {
		return state;
	}

	static int terminate(int parm) {
		return -1;
	}

	static int restart(int parm) {
		return 0;
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
		bool closed = widget->keypress(key);
		after_keypress(key, _cur_state);
		if (closed) {
			_display->clear();
			int old_state = _cur_state;
			update_state(widget->close());
			after_close(key, old_state);
		}
	}

	virtual void update_state(int param) {
		_cur_state = _state_to_callback[_cur_state](param);
		if (finished()) _stop = true;
		else assert(_state_to_widget.count(_cur_state));
	}

	virtual bool finished() {
		return _cur_state == -1;
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
	map<int, FNextState> _state_to_callback;
};

}  // namespace minibus

#endif  // __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
