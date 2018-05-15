#pragma once
#include "zmq/common.h"
#include "all.h"

namespace cultlang {
namespace zmq
{
	class ZSocket
		: public virtual craft::types::Object
	{
		CULTLANG_ZMQ_EXPORTED CRAFT_OBJECT_DECLARE(cultlang::zmq::ZSocket)
	private:
		void* _socket;

	public:
		CULTLANG_ZMQ_EXPORTED ZSocket();
		~ZSocket();

		CULTLANG_ZMQ_EXPORTED void send(craft::instance<ZMessage> s, craft::instance<bool> more);
		CULTLANG_ZMQ_EXPORTED craft::instance<ZMessage> recv();
		CULTLANG_ZMQ_EXPORTED craft::instance<bool> recv_more();

		friend class ZContext;
	};
}}