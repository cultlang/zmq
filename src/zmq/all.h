#pragma once
#include "zmq/common.h"

namespace cultlang {
namespace zmq {
	extern craft::lisp::BuiltinModuleDescription BuiltinZmq;

	CULTLANG_ZMQ_EXPORTED craft::instance<craft::lisp::Module> make_zmq_bindings(craft::instance<craft::lisp::Namespace> ns, craft::instance<> loader);
}}
