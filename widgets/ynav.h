#ifndef __MINIBUS__WIDGET__YNAV__H__
#define __MINIBUS__WIDGET__YNAV__H__

#include <vector>

namespace minibus {

class YNav {
public:
	YNav() : YNav(0) {}
	YNav(size_t max) :
	    _ycur(0), _ymin(0), _ymax(max) {}

	virtual void resize(size_t max) {
		_ymax = max;
	}

	virtual int keypress(const Key& key) {
		if (key.up()) {
			if (_ycur > 0) --_ycur;
		} else if (key.down()) {
			if (++_ycur == _ymax) --_ycur;
		}
		return 0;
	}

protected:
	size_t _ycur;
	size_t _ymin;
	size_t _ymax;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__LIST_SELECT__H__

