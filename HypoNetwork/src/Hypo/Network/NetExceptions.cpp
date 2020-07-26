#include "networkpch.h"
#include "NetExceptions.h"

namespace Hypo
{

	HYPO_IMPLEMENT_EXCEPTION(NetException, IOException, "Net Exception")
	HYPO_IMPLEMENT_EXCEPTION(InvalidAddressException, NetException, "Invalid address")
	HYPO_IMPLEMENT_EXCEPTION(InvalidSocketException, NetException, "Invalid socket")
	HYPO_IMPLEMENT_EXCEPTION(ServiceNotFoundException, NetException, "Service not found")
	HYPO_IMPLEMENT_EXCEPTION(ConnectionAbortedException, NetException, "Software caused connection abort")
	HYPO_IMPLEMENT_EXCEPTION(ConnectionResetException, NetException, "Connection reset by peer")
	HYPO_IMPLEMENT_EXCEPTION(ConnectionRefusedException, NetException, "Connection refused")
	HYPO_IMPLEMENT_EXCEPTION(DNSException, NetException, "DNS error")
	HYPO_IMPLEMENT_EXCEPTION(HostNotFoundException, DNSException, "Host not found")
	HYPO_IMPLEMENT_EXCEPTION(NoAddressFoundException, DNSException, "No address found")
	HYPO_IMPLEMENT_EXCEPTION(InterfaceNotFoundException, NetException, "Interface not found")
	HYPO_IMPLEMENT_EXCEPTION(NoMessageException, NetException, "No message received")
	HYPO_IMPLEMENT_EXCEPTION(MessageException, NetException, "Malformed message")
	HYPO_IMPLEMENT_EXCEPTION(MultipartException, MessageException, "Malformed multipart message")
	HYPO_IMPLEMENT_EXCEPTION(HTTPException, NetException, "HTTP Exception")
	HYPO_IMPLEMENT_EXCEPTION(NotAuthenticatedException, HTTPException, "No authentication information found")
	HYPO_IMPLEMENT_EXCEPTION(UnsupportedRedirectException, HTTPException, "Unsupported HTTP redirect (protocol change)")
	HYPO_IMPLEMENT_EXCEPTION(FTPException, NetException, "FTP Exception")
	HYPO_IMPLEMENT_EXCEPTION(SMTPException, NetException, "SMTP Exception")
	HYPO_IMPLEMENT_EXCEPTION(POP3Exception, NetException, "POP3 Exception")
	HYPO_IMPLEMENT_EXCEPTION(ICMPException, NetException, "ICMP Exception")
	HYPO_IMPLEMENT_EXCEPTION(NTPException, NetException, "NTP Exception")
	HYPO_IMPLEMENT_EXCEPTION(HTMLFormException, NetException, "HTML Form Exception")
	HYPO_IMPLEMENT_EXCEPTION(WebSocketException, NetException, "WebSocket Exception")
	HYPO_IMPLEMENT_EXCEPTION(UnsupportedFamilyException, NetException, "Unknown or unsupported socket family")
	HYPO_IMPLEMENT_EXCEPTION(AddressFamilyMismatchException, NetException, "Address family mismatch")
}