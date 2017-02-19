#ifndef __MINIBUS__WIDGET__CLOSE_ON_KEY__H__
#define __MINIBUS__WIDGET__CLOSE_ON_KEY__H__

#include <functional>
#include <set>
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
			: Compose(next) {
		_keys.insert(key);
	}
	template<typename... ARGS>
	CloseOnKey(Widget* next, const Key& key, const Key& car, ARGS... cdr)
			: CloseOnKey(next, key, cdr...) {
		_keys.insert(car);
	}

	virtual int keypress(const Key& key) {
		if (_keys.count(key)) return -1;
		return _next->keypress(key);
	}

protected:
	set<Key> _keys;
};

}  // minibus

#endif  // __MINIBUS__WIDGET__CLOSE_ON_KEY__H__

