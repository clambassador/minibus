#ifndef __MINIBUS__WIDGET__WIDGET__H__
#define __MINIBUS__WIDGET__WIDGET__H__

#include <ncurses.h>

#include "minibus/io/key.h"
#include "minibus/io/i_display.h"

namespace minibus {

class Widget {
public:
	virtual int render(IDisplay*) = 0;
	virtual int open() = 0;
	virtual int close() = 0;
	virtual int keypress(const Key&) = 0;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__WIDGET__H__
