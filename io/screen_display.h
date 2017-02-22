#ifndef __MINIBUS__IO__SCREEN_DISPLAY__H__
#define __MINIBUS__IO__SCREEN_DISPLAY__H__

#include <mutex>
#include <ncurses.h>

#include "minibus/io/base_display.h"
#include "minibus/io/render_finish.h"

namespace minibus {

class ScreenDisplay : public BaseDisplay {
public:
	ScreenDisplay(WINDOW* window) : BaseDisplay(), _window(window) {
		/* N.B.: keep up to date with IDisplay's enum */
                init_pair(0, COLOR_WHITE, COLOR_BLACK);
                init_pair(1, COLOR_RED, COLOR_BLACK);
                init_pair(2, COLOR_BLUE, COLOR_BLACK);
                init_pair(3, COLOR_GREEN, COLOR_BLACK);
                init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
                init_pair(5, COLOR_CYAN, COLOR_BLACK);
                init_pair(6, COLOR_YELLOW, COLOR_BLACK);
                init_pair(7, COLOR_BLACK, COLOR_WHITE);
                init_pair(8, COLOR_BLACK, COLOR_RED);
                init_pair(9, COLOR_BLACK, COLOR_BLUE);
                init_pair(10, COLOR_BLACK, COLOR_GREEN);
                init_pair(11, COLOR_BLACK, COLOR_MAGENTA);
                init_pair(12, COLOR_BLACK, COLOR_CYAN);
                init_pair(13, COLOR_BLACK, COLOR_MAGENTA);
                init_pair(13, COLOR_BLACK, COLOR_YELLOW);
                init_pair(15, COLOR_RED, COLOR_WHITE);
                init_pair(16, COLOR_BLUE, COLOR_WHITE);
                init_pair(17, COLOR_GREEN, COLOR_WHITE);
                init_pair(18, COLOR_MAGENTA, COLOR_WHITE);
                init_pair(19, COLOR_CYAN, COLOR_WHITE);
                init_pair(20, COLOR_YELLOW, COLOR_WHITE);
	}

	virtual void write(size_t y, size_t x, const string& text,
			   int attr = 0) {
		unique_lock<mutex> ul(_m);
		write_impl(y, x, text, attr);
	}

	virtual void move(size_t y, size_t x) {
		wmove(_window, y_pos(y), x_pos(x));
	}

	virtual void clear() {
		::clear();
	}

	virtual size_t width() const { return 80; }
	virtual size_t height() const { return 40; }

protected:
	virtual void write_impl(size_t y, size_t x, const string& text) {
		mvwprintw(_window, y_pos(y), x_pos(x), text.c_str());
		seen(y_pos(y), x_pos(x) + text.length());
	}

	virtual void write_impl(size_t y, size_t x, const string& text,
				int attr) {
		vector<int> attrs = process_attrs(attr);
		for (auto &z : attrs) attron(z);
		write_impl(y, x, text);
		for (auto &z : attrs) attroff(z);
	}

	virtual vector<int> process_attrs(int attr) {
		vector<int> retval;
		if (BOLD & attr) {
			retval.push_back(A_BOLD);
			attr -= BOLD;
		}
		/* TODO: put other attrs here. */
		if (attr) retval.push_back(COLOR_PAIR(attr));
		return retval;
	}

	WINDOW* _window;
	mutex _m;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__SCREEN_DISPLAY__H__
