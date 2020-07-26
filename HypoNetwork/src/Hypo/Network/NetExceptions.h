#pragma once
#include <Hypo/Network/Export.h>
#include <Hypo/System/Core/Exception.h>

namespace Hypo
{

	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, NetException, Hypo::IOException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, InvalidAddressException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, InvalidSocketException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, ServiceNotFoundException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, ConnectionAbortedException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, ConnectionResetException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, ConnectionRefusedException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, DNSException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, HostNotFoundException, DNSException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, NoAddressFoundException, DNSException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, InterfaceNotFoundException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, NoMessageException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, MessageException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, MultipartException, MessageException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, HTTPException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, NotAuthenticatedException, HTTPException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, UnsupportedRedirectException, HTTPException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, FTPException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, SMTPException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, POP3Exception, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, ICMPException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, NTPException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, HTMLFormException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, WebSocketException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, UnsupportedFamilyException, NetException)
	HYPO_DECLARE_EXCEPTION(HYPO_NETWORK_API, AddressFamilyMismatchException, NetException)
}