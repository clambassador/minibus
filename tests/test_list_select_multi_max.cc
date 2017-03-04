#include <iostream>
#include <functional>
#include <future>
#include <ncurses.h>
#include <string>
#include <vector>

#include "minibus/io/cached_display.h"
#include "minibus/io/key.h"
#include "minibus/io/screen_display.h"
#include "minibus/widgets/list_select_multi.h"

using namespace std;
using namespace std::placeholders;
using namespace minibus;

int main() {
	vector<string> vs;
	vs.push_back("hello");
	vs.push_back("there");
	vs.push_back("good");
	vs.push_back("sir");
	vs.push_back("here");
	vs.push_back("are");
	vs.push_back("some");
	vs.push_back("things");
	vs.push_back("to");
	vs.push_back("select");

	initscr();
	start_color();
	keypad(stdscr, true);
	noecho();
	cbreak();

	ListSelectMulti lsm(vs, 3);

	while (true) {
		lsm.render(new ScreenDisplay(stdscr));
		Key key(getch());
		if (key.enter()) {
			lsm.close();
			break;
		} else {
			lsm.keypress(key);
		}
	}
	set<size_t> selected = lsm.get_selected();
	cout << "\n\rSelected" << endl;
	for (auto x : selected) {
		cout << '\r' <<  vs[x] << endl;
	}
	getch();
	endwin();
}
