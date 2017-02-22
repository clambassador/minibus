#ifndef __MINIBUS__WIDGET__TEXT__H__
#define __MINIBUS__WIDGET__TEXT__H__

#include <functional>
#include <string>
#include <vector>
#include <ncurses.h>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"

using namespace std;

namespace minibus {

class Text : public Widget {
public:
	Text(const string& text) : _bold(0), _text(text) {}
	virtual ~Text() {}

	virtual int render(IDisplay* win) {
		win->write(0, 0, _text, _bold);
		return 0;
	}

	virtual int open() {
		return 0;
	}

	virtual int close() {
		return 0;
	}

	virtual int keypress(const Key& key) {
		return 0;
	}

	virtual void set_text(const string& text) {
		_text = text;
	}

	virtual void bold() {
		_bold = IDisplay::BOLD;
	}

	virtual void focus() {
		bold();
	}

protected:
	int _bold;
	string _text;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__TEXT__H__

