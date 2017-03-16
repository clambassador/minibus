#ifndef __MINIBUS__WIDGET__LIST_SELECT_MULTI__H__
#define __MINIBUS__WIDGET__LIST_SELECT_MULTI__H__

#include <functional>
#include <future>
#include <string>
#include <vector>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/base.h"
#include "minibus/widgets/ynav.h"

using namespace std;

namespace minibus {

class ListSelectMulti : public YNav, public Base {
public:
	ListSelectMulti(const string& name, const vector<string>& items)
	    : ListSelectMulti(name, items, 0) {}

	ListSelectMulti(const string& name,
			const vector<string>& items, size_t max_select)
	    : YNav(items.size()), Base(name),
	      _items(items), _max_select(max_select) {}

	virtual int render(IDisplay* win) {
		for (size_t i = 0; i < _items.size(); ++i) {
			string line;
			if (_selected.count(i)) {
				line += "[x] ";
			} else {
				line += "[ ] ";
			}
			win->write(i, 0, line + _items[i],
				   (_ycur == i) ?
					IDisplay::BLACK_YELLOW :
					IDisplay::YELLOW_BLACK);
		}
		return 0;
	}

	virtual int keypress(const Key& key) {
		if (key == ' ') {
			toggle();
			return 1;
		}
		return YNav::keypress(key);
	}

	virtual const set<size_t>& get_selected() const {
		return _selected;
	}

protected:
	virtual void toggle() {
		if (_selected.count(_ycur)) {
			_selected.erase(_ycur);
		} else {
			if (!_max_select || _selected.size() < _max_select) {
				_selected.insert(_ycur);
			}
		}
	}

	vector<string> _items;
	set<size_t> _selected;
	size_t _max_select;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__LIST_SELECT_MULTI__H__

