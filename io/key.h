#ifndef __MINIBUS__IO__KEY__H__
#define __MINIBUS__IO__KEY__H__

#include <ncurses.h>

#include <iostream>
#include <set>

using namespace std;

namespace minibus {

class Key {
public:
	Key(int ch) : _ch(ch) {}
	Key(const Key& key) : _ch(key._ch) {}
	bool operator<(const Key& other) const {
		return tidy(_ch) < tidy(other._ch);
	}

	bool operator==(const Key& other) const {
		return tidy(_ch) == tidy(other._ch);
	}

	static Key javascript(int key) {
		if (key == 37) return KEY_LEFT;
		if (key == 38) return KEY_UP;
		if (key == 39) return KEY_RIGHT;
		if (key == 40) return KEY_DOWN;
		return key;
	}

	static int tidy(int key) {
		// handle paired keys. currently only one.
		switch (key) {
			case KEY_ENTER:
				return '\n';
			case '\r':
				return '\n';
			default:
				return key;
		}
	}

	bool enter() const {
		return (_ch == '\n' || _ch == KEY_ENTER);
	}

	bool up() const {
		return _ch == KEY_UP;
	}

	bool down() const {
		return _ch == KEY_DOWN;
	}

	bool left() const {
		return _ch == KEY_LEFT;
	}

	bool right() const {
		return _ch == KEY_RIGHT;
	}

	bool page_down() const {
		return _ch == KEY_NPAGE;
	}

	bool page_up() const {
		return _ch == KEY_PPAGE;
	}

	bool home() const {
		return _ch == KEY_HOME;
	}

	bool end() const {
		return _ch == KEY_END;
	}

	bool shift_home() const {
		return _ch == KEY_SHOME;
	}

	bool shift_end() const {
		return _ch == KEY_SEND;
	}

	bool del() const {
		return _ch == KEY_DC;
	}

	bool backspace() const {
		return _ch == KEY_BACKSPACE;
	}

	bool eot() const {
		return _ch == 4;
	}

	bool y_navigation() const {
		static set<int> navkeys;
		if (navkeys.empty()) {
			navkeys.insert(KEY_UP);
			navkeys.insert(KEY_DOWN);
			navkeys.insert(KEY_PPAGE);
			navkeys.insert(KEY_NPAGE);
		}
		return (navkeys.count(_ch));
	}

	bool x_navigation() const {
		static set<int> navkeys;
		if (navkeys.empty()) {
			navkeys.insert(KEY_LEFT);
			navkeys.insert(KEY_RIGHT);
			navkeys.insert(KEY_HOME);
			navkeys.insert(KEY_SHOME);
			navkeys.insert(KEY_END);
			navkeys.insert(KEY_SEND);
		}
		return (navkeys.count(_ch));
	}

	bool navigation() const {
		static set<int> navkeys;
		if (navkeys.empty()) {
			navkeys.insert(KEY_LEFT);
			navkeys.insert(KEY_UP);
			navkeys.insert(KEY_RIGHT);
			navkeys.insert(KEY_DOWN);
			navkeys.insert(KEY_HOME);
			navkeys.insert(KEY_SHOME);
			navkeys.insert(KEY_END);
			navkeys.insert(KEY_SEND);
			navkeys.insert(KEY_PPAGE);
			navkeys.insert(KEY_NPAGE);
		}
		return (navkeys.count(_ch));
	}

	int key() const {
		return _ch;
	}

protected:
	int _ch;

};

}  // namespace minibus

#endif  // __MINIBUS__IO__KEY__H__
