#ifndef __MINIBUS__IO__CACHED_INPUT__H__
#define __MINIBUS__IO__CACHED_INPUT__H__

#include <ncurses.h>

#include "ib/wait_queue.h"
#include "minibus/io/i_input.h"
#include "minibus/io/key.h"

namespace minibus {

class CachedInput : public IInput {
public:
	CachedInput() {}
	~CachedInput() {}

	virtual void terminate() {
		_q.push(4);
	}

	virtual Key get_key() {
		return _q.pop();
	}

	virtual void queue_key(const Key& key) {
		_q.push(key);
	}

protected:
	WaitQueue<Key> _q;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__CACHED_INPUT__H__
