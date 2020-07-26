#include "systempch.h"
#include "Hypo/System/Streams/MemoryStream.h"


namespace Hypo {


	MemoryIOS::MemoryIOS(char* pBuffer, std::streamsize bufferSize) :
		_buf(pBuffer, bufferSize)
	{
	}


	MemoryIOS::~MemoryIOS()
	{
	}


	MemoryInputStream::MemoryInputStream(const char* pBuffer, std::streamsize bufferSize) :
		MemoryIOS(const_cast<char*>(pBuffer), bufferSize),
		std::istream(&_buf)
	{
	}


	MemoryInputStream::~MemoryInputStream()
	{
	}


	MemoryOutputStream::MemoryOutputStream(char* pBuffer, std::streamsize bufferSize) :
		MemoryIOS(pBuffer, bufferSize),
		std::ostream(&_buf)
	{
	}


	MemoryOutputStream::~MemoryOutputStream()
	{
	}


} // namespace Poco
