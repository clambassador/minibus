#ifndef __MINIBUS__WIDGET__XYNAV__H__
#define __MINIBUS__WIDGET__XYNAV__H__

#include <vector>

#include "minibus/widgets/xnav.h"
#include "minibus/widgets/ynav.h"

namespace minibus {

class XYNav : public XNav, public YNav {
public:
	XYNav() : XNav(0), YNav(0) {}
	XYNav(size_t max) : XNav(max), YNav(max) {}
	XYNav(size_t ymax, size_t xmax) :
	    XNav(xmax), YNav(ymax) {}

	virtual void resize(size_t max) {
		resize(max, max);
	}

	virtual void resize(size_t ymax, size_t xmax) {
		_xmax = xmax;
		_ymax = ymax;
	}

	virtual int keypress(const Key& key) {
		if (key.left() || key.right()) {
			XNav::keypress(key);
		}
		if (key.up() || key.down()) {
			YNav::keypress(key);
		}
		return 0;
	}

protected:
};

}  // minibus

#endif  // __MINIBUS__WIDGET__XYNAV__H__
