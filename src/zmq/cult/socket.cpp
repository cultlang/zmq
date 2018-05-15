#include "zmq/common.h"
#include "all.h"

using namespace craft;
using namespace craft::types;
using namespace cultlang::zmq;




CRAFT_DEFINE(ZSocket)
{
	/*_.use<SObjectManipulation>().byConfiguring<ObjectManipulater>()
	->withMethod("send", &ZSocket::send)
	->withMethod("recv", &ZSocket::recv);*/
	_.defaults();
}


ZSocket::ZSocket()
{
	_socket = nullptr;
}

ZSocket::~ZSocket()
{
	if (_socket)
	{
		zmq_close(_socket);
	}
}

void ZSocket::send(instance<ZMessage> s, instance<bool> more)
{
	auto flags = (*more) ? ZMQ_SNDMORE : 0;
	auto errval = zmq_sendmsg(_socket, (zmq_msg_t*)s->_msg, flags);
	if (errval == -1) throw stdext::exception("{0}", zmq_strerror(zmq_errno()));
}

instance<ZMessage> ZSocket::recv()
{
	auto res = instance<ZMessage>::make();
	zmq_msg_init((zmq_msg_t*)res->_msg);

	auto errval = zmq_msg_recv((zmq_msg_t*)res->_msg, _socket, 0);

	if (errval == -1) throw stdext::exception("{0}", zmq_strerror(zmq_errno()));

	return res;
}

instance<bool> ZSocket::recv_more()
{
	int more;
	size_t more_size = sizeof(more);

	auto rc = zmq_getsockopt(socket, ZMQ_RCVMORE, &more, &more_size);
	return instance<bool>::make((more != 0));
}