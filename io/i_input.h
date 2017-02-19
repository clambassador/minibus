#ifndef __MINIBUS__IO__I_INPUT__H__
#define __MINIBUS__IO__I_INPUT__H__

namespace minibus {

class Key;

class IInput {
public:
	virtual Key get_key() = 0;
	virtual void terminate() = 0;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__DISPLAY__H__
