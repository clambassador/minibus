#ifndef __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
#define __MINIBUS__DRIVER__MINIBUS_DRIVER__H__

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <ncurses.h>
#include <thread>

#include "minibus/io/getch_input.h"
#include "minibus/io/i_display.h"
#include "minibus/io/i_input.h"
#include "minibus/io/screen_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"

using namespace std;
using namespace std::placeholders;

namespace minibus {

typedef function<int(int)> FNextState;

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

	~MinibusDriver() {
		_thread->join();
		endwin();
	}

	virtual void start() {
		_stop = false;
		_thread.reset(new thread(&MinibusDriver::run, this));
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

	static int terminate(int parm) {
		return -1;
	}

	static int restart(int parm) {
		return 0;
	}

protected:
	virtual void render() {
		unique_ptr<RenderFinish> rd(_display->start_render());
		Widget* widget = get_focus();
		assert(widget);
		widget->render(_display);
	}

	virtual void keypress(const Key& key) {
		Widget* widget = get_focus();
		assert(widget);
		if (widget->keypress(key)) {
			_display->clear();
			update_state(widget->close());
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
			keypress(key);
		}
	}

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
