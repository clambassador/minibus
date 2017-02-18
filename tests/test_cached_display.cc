#include <iostream>
#include <functional>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

#include "minibus/driver/minibus_driver.h"
#include "minibus/io/cached_display.h"
#include "minibus/io/getch_input.h"
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

	ListSelect *ls = new ListSelect(vs);
	Text *tx1 = new Text("Hello THERE!!");
	tx2 = new Text("loading.");

	MinibusDriver md(new CachedDisplay(25, 80), new GetchInput());
	md.add_state_widget(new CloseOnKey(tx1));
	md.add_state_widget(new CloseOnKey(ls));
	md.add_state_widget(new CloseOnKey(tx2));

	md.start();
	future<int> fpos = ls->get_selected_pos();
	fpos.wait();
	result(fpos.get());
}
