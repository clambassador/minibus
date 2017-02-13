#include <iostream>
#include <functional>
#include <future>
#include <ncurses.h>
#include <string>
#include <vector>

#include "minibus/io/key.h"
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

	ListSelect ls(vs);
	future<int> fpos = ls.get_selected_pos();
	future<string> fval = ls.get_selected_value();

	while (true) {
		ls.render(stdscr);
		Key key(getch());
		if (key.enter()) {
			ls.close();
			break;
		} else {
			ls.keypress(key);
		}
	}
	fpos.wait();
	fval.wait();
	cout << "selected: " << fpos.get() << " " << fval.get() << endl;

}
