#ifndef __MINIBUS__WIDGET__MOVEABLE_TEXT__H__
#define __MINIBUS__WIDGET__MOVEABLE_TEXT__H__

#include <functional>
#include <string>
#include <vector>
#include <ncurses.h>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/text.h"
#include "minibus/widgets/widget.h"
#include "minibus/widgets/xynav.h"

using namespace std;

namespace minibus {

class MoveableText : public Text, public XYNav {
public:
	MoveableText(const string& text) : Text(text), XYNav(30) {}
	virtual ~MoveableText() {}

	virtual int render(IDisplay* win) {
		win->write(_ycur, _xcur, _text);
		return 0;
	}

	virtual int open() {
		return 0;
	}

	virtual int close() {
		return 0;
	}

	virtual int keypress(const Key& key) {
		return XYNav::keypress(key);
	}

};

}  // minibus

#endif  // __MINIBUS__WIDGET__MOVEABLE_TEXT__H__
