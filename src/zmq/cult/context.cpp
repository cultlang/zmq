#include "zmq/common.h"
#include "all.h"

using namespace craft;
using namespace craft::types;
using namespace cultlang::zmq;


CRAFT_DEFINE(ZContext)
{
	/*_.use<SObjectManipulation>().byConfiguring<ObjectManipulater>()
	->withMethod("bind", &ZContext::bind)
	->withMethod("connect", &ZContext::connect);*/
	_.defaults();
}

ZContext::ZContext()
{
	_ctx = zmq_ctx_new();
}


ZContext::~ZContext()
{
	zmq_ctx_destroy(_ctx);
}

instance<ZSocket> ZContext::bind(instance<std::string> kind, instance<int64_t> port)
{
	int zmq_type;
	if ((*kind) == "PUB")
	{
		zmq_type = ZMQ_PUB;
	}
	else if ((*kind) == "PUSH")
	{
		zmq_type = ZMQ_PUSH;
	}
	else if ((*kind) == "REP")
	{
		zmq_type = ZMQ_REP;
	}
	else if ((*kind) == "STREAM")
	{
		zmq_type = ZMQ_STREAM;
	}
	else
	{
		throw stdext::exception("Unsupported Bindable Kind {0}", *kind);
	}
	auto res = instance<ZSocket>::make();

	res->_socket = zmq_socket(_ctx, zmq_type);
	auto uri = fmt::format("tcp://*:{0}", *port.get());
	auto err = zmq_bind(res->_socket, uri.c_str());

	if (err == -1) throw stdext::exception("{0}", zmq_strerror(zmq_errno()));

	return res;
}

instance<ZSocket> ZContext::connect(instance<std::string> kind, instance<std::string> uri)
{
	int zmq_type;
	if ((*kind) == "SUB")
	{
		zmq_type = ZMQ_PUB;
	}
	else if ((*kind) == "PULL")
	{
		zmq_type = ZMQ_PUSH;
	}
	else if ((*kind) == "REQ")
	{
		zmq_type = ZMQ_REQ;
	}
	else
	{
		throw stdext::exception("Unsupported Bindable Kind {0}", *kind);
	}
	auto res = instance<ZSocket>::make();

	res->_socket = zmq_socket(_ctx, zmq_type);
	auto err = zmq_connect(res->_socket, uri->c_str());

	if (err == -1) throw stdext::exception("{0}", zmq_strerror(zmq_errno()));

	return res;
}
