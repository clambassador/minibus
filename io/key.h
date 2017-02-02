#ifndef __MINIBUS__IO__KEY__H__
#define __MINIBUS__IO__KEY__H__

#include <ncurses.h>

namespace minibus {

class Key {
public:
	Key(int ch) : _ch(ch) {}

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

	int key() const {
		return _ch;
	}

protected:
	int _ch;

};

}  // namespace minibus

#endif  // __MINIBUS__IO__KEY__H__
