#include <iostream>
#include <functional>
#include <future>
#include <ncurses.h>
#include <string>
#include <vector>

#include "minibus/driver/minibus_driver.h"
#include "minibus/io/cached_display.h"
#include "minibus/io/key.h"
#include "minibus/io/screen_display.h"
#include "minibus/widgets/close_on_key.h"
#include "minibus/widgets/list_select.h"

using namespace std;
using namespace std::placeholders;
using namespace minibus;

vector<string> vs;
int result(size_t t) {
	mvprintw(10, 10, vs[t].c_str());
	return 0;
}

int main() {
	vs.push_back("hello");
	vs.push_back("there");
	vs.push_back("good");
	vs.push_back("sir");

	initscr();
	start_color();
	keypad(stdscr, true);
	noecho();
	cbreak();

	ListSelect *ls = new ListSelect("ls", vs);
	MinibusDriver md;
	md.start(md.build_program("main", new CloseOnKey(ls))->finish());
	md.wait();
}
