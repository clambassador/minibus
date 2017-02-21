#ifndef __MINIBUS__WEB__MINIBUS_WEB__H__
#define __MINIBUS__WEB__MINIBUS_WEB__H__

#include <cstdlib>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "ib/config.h"
#include "ib/formatting.h"
//#include "ib/run.h"

#include "centipede/types.h"
#include "centipede/webserver.h"
#include "centipede/backend/i_webserver_backend.h"
#include "centipede/nodes/scaffold_node.h"

#include "minibus/io/cached_display.h"
#include "minibus/io/cached_input.h"

using namespace centipede;
using namespace ib;
using namespace std;

namespace minibus {

template <typename DRIVER>
class MinibusWeb : public IWebserverBackend {
public:
	MinibusWeb() {
		_node.reset(new ScaffoldNode(
				Config::_()->gets("html_file")));
	}

	virtual ~MinibusWeb() {}

	virtual void get_page(const ClientID& cid, int state,
	                      string* output) {
		*output = static_cast<INode*>(_node.get())->display(cid);
	}

        virtual void get_resource(const ClientID& cid,
                                  const ResourceID& rid,
                                  const string& ject,
                                  string* output) {
        }

	virtual bool set_value(const ClientID& cid, int state,
			       const string& name,
			       const vector<string>& parameters,
			       const map<string, string>& arguments) {
		if (name == "key") {
			int ch = atoi(arguments.at("val").c_str());
			if (!_keyboards.count(cid)) return false;
			if (!_keyboards[cid].get()) return false;
			_keyboards[cid]->queue_key(Key::javascript(ch));
			return true;
		}
		return false;
	}

	virtual bool get_value(const ClientID& cid, int state,
			       const string& name,
			       const vector<string>& parameters,
			       const map<string, string>& arguments,
			       string* output) {
		CachedDisplay *display = _displays[cid].get();
		if (!display) {
			*output = "";
			return false;
		}
		if (name == "screen_width") {
			*output = Logger::stringify("%", display->width());
			return true;
		}
		if (name == "screen_height") {
			*output = Logger::stringify("%", display->height());
			return true;
		}
		if (name == "screen") {
			display->get_data(output);
			return true;
		}
		if (name == "format") {
			display->get_format(output);
			return true;
		}
		Logger::error("unknown value %", name);
		*output = "";
		return false;
	}

	virtual int run_command(const ClientID& cid, int state,
	                        const string& command,
				const vector<string>& parameters,
				const map<string, string>& arguments) {
		return 0;
	}

        virtual void run_node_command(const ClientID&, int state,
                                      const string& node,
                                      const string& command,
                                      const vector<string>& parameters,
                                      const map<string, string>& arguments) {
	}

        virtual int recv_post(const ClientID&, const string& command,
                              const string& key, const string& filename,
                              const string& content_type, const string& encoding,
                              const string& data, uint64_t offset,
                              size_t size, string* output) {
		return 0;
	}

	virtual void new_client(const ClientID& cid) {
		_displays[cid].reset(new CachedDisplay(25, 80));
		_keyboards[cid].reset(new CachedInput());
		_drivers[cid].reset(new DRIVER(
			_displays[cid].get(),
			_keyboards[cid].get()));
		_drivers[cid]->start();
	}

	virtual void bye_client(const ClientID& cid) {
		cleanup(cid);
	}

protected:
	virtual void cleanup(const ClientID& cid) {
		_drivers.erase(cid);
		_displays.erase(cid);
		_keyboards.erase(cid);
	}

	map<ClientID, unique_ptr<CachedInput>> _keyboards;
	map<ClientID, unique_ptr<CachedDisplay>> _displays;
	map<ClientID, unique_ptr<DRIVER>> _drivers;

	unique_ptr<ScaffoldNode> _node;
};

}  // namespace minibus

#endif  // __MINIBUS__WEB__MINIBUS_WEB__H__
