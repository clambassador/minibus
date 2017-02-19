#ifndef __MINIBUS__IO__SCREEN_DISPLAY__H__
#define __MINIBUS__IO__SCREEN_DISPLAY__H__

#include <ncurses.h>

#include "minibus/io/i_display.h"
#include "minibus/io/render_finish.h"

namespace minibus {

class ScreenDisplay : public IDisplay {
public:
	ScreenDisplay(WINDOW* window) : _window(window) {
	}

	virtual void write(size_t y, size_t x, const string& text) {
		mvwprintw(_window, y, x, text.c_str());
	}

	virtual void clear() {
		::clear();
	}

	virtual RenderFinish* start_render() {
		return new RenderFinish(this);
	}

	virtual void finish_render() {
	}

	virtual size_t width() const { return 80; }
	virtual size_t height() const { return 40; }


protected:
	WINDOW* _window;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__SCREEN_DISPLAY__H__
