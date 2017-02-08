#ifndef __MINIBUS__WIDGET__COMPOSE__H__
#define __MINIBUS__WIDGET__COMPOSE__H__

#include <functional>
#include <string>
#include <vector>

#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"

using namespace std;

namespace minibus {

class Compose : public Widget {
public:
	Compose(Widget* next) : _next(next) {
		assert(_next.get());
	}

	virtual int render(WINDOW* win) {
		return _next->render(win);
	}

	virtual int open() {
		return _next->open();
	}

	virtual int close() {
		return _next->close();
	}

	virtual int keypress(const Key& key) {
		return _next->keypress(key);
	}

protected:
	unique_ptr<Widget> _next;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__COMPOSE__H__
