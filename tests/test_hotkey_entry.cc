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
#include "minibus/widgets/hotkeys.h"
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

	Hotkeys *tx1 = new Hotkeys("tx1", "test", "hi", "more", "keys");
	VerticalList *vl = new VerticalList("vl", new Text("prompt", "Good day"),
					    new TextEntry("enter", "> "));
	HeaderMain *hm = new HeaderMain(tx1, vl);

	MinibusDriver md;
	md.start(md.build_program("main", new CloseOnKey(hm))->finish());
	md.wait();
}
