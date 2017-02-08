#include <iostream>
#include <functional>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

#include "minibus/driver/minibus_driver.h"
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

	ListSelect *ls = new ListSelect(vs, bind(&result, _1));
	Text *tx1 = new Text("Hello THERE!!");
	tx2 = new Text("You're all set!");

	MinibusDriver md;
	md.set_state_widget(0, new CloseOnKey(tx1));
	md.set_state_widget(1, new CloseOnKey(ls));
	md.set_state_widget(2, new CloseOnKey(tx2),
			    bind(MinibusDriver::terminate, _1));

	md.start();
}
