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
bool decide(ListSelect* ls) {
	static int i = 0;
	static int pos = 0;
	if (ls) pos = ls->get_selected();
	++i;
	stringstream ss;
	ss << "you chose " + vs[pos] << " " << i << " times!";
	tx2->set_text(ss.str());
	if (i == 10) {
		tx2->set_text("okay i'll stop.");
	} else if (i == 11) return false;
	if (!ls) return true;
	return pos;
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

	MinibusDriver md;
	md.start(md.build_program("main", new CloseOnKey(tx1))
		 ->then(new CloseOnKey(ls))
		 ->when(new CloseOnKey(tx1), new CloseOnKey(tx2), bind(&decide, ls))
		 ->done()
		 ->loop(nullptr, bind(&decide, nullptr))
		 ->finish());
	md.wait();
}
