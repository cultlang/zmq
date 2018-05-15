#include "zmq/common.h"
#include "all.h"

using namespace craft;
using namespace craft::types;
using namespace cultlang::zmq;

CRAFT_DEFINE(ZMessage)
{
	/*_.use<SObjectManipulation>().byConfiguring<ObjectManipulater>()
	->withMethod("get", &ZMessage::get)
	->withMethod("fill", &ZMessage::fill);*/
	_.defaults();
}

ZMessage::ZMessage()
{
	_msg = new zmq_msg_t;
	memset(_msg, 0, sizeof(zmq_msg_t));
}

ZMessage::~ZMessage()
{
	zmq_msg_t* p = (zmq_msg_t*)_msg;
	zmq_msg_close(p);
	delete _msg;
}

instance<std::string> ZMessage::get()
{
	zmq_msg_t* p = (zmq_msg_t*)_msg;
	size_t s = zmq_msg_size(p);
	void* d = zmq_msg_data(p);

	auto res = instance<std::string>::make();
	res->resize(s);

	std::memcpy(const_cast<char*>(res->data()), d, s);
	return res;
}


void ZMessage::fill(instance<std::string> s)
{
	_owned = s;
	zmq_msg_t* p = (zmq_msg_t*)_msg;
	zmq_msg_init_data(p, const_cast<char*>(s->data()), s->size() + 1, nullptr, nullptr);
}