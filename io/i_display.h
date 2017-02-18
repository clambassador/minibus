#ifndef __MINIBUS__IO__I_DISPLAY__H__
#define __MINIBUS__IO__I_DISPLAY__H__

#include <string>

using namespace std;

namespace minibus {

class RenderFinish;

class IDisplay {
public:
	virtual void write(size_t y, size_t x, const string& text) = 0;
	virtual RenderFinish* start_render() = 0;
	virtual void finish_render() = 0;
	virtual void clear() = 0;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__I_DISPLAY__H__
