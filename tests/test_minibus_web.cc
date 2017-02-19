#include <iostream>
#include <functional>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

#include "minibus/driver/minibus_driver.h"
#include "minibus/io/key.h"
#include "minibus/web/minibus_web.h"
#include "minibus/widgets/close_on_key.h"
#include "minibus/widgets/list_select.h"
#include "minibus/widgets/text.h"

using namespace std;
using namespace std::placeholders;
using namespace minibus;

vector<string> vs;

class MinibusDriverTest : public MinibusDriver {
public:
	MinibusDriverTest(IDisplay* display,
			  IInput* input)
			: MinibusDriver(display, input) {
		vs.push_back("new const");
		_ls = new ListSelect(vs);
		_tx1 = new Text("Hello THERE!!");
		_tx2 = new Text("loading.");
		_f_pos = _ls->get_selected_pos();
		add_state_widget(new CloseOnKey(_tx1));
		add_state_widget(new CloseOnKey(_ls));
		add_state_widget(new CloseOnKey(_tx2));
	}

	virtual ~MinibusDriverTest() {
		Logger::error("EXIT");
	}

protected:
	virtual void after_keypress(const Key& key) {
		if (pos_ready()) {
			int pos = _f_pos.get();
			_tx2->set_text(
			    Logger::stringify("You chose: % (item %)",
				      vs[pos], pos));
		}
	}

	virtual bool pos_ready() {
		if (!_f_pos.valid()) return false;
		return _f_pos.wait_for(chrono::seconds(0)) ==
			future_status::ready;
	}

	ListSelect* _ls;
	Text* _tx1;
	Text* _tx2;
	future<int> _f_pos;
};

int main() {
	vs.push_back("hello");
	vs.push_back("there");
	vs.push_back("good");
	vs.push_back("sir");

	Config::_()->load("tests/test.cfg");
	MinibusWeb<MinibusDriverTest> mw;
	WebServer webserver(&mw);
	webserver.start_server(Config::_()->get("http_port"));
	cout << Config::_()->get("http_port") << endl;
        cout << "Running.\nHit enter to stop.";

        getchar();
        webserver.stop_server();
}
