#ifndef __MINIBUS__WIDGET__BASE__H__
#define __MINIBUS__WIDGET__BASE__H__

#include <functional>
#include <string>
#include <vector>
#include <ncurses.h>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"

using namespace std;

namespace minibus {

class Base : public Widget {
public:
	Base() {}
	virtual ~Base() {}

	virtual int render(IDisplay* win) {
		return 0;
	}

	virtual int open() {
		return 0;
	}

	virtual int close() {
		return 0;
	}

	virtual int keypress(const Key& key) {
		return -1;
	}

	virtual void focus() {}
protected:
};

}  // minibus

#endif  // __MINIBUS__WIDGET__BASE__H__

