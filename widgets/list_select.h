#ifndef __MINIBUS__WIDGET__LIST_SELECT__H__
#define __MINIBUS__WIDGET__LIST_SELECT__H__

#include <functional>
#include <string>
#include <vector>

#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"
#include "minibus/widgets/ynav.h"

using namespace std;

namespace minibus {

typedef function<int(size_t)> SelectCB;

class ListSelect : public YNav, public Widget {
public:
	ListSelect(const vector<string>& items, SelectCB cb)
	    : YNav(items.size()), _items(items), _cb(cb) {}

	virtual int render(WINDOW* win) {
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_BLACK, COLOR_GREEN);
		for (size_t i = 0; i < _items.size(); ++i) {
			if (_ycur == i) {
				// todo: use a destructor to attroff
				attron(COLOR_PAIR(2));
			} else {
				attron(COLOR_PAIR(1));
			}
			mvwprintw(win, i, 0, _items[i].c_str());
			if (_ycur == i) {
				// todo: use a destructor to attroff
				attroff(COLOR_PAIR(2));
			} else {
				attroff(COLOR_PAIR(1));
			}
		}
		return 0;
	}

	virtual int open() {
		return 0;
	}

	virtual int close() {
		_cb(_ycur);
		return 0;
	}

	virtual int keypress(const Key& key) {
		return YNav::keypress(key); }

protected:
	vector<string> _items;
	SelectCB _cb;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__LIST_SELECT__H__

