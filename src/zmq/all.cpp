#include "zmq/common.h"

#include "all.h"

#include "lisp/library/system/prelude.h"
#include "lisp/semantics/cult/calling.h"

#include "cult/all.h"

using namespace craft;
using namespace craft::lisp;
using namespace craft::types;
using namespace cultlang::zmq;



#define lMM semantics->builtin_implementMultiMethod
#define zMq "zmq"


instance<Module> cultlang::zmq::make_zmq_bindings(instance<lisp::Namespace> ns, instance<> loader)
{
	auto ret = instance<Module>::make(ns, loader);
	auto sem = instance<CultSemantics>::make(ret);
	ret->builtin_setSemantics(sem);

	auto semantics = ret->require<CultSemantics>();
	
	lMM(zMq, []() { return instance<ZContext>::make(); });

	lMM(zMq, [](instance<ZContext> ctx, instance<std::string> kind, instance<int64_t> port) -> instance<ZSocket>
	{
		return ctx->bind(kind, port);
	});

	lMM(zMq"/connect", [](instance<ZContext> ctx, instance<std::string> kind, instance<std::string> address) -> instance<ZSocket>
	{
		return ctx->connect(kind, address);
	});

	lMM(zMq"/msg",[](instance<std::string> msg) -> instance<ZMessage>
	{
		auto res = instance<ZMessage>::make();
		res->fill(msg);
		return res;
	});

	lMM(zMq"/msg", [](instance<ZMessage> msg) -> instance<std::string>
	{
		return msg->get();
	});

	lMM(zMq"/send",
		[](instance<ZSocket> socket, instance<ZMessage> msg)
	{
		socket->send(msg, instance<bool>::make(false));
	});

	lMM(zMq"/send",
		[](instance<ZSocket> socket, instance<ZMessage> msg, instance<bool> more)
	{
		socket->send(msg, more);
	});


	lMM(zMq"/recv",
		[](instance<ZSocket> socket) -> instance<ZMessage>
	{
		return socket->recv();
	});

	lMM(zMq"/more",
		[](instance<ZSocket> socket) -> instance<bool>
	{
		return socket->recv_more();
	});
	return ret;
}

BuiltinModuleDescription cultlang::zmq::BuiltinZmq("cult/zmq", cultlang::zmq::make_zmq_bindings);


#include "types/dll_entry.inc"
