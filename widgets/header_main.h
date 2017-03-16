#ifndef __MINIBUS__WIDGET__HEADER_MAIN__H__
#define __MINIBUS__WIDGET__HEADER_MAIN__H__

#include <functional>
#include <string>
#include <vector>

#include "minibus/io/i_display.h"
#include "minibus/io/key.h"
#include "minibus/widgets/base.h"

using namespace std;

namespace minibus {

class HeaderMain : public Base {
public:
	HeaderMain(Widget* header, Widget* main)
	    : HeaderMain("", header, main) {}

	HeaderMain(const string& name, Widget* header, Widget* main)
	    : Base(name), _header(header), _main(main) {
		assert(_header.get());
		assert(_main.get());
	}

	virtual ~HeaderMain() {}

	virtual int render(IDisplay* display) {
		assert(!_header->render(display));
		display->vertical();
		return _main->render(display);
	}

	virtual int open() {
		assert(!_header->open());
		return _main->open();
	}

	virtual int close() {
		assert(!_header->close());
		return _main->close();
	}

	virtual int keypress(const Key& key) {
		int retval = _main->keypress(key);
		if (!retval) retval = _header->keypress(key);
		return retval;
	}

	virtual void focus() {
		_header->focus();
	}

protected:
	unique_ptr<Widget> _header;
	unique_ptr<Widget> _main;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__HEADER_MAIN__H__
