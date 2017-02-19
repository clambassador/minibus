#ifndef __MINIBUS__IO__GETCH_INPUT__H__
#define __MINIBUS__IO__GETCH_INPUT__H__

#include <ncurses.h>

#include "minibus/io/i_input.h"
#include "minibus/io/key.h"

namespace minibus {

class GetchInput : public IInput {
public:
	GetchInput() {}
	~GetchInput() {}
	virtual Key get_key() {
		return Key(getch());
	}

	virtual void terminate() {
		/* TODO: make a timeout version */
	}
};

}  // namespace minibus

#endif  // __MINIBUS__IO__GETCH_INPUT__H__
