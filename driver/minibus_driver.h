#ifndef __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
#define __MINIBUS__DRIVER__MINIBUS_DRIVER__H__

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <thread>

#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"

using namespace std;
using namespace std::placeholders;

namespace minibus {

typedef function<int(int)> FNextState;

class MinibusDriver {
public:
	MinibusDriver() : MinibusDriver(stdscr) {
		initscr();
		start_color();
		keypad(stdscr, true);
		noecho();
		cbreak();
	}
	MinibusDriver(WINDOW* window)
		: _window(window), _cur_state(0) {}

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
		Widget* widget = get_focus();
		assert(widget);
		widget->render(_window);
	}

	virtual void keypress(const Key& key) {
		Widget* widget = get_focus();
		assert(widget);
		if (widget->keypress(key)) {
			clear();
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

			/* TODO: do a preemptable version */
			Key key(getch());

			keypress(key);
		}
	}

	WINDOW* _window;
	bool _stop;
	unique_ptr<thread> _thread;
	int _cur_state;
	map<int, unique_ptr<Widget>> _state_to_widget;
	map<int, FNextState> _state_to_callback;
};

}  // namespace minibus

#endif  // __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
