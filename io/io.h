#ifndef __MINIBUS__IO__IO__H__
#define __MINIBUS__IO__IO__H__

#include "minibus/io/key.h"

namespace minibus

class IO {
public:
	static Key getch() {
		Key key(getch());
		return key;
	}
};

}  // namespace minibus

#endif  // __MINIBUS__IO__IO__H__
