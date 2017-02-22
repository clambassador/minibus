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

	TextEntry *tx1 = new TextEntry("> ");
	Text *header = new Text("WELCOME TO TEXT ENTRY !!!");
	Text *tx2 = new Text("");
	HeaderMain *hm = new HeaderMain(header, tx1);

	MinibusDriver md;
	md.add_state_widget(new CloseOnKey(hm));
	md.add_state_widget(new CloseOnKey(tx2));
	md.start();
	string txt = tx1->get_result().get();
	tx2->set_text("Thanks for your interesting thoughts: " + txt);
	md.wait();
}
