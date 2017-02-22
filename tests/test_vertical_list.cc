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
#include "minibus/widgets/vertical_list.h"

using namespace std;
using namespace std::placeholders;
using namespace minibus;

int main() {
	initscr();
	start_color();
	keypad(stdscr, true);
	noecho();
	cbreak();

	Text *header = new Text("WELCOME TO TEXT ENTRY !!!");
	Text *tx2 = new Text("");
	VerticalList *vl = new VerticalList();
	TextEntry* name = new TextEntry("NAME: ");
	vl->add_items(name,
		      new TextEntry("AGE : "),
		      new TextEntry("JOB : "),
		      new TextEntry("MOOD: "));

	HeaderMain *hm = new HeaderMain(header, vl);

	MinibusDriver md;
	md.add_state_widget(new CloseOnKey(hm));
	md.add_state_widget(new CloseOnKey(tx2));
	md.start();
	tx2->set_text("Thanks " + name->get_result().get());
	md.wait();
}
