#ifndef __MINIBUS__WIDGET__VERTICAL_LIST__H__
#define __MINIBUS__WIDGET__VERTICAL_LIST__H__

#include <functional>
#include <future>
#include <string>
#include <vector>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"
#include "minibus/widgets/ynav.h"

using namespace std;

namespace minibus {

class VerticalList : public YNav, public Widget {
public:
	template <typename... ARGS>
	VerticalList(ARGS... args)
			: YNav(0) {
		add_items(args...);
	}

	void add_items() {
		resize(_items.size());
	}

	template <typename... ARGS>
	void add_items(Widget *item, ARGS... items) {
		_items.push_back(nullptr);
		_items.back().reset(item);
		add_items(items...);
	}

	virtual int render(IDisplay* win) {
		for (size_t i = 0; i < _items.size(); ++i) {
			if (i == _ycur) {
				_items[i]->focus();
			}
			_items[i]->render(win);
			if (i == _ycur) {
				win->stay();
			}
			win->vertical();
		}
		return 0;
	}

	virtual int open() {
		for (size_t i = 0; i < _items.size(); ++i) {
			_items[i]->open();
		}
		return 0;
	}

	virtual int close() {
		for (size_t i = 0; i < _items.size(); ++i) {
			_items[i]->close();
		}
		return 0;
	}

	virtual int keypress(const Key& key) {
		if (key.y_navigation()) return YNav::keypress(key);
		return _items[_ycur]->keypress(key);
	}

	virtual void focus() {}

protected:
	vector<unique_ptr<Widget>> _items;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__VERTICAL_LIST__H__

