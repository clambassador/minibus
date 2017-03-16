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
#include "minibus/widgets/moveable_text.h"
#include "minibus/widgets/text.h"

using namespace std;
using namespace std::placeholders;
using namespace minibus;

int main() {
	initscr();
	start_color();
	keypad(stdscr, true);
	noecho();
	cbreak();

	MoveableText *tx1 = new MoveableText("tx1", "hit a b c or d!");
	Text *tx2 = new Text("tx2", "thanks alot!");

	MinibusDriver md;
	md.start(md.build_program(
			"main",
		        new CloseOnKey(tx1, 'a', 'b', 'c', 'd'))
		->then(new CloseOnKey(tx2))
		->finish());
	md.wait();
}
