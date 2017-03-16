#ifndef __MINIBUS__DRIVER__PROGRAM_BUILDER__H__
#define __MINIBUS__DRIVER__PROGRAM_BUILDER__H__

#include <cassert>
#include <functional>
#include <map>
#include <set>
#include <vector>

#include "minibus/widgets/widget.h"

using namespace std;
using namespace std::placeholders;

namespace minibus {

typedef function<void(Widget*, Widget*, Widget*, function<bool()>)> FAddLogic;

class ProgramBuilder {
public:
	ProgramBuilder(FAddLogic add_logic, Widget* start)
			: _add_logic(add_logic), _start(start) {
		set_last(nullptr);
		then(start);
	}

	virtual ~ProgramBuilder() {}

	virtual ProgramBuilder* done() {
		return then(nullptr);
	}

	virtual ProgramBuilder* then(Widget* widget) {
		return when(widget, nullptr, bind(&yes));
	}

	virtual ProgramBuilder* loop(Widget* widget_next,
				     function<bool()> determine) {
		prepare();
		return when_impl(_last, widget_next, determine);
	}

	virtual ProgramBuilder* when(Widget* widget_yes,
				     Widget* widget_no,
				     function<bool()> determine) {
		prepare();
		return when_impl(widget_yes, widget_no, determine);
	}

	virtual ProgramBuilder* when_impl(Widget* widget_yes,
					  Widget* widget_no,
					  function<bool()> determine) {
		cout << "state when " << widget_yes << " " << widget_no << "\r\n";
		_add_logic(_last, widget_yes, widget_no, determine);
		set_last(widget_yes);
		if (widget_no) _stack.push_back(widget_no);
		return this;
	}

	virtual Widget* finish() {
		cout << "finish " << _stack.size() << "\r\n";
		then(nullptr);
		cout << "whenfinish " << _stack.size() << "\r\n";

		assert(_stack.empty());
		Widget* retval = _start;
		delete this;
		return retval;
	}

protected:
	virtual void prepare() {
		cout << "prep: " << _last << " " << _stack.empty() << "\r\n";

		while (!_last && !_stack.empty()) {
			cout << "last: " << _stack.back() << "\r\n";
			set_last(_stack.back());
			_stack.pop_back();
		}
	}

	virtual void set_last(Widget* last) {
		cout << "state set last from " << _last << " -> " << last
		     << " seen ? " << _seen.count(last) << " " << _seen.size()
		     << "\r\n";
		_seen.insert(_last);
		if (_seen.count(last)) _last = nullptr;
		else {
			cout << "now seen " << _last << "\r\n";
			_last = last;
		}
		cout << "set last " << last << " -> " << _last << "\r\n";
	}

	static bool yes() { return true; }
	static bool no() { return false; }

	FAddLogic _add_logic;
	Widget* _start;
	Widget* _last;
	vector<Widget*> _stack;
	set<Widget*> _seen;
};

}  // namespace minibus

#endif  // __MINIBUS__DRIVER__PROGRAM_BUILDER__H__
