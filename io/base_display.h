#ifndef __MINIBUS__IO__BASE_DISPLAY__H__
#define __MINIBUS__IO__BASE_DISPLAY__H__

#include <mutex>
#include <ncurses.h>

#include "minibus/io/i_display.h"
#include "minibus/io/render_finish.h"

namespace minibus {

class BaseDisplay : public IDisplay {
public:
	BaseDisplay() {
		reset_box();
	}
	virtual ~BaseDisplay() {}

	virtual void clear() {
		::clear();
	}

	virtual RenderFinish* start_render() {
		reset_box();
		_stay = false;
		return new RenderFinish(this);
	}

	virtual void finish_render() {
	}

	virtual void stay() {
		_stay = true;
	}

	virtual void horizontal() {
		_xtop = _xbot + 1;
	}

	virtual void vertical() {
		_ytop = _ybot + 1;
	}

	virtual void move(size_t y, size_t x) {
		seen(y_pos(y), x_pos(x));
	}

protected:
	virtual void reset_box() {
		_xtop = 0;
		_ytop = 0;
		_xbot = 0;
		_ybot = 0;
	}

	virtual size_t x_pos(size_t x) {
		return x + _xtop;
	}

	virtual size_t y_pos(size_t y) {
		return y + _ytop;
	}

	virtual void seen(size_t y, size_t x) {
		if (y > _ybot) _ybot = y;
		if (x > _xbot) _xbot = x;
		if (!_stay) {
			_cursor_y = y;
			_cursor_x = x;
		}
	}

	size_t _xtop;
	size_t _ytop;
	size_t _xbot;
	size_t _ybot;
	bool _stay;
	size_t _cursor_x;
	size_t _cursor_y;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__BASE_DISPLAY__H__
