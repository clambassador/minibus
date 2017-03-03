#ifndef __MINIBUS__WIDGET__XNAV__H__
#define __MINIBUS__WIDGET__XNAV__H__

#include <vector>

namespace minibus {

class XNav {
public:
	XNav() : XNav(0) {}
	XNav(size_t max) :
	    _xcur(0), _xmin(0), _xmax(max) {}

	virtual void resize(size_t max) {
		_xmax = max;
	}

	virtual int keypress(const Key& key) {
		if (key.left()) {
			if (_xcur > 0) --_xcur;
		} else if (key.right()) {
			if (++_xcur == _xmax) --_xcur;
		} else if (key.home()) {
			_xcur = 0;
		} else if (key.end()) {
			_xcur = _xmax;
		} else return 0;

		return 1;
	}

protected:
	size_t _xcur;
	size_t _xmin;
	size_t _xmax;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__XNAV__H__

