#ifndef __MINIBUS__WIDGET__HOTKEYS__H__
#define __MINIBUS__WIDGET__HOTKEYS__H__

#include <functional>
#include <map>
#include <string>
#include <ncurses.h>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/base.h"
#include "minibus/widgets/widget.h"

using namespace std;

namespace minibus {

class Hotkeys : public Base {
public:
	template <typename... ARGS>
	Hotkeys(ARGS... args) : Base() {
		add_keys(args...);
	}

	void add_keys() {}

	template <typename... ARGS>
	void add_keys(const string& key, ARGS... args) {
		add_key(_keys.size() + '1', key);
		add_keys(args...);
	}

	virtual ~Hotkeys() {}

	virtual void add_key(Key key, const string& text) {
		_keys[key] = text;
	}

	virtual int keypress(const Key& key) {
		stringstream ss;

		if (_keys.count(key)) {
			_key = key;
			return -1;
		}
		return 0;
	}

	virtual int render(IDisplay* win) {
		size_t pos = 0;
		size_t i = 0;
		for (auto &x : _keys) {
			stringstream ss;
			ss << "[" << (char) x.first.key() << ": " << x.second << "]  ";
			win->write(0, pos, ss.str(), (i++ % 7) + 1);
			pos += ss.str().length();
		}
		return 0;
	}

protected:
	map<Key, string> _keys;
	Key _key;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__HOTKEYS__H__

