#ifndef __MINIBUS__IO__CACHED_DISPLAY__H__
#define __MINIBUS__IO__CACHED_DISPLAY__H__

#include <cassert>
#include <cstring>
#include <string>

#include "minibus/io/i_display.h"
#include "minibus/io/render_finish.h"

using namespace std;

namespace minibus {

class CachedDisplay : public IDisplay {
public:
	CachedDisplay(size_t y, size_t x)
			: _maxx(x), _maxy(y) {
		_screen_size = (_maxx * _maxy) + 1;
		_screen.reset(new char[_screen_size]);
		clear();
	}

	virtual void write(size_t y, size_t x, const string& text) {
		for (size_t i = 0; i < text.length(); ++i) {
			set(y, x + i, text.at(i));
		}
	}

	virtual void get_data(string* value) {
		value->assign(_screen.get());
	}
	virtual void clear() {
		memset(_screen.get(), ' ', _maxx * _maxy);
		_screen.get()[_maxx * _maxy] = 0;
	}

	virtual RenderFinish* start_render() {
		return new RenderFinish(this);
	}

	virtual void finish_render() {
		string s;
		get_data(&s);
	}

	virtual size_t width() const { return _maxx; }
	virtual size_t height() const { return _maxy; }

protected:
	CachedDisplay(const CachedDisplay&) : _maxx(0), _maxy(0) { assert(0); }

	virtual void set(int y, int x, char c) {
		_screen.get()[pos(y, x)] = c;
	}

	virtual size_t pos(size_t y, size_t x) {
		return (y * _maxx) + x;
	}

	const size_t _maxx;
	const size_t _maxy;
	unique_ptr<char[]> _screen;
	size_t _screen_size;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__CACHED_DISPLAY__H__
