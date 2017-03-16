#include <iostream>
#include <functional>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

#include "minibus/driver/minibus_driver.h"
#include "minibus/io/cached_display.h"
#include "minibus/io/getch_input.h"
#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/close_on_key.h"
#include "minibus/widgets/list_select.h"
#include "minibus/widgets/text.h"

using namespace std;
using namespace std::placeholders;
using namespace minibus;

vector<string> vs;
Text* tx2;
int result(size_t t) {
	stringstream ss;
	ss << "You chose: " << vs[t] << " (item " << t
	   << ")" << endl;
	tx2->set_text(ss.str());
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
	Text *tx1 = new Text("tx1", "Hello THERE!!");
	tx2 = new Text("tx2", "loading.");

	MinibusDriver md(new CachedDisplay(25, 80), new GetchInput());
	md.start(md.build_program("main", new CloseOnKey(tx1))->then(new CloseOnKey(ls))
	    ->then(new CloseOnKey(tx2))->finish());

	future<int> fpos = ls->get_selected_pos();
	fpos.wait();
	result(fpos.get());
}
