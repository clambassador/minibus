#ifndef __MINIBUS__WIDGET__CLOSE_ON_KEY__H__
#define __MINIBUS__WIDGET__CLOSE_ON_KEY__H__

#include <functional>
#include <string>
#include <vector>

#include "minibus/io/key.h"
#include "minibus/widgets/compose.h"
#include "minibus/widgets/widget.h"

using namespace std;

namespace minibus {

class CloseOnKey : public Compose {
public:
	CloseOnKey(Widget* next) : CloseOnKey(next, Key('\n')) {}
	CloseOnKey(Widget* next, const Key& key)
			: Compose(next), _key(key) {}

	virtual int keypress(const Key& key) {
		if (key == _key) return -1;
		return _next->keypress(key);
	}

protected:
	Key _key;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__CLOSE_ON_KEY__H__

