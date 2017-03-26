#ifndef __MINIBUS__WIDGET__HOTKEYS_SELECT__H__
#define __MINIBUS__WIDGET__HOTKEYS_SELECT__H__

#include <functional>
#include <map>
#include <string>
#include <ncurses.h>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/hotkeys.h"
#include "minibus/widgets/widget.h"

using namespace std;

namespace minibus {

class HotkeysSelect : public Hotkeys {
public:
	template <typename... ARGS>
	HotkeysSelect(const string& name, ARGS... args)
			: Hotkeys(name, args...) {
	}

	virtual ~HotkeysSelect() {}

	virtual int keypress(const Key& key) {
		stringstream ss;

		if (_keys.count(key)) {
			toggle(key);
			return 0;
		}
		return 0;
	}

	virtual int render(IDisplay* win) {
		size_t pos = 0;
		size_t i = 0;
		for (auto &x : _keys) {
			stringstream ss;
			ss << "[" << (char) x.first.key() << ": " << x.second << "]  ";
			if (!selected(x.first)) {
				win->write(0, pos, ss.str(), (i++ % 7) + 1);
			} else {
				win->write(0, pos, ss.str(), (i++ % 7) + 8);
			}
			pos += ss.str().length();
		}
		return 0;
	}

	virtual bool selected(const Key& key) const {
		return _selected.count(key);
	}

protected:
	virtual void toggle(const Key& key) {
		if (selected(key)) {
			_selected.erase(key);
		} else {
			_selected.insert(key);
		}
	}

	set<Key> _selected;
};

}  // namespace minibus

#endif  // __MINIBUS__WIDGET__HOTKEYS_SELECT__H__
