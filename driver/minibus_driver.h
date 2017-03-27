#ifndef __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
#define __MINIBUS__DRIVER__MINIBUS_DRIVER__H__

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <ncurses.h>
#include <thread>
#include <unistd.h>

#include "minibus/driver/program_builder.h"
#include "minibus/io/getch_input.h"
#include "minibus/io/i_display.h"
#include "minibus/io/i_input.h"
#include "minibus/io/screen_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/close_on_key.h"
#include "minibus/widgets/list_select.h"
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
		: _display(display), _input(input), _cur_state(0),
		  _cur_state_build(0), _cur(nullptr) {}

	virtual ~MinibusDriver() {
		stop();
		_input->terminate();
		_thread->join();
		endwin();
	}

	virtual void start() {
		assert(_cur || _programs.count("main"));
		if (!_cur) _cur = _programs["main"].get();
		start(_cur);
	}

	virtual void start(Widget* first) {
		_cur = first;
		open();
		_stop = false;
		_thread.reset(new thread(&MinibusDriver::run, this));
	}

	virtual void wait() {
		while (!_stop) sleep(1);
	}

	virtual void stop() {
		_stop = true;
	}

	virtual ProgramBuilder* build_program(const string& name, Widget* start) {
		_programs[name].reset(start);
		return new ProgramBuilder(bind(&MinibusDriver::add_logic, this,
					       _1, _2, _3, _4),
					  start);
	}

	virtual void use_menu() {
		vector<string> items;
		for (auto &x : _programs) {
			items.push_back(x.first);
		}
		items.push_back("Exit");
		_menu = new ListSelect("menu", items);
		_menu_item.reset(new CloseOnKey(_menu));
		_cur = _menu_item.get();
	}

protected:
	virtual bool state(Widget* main, Widget* sub) {
		return main->name() == sub->name();
	}

	virtual void add_logic(Widget* source, Widget* next,
			       Widget* jump, function<bool()> which) {
		_state_logic[source][true] = next;
		_state_logic[source][false] = jump;
		_state_choice[source] = which;
	}

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
		after_keypress(key, _cur);
		if (closed == -1) {
			_display->clear();

			Widget* old = _cur;
			auto_update_state(widget->close());
			if (finished()) _stop = true;

			after_close(key, old);
			widget_switch(old, _cur);
			open();
			after_open(_cur);
		}
	}

	virtual void open() {
		if (_cur) {
			_cur->open();
			after_open(_cur);
		}
	}

	virtual void auto_update_state(int param) {
		if (!_cur) return;
		if (_cur == _menu_item.get()) {
			string program = _menu->get_selected_item();
			if (program == "Exit") _cur = nullptr;
			else _cur = _programs[program].get();
			return;
		}
		if (_state_logic.count(_cur)) {
			_cur = _state_logic[_cur][_state_choice[_cur]()];
			if (!_cur) _cur = _menu_item.get();
		} else {
			update_state(param);
		}
	}

	virtual void update_state(int param) { _cur = nullptr; }
	virtual int update_state(int cur_state, int param) {
		return cur_state + 1;
	}

	virtual bool finished() {
		return !_cur;
	}

	virtual Widget* get_focus() {
		return _cur;
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

	virtual void after_keypress(const Key&, Widget*) {}
	virtual void after_close(const Key&, Widget*) {}
	virtual void widget_switch(Widget*, Widget*) {}
	virtual void after_open(Widget*) {}

	IDisplay* _display;
	IInput* _input;
	bool _stop;
	unique_ptr<thread> _thread;
	int _cur_state;
	int _cur_state_build;
	map<string, unique_ptr<Widget>> _programs;
	map<Widget*, map<bool, Widget*>> _state_logic;
	map<Widget*, function<bool()>> _state_choice;
	unique_ptr<Widget> _menu_item;
	Widget* _cur;
	ListSelect* _menu;
};

}  // namespace minibus

#endif  // __MINIBUS__DRIVER__MINIBUS_DRIVER__H__
