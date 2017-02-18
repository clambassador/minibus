#ifndef __MINIBUS__IO__RENDER_FINISH__H__
#define __MINIBUS__IO__RENDER_FINISH__H__

#include "minibus/io/i_display.h"

using namespace std;

namespace minibus {

class RenderFinish {
public:
	RenderFinish(IDisplay *display) :
		_display(display) {}
	~RenderFinish() {
		_display->finish_render();
	}
protected:
	IDisplay* _display;
};

}  // namespace minibus

#endif  // __MINIBUS__IO__RENDER_FINISH__H__

