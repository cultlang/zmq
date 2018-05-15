#pragma once
#include "zmq/common.h"
#include "all.h"

namespace cultlang {
namespace zmq
{
	class ZContext
		: public virtual craft::types::Object
	{
		CULTLANG_ZMQ_EXPORTED CRAFT_OBJECT_DECLARE(cultlang::zmq::ZContext)
	private:
		void* _ctx;

	public:
		CULTLANG_ZMQ_EXPORTED ZContext();
		~ZContext();


		CULTLANG_ZMQ_EXPORTED craft::instance<ZSocket> bind(craft::instance<std::string> kind, craft::instance<int64_t> port);
		CULTLANG_ZMQ_EXPORTED craft::instance<ZSocket> connect(craft::instance<std::string> kind, craft::instance<std::string> uri);
	};
}}