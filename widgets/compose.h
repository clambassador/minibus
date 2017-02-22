#ifndef __MINIBUS__WIDGET__COMPOSE__H__
#define __MINIBUS__WIDGET__COMPOSE__H__

#include <functional>
#include <string>
#include <vector>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"

using namespace std;

namespace minibus {

class Compose : public Widget {
public:
	Compose(Widget* next) : _next(next) {
		assert(_next.get());
	}

	virtual ~Compose() {}

	virtual int render(IDisplay* display) {
		return _next->render(display);
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

	virtual void focus() {
		_next->focus();
	}

protected:
	unique_ptr<Widget> _next;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__COMPOSE__H__
