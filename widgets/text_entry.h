#ifndef __MINIBUS__WIDGET__TEXT_ENTRY__H__
#define __MINIBUS__WIDGET__TEXT_ENTRY__H__

#include <functional>
#include <future>
#include <string>
#include <vector>
#include <ncurses.h>

#include "minibus/io/key.h"
#include "minibus/widgets/widget.h"
#include "minibus/widgets/xnav.h"

using namespace std;

namespace minibus {

class TextEntry : public XNav, public Text {
public:
	TextEntry(const string& prompt)
			: XNav(), Text(""), _prompt(prompt) {}

	virtual int render(IDisplay* win) {
		win->write(0, 0, _prompt + _text.c_str());
		win->move(0, _prompt.length() + _xcur);
		return 0;
	}

	virtual int close() {
		_result.set_value(_text);
		return 0;
	}

	virtual int keypress(const Key& key) {
		if (key.del()) del();
		else if (key.backspace()) backspace();
		else if (key.navigation()) XNav::keypress(key);
		else if (key.key() >= 0 && key.key() < 256) {
			insert(key, _xcur);
		}
		else return 0;
		return 1;
	}

	virtual future<string> get_result() {
		return _result.get_future();
	}

protected:
	virtual void insert(const Key& key, size_t pos) {
		_text = _text.substr(0, pos)
		    + (char) key.key()
		    + ((pos < _text.length()) ? _text.substr(pos) : "");
		++_xcur;
		++_xmax;
	}

	virtual void del() {
		if (_xcur < _text.size() - 1) {
			cut(_xcur);
		}
	}

	virtual void backspace() {
		if (_xcur) {
			--_xcur;
			cut(_xcur);
		}
	}

	virtual void cut(size_t pos) {
		_text = _text.substr(0, pos) + _text.substr(pos + 1);
		--_xmax;
	}

	string _prompt;
	promise<string> _result;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__TEXT_ENTRY__H__
