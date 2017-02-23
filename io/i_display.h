#ifndef __MINIBUS__IO__I_DISPLAY__H__
#define __MINIBUS__IO__I_DISPLAY__H__

#include <string>

using namespace std;

namespace minibus {

class RenderFinish;

class IDisplay {
public:
	virtual ~IDisplay() {}
	virtual void move(size_t y, size_t x) = 0;
	//virtual void write(size_t y, size_t x, const string& text) = 0;
	virtual void write(size_t y, size_t x, const string& text,
		   int attr = 0) = 0;
	virtual RenderFinish* start_render() = 0;
	virtual void finish_render() = 0;
	virtual void clear() = 0;

	virtual size_t width() const = 0;
	virtual size_t height() const = 0;

	virtual void vertical() = 0;
	virtual void horizontal() = 0;

	virtual void stay() = 0;

	enum {
		WHITE_BLACK = 0,
		RED_BLACK,
		BLUE_BLACK,
		GREEN_BLACK,
		MAGENTA_BLACK,
		CYAN_BLACK,
		YELLOW_BLACK,
		BLACK_WHITE,
		BLACK_RED,
		BLACK_BLUE,
		BLACK_GREEN,
		BLACK_MAGENTA,
		BLACK_CYAN,
		BLACK_YELLOW,
		RED_WHITE,
		BLUE_WHITE,
		GREEN_WHITE,
		MAGENTA_WHITE,
		CYAN_WHITE,
		YELLOW_WHITE,
		BOLD = 32
	};
};

}  // namespace minibus

#endif  // __MINIBUS__IO__I_DISPLAY__H__
