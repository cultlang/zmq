#pragma once
#include "zmq/common.h"
#include "all.h"

namespace cultlang {
namespace zmq
{

	class ZMessage
		: public virtual craft::types::Object

	{
		CULTLANG_ZMQ_EXPORTED CRAFT_OBJECT_DECLARE(cultlang::zmq::ZMessage)

	private:
		void* _msg;
		craft::instance<std::string> _owned;
	public:
		CULTLANG_ZMQ_EXPORTED ZMessage();
		CULTLANG_ZMQ_EXPORTED ~ZMessage();


		CULTLANG_ZMQ_EXPORTED craft::instance<std::string> get();
		CULTLANG_ZMQ_EXPORTED void fill(craft::instance<std::string> s);

		friend class ZSocket;
	};
}}