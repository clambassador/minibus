#include <iostream>
#include <functional>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

#include "minibus/driver/minibus_driver.h"
#include "minibus/io/key.h"
#include "minibus/widgets/close_on_key.h"
#include "minibus/widgets/header_main.h"
#include "minibus/widgets/list_select.h"
#include "minibus/widgets/text.h"
#include "minibus/widgets/text_entry.h"

using namespace std;
using namespace std::placeholders;
using namespace minibus;

int main() {
	initscr();
	start_color();
	keypad(stdscr, true);
	noecho();
	cbreak();

	TextEntry *tx1 = new TextEntry("tx1", "> ");
	Text *header = new Text("header", "WELCOME TO TEXT ENTRY !!!");
	Text *tx2 = new Text("tx2", "");
	HeaderMain *hm = new HeaderMain(header, tx1);

	MinibusDriver md;
	md.start(md.build_program("main", new CloseOnKey(hm))
		 ->then(new CloseOnKey(tx2))->finish());
	string txt = tx1->get_result().get();
	tx2->set_text("Thanks for your interesting thoughts: " + txt);
	md.wait();
}
