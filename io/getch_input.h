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
	/* TODO: make a timeout version */
	virtual Key get_key() {
		return Key(getch());
	}
};

}  // namespace minibus

#endif  // __MINIBUS__IO__GETCH_INPUT__H__
