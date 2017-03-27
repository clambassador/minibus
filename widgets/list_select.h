#ifndef __MINIBUS__WIDGET__LIST_SELECT__H__
#define __MINIBUS__WIDGET__LIST_SELECT__H__

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

class ListSelect : public YNav, public Base {
public:
	ListSelect(const string& name, const vector<string>& items)
	    : YNav(items.size()), Base(name), _items(items) {}

	virtual int render(IDisplay* win) {
		for (size_t i = 0; i < _items.size(); ++i) {
			win->write(i, 0, _items[i],
				   (_ycur == i) ?
					IDisplay::BLACK_YELLOW :
					IDisplay::YELLOW_BLACK);
		}
		return 0;
	}

	virtual int open() {
		// TODO: clear promise
		_ycur = 0;
		return 0;
	}

	virtual void focus() {}

	virtual int close() {
	//	_selected_pos.set_value(_ycur);
	//	_selected_value.set_value(_items.at(_ycur));
		return 0;
	}

	virtual int keypress(const Key& key) {
		return YNav::keypress(key);
	}

	virtual int get_selected() const {
		return _ycur;
	}

	virtual string get_selected_item() const {
		return _items[_ycur];
	}

	virtual future<int> get_selected_pos() {
		return _selected_pos.get_future();
	}

	virtual future<string> get_selected_value() {
		return _selected_value.get_future();
	}

protected:
	vector<string> _items;
	promise<int> _selected_pos;
	promise<string> _selected_value;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__LIST_SELECT__H__

