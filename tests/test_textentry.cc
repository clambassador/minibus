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
	Text *tx2 = new Text("tx2", "");

	MinibusDriver md;
	md.start(md.build_program("main",
		new CloseOnKey(tx1))->then(new CloseOnKey(tx2))->finish());
	tx2->set_text("Thanks for your interesting thoughts: " +
		      tx1->get_result().get());
	md.wait();
}
