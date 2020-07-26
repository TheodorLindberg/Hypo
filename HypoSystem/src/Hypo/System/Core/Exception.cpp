#include "systempch.h"
#include "Exception.h"

namespace Hypo
{

	Exception::Exception(int code) : _pNested(0), _code(code)
	{
	}


	Exception::Exception(const std::string& msg, int code) : _msg(msg), _pNested(0), _code(code)
	{
	}


	Exception::Exception(const std::string& msg, const std::string& arg, int code) : _msg(msg), _pNested(0), _code(code)
	{
		if (!arg.empty())
		{
			_msg.append(": ");
			_msg.append(arg);
		}
	}


	Exception::Exception(const std::string& msg, const Exception& nested, int code) : _msg(msg), _pNested(nested.Clone()), _code(code)
	{
	}


	Exception::Exception(const Exception& exc) :
		std::exception(exc),
		_msg(exc._msg),
		_code(exc._code)
	{
		_pNested = exc._pNested ? exc._pNested->Clone() : 0;
	}


	Exception::~Exception() throw()
	{
		delete _pNested;
	}


	Exception& Exception::operator = (const Exception& exc)
	{
		if (&exc != this)
		{
			Exception* newPNested = exc._pNested ? exc._pNested->Clone() : 0;
			delete _pNested;
			_msg = exc._msg;
			_pNested = newPNested;
			_code = exc._code;
		}
		return *this;
	}


	const char* Exception::Name() const throw()
	{
		return "Exception";
	}


	const char* Exception::ClassName() const throw()
	{
		return typeid(*this).name();
	}


	const char* Exception::What() const throw()
	{
		return Name();
	}


	std::string Exception::DisplayText() const
	{
		std::string txt = Name();
		if (!_msg.empty())
		{
			txt.append(": ");
			txt.append(_msg);
		}
		return txt;
	}


	void Exception::ExtendedMessage(const std::string& arg)
	{
		if (!arg.empty())
		{
			if (!_msg.empty()) _msg.append(": ");
			_msg.append(arg);
		}
	}


	Exception* Exception::Clone() const
	{
		return new Exception(*this);
	}


	void Exception::Rethrow() const
	{
		throw *this;
	}

	HYPO_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
	HYPO_IMPLEMENT_EXCEPTION(AssertionViolationException, LogicException, "Assertion violation")
	HYPO_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
	HYPO_IMPLEMENT_EXCEPTION(NullValueException, LogicException, "Null value")
	HYPO_IMPLEMENT_EXCEPTION(BugcheckException, LogicException, "Bugcheck")
	HYPO_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException, "Invalid argument")
	HYPO_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException, "Not implemented")
	HYPO_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")
	HYPO_IMPLEMENT_EXCEPTION(IllegalStateException, LogicException, "Illegal state")
	HYPO_IMPLEMENT_EXCEPTION(InvalidAccessException, LogicException, "Invalid access")
	HYPO_IMPLEMENT_EXCEPTION(SignalException, LogicException, "Signal received")
	HYPO_IMPLEMENT_EXCEPTION(UnhandledException, LogicException, "Unhandled exception")

	HYPO_IMPLEMENT_EXCEPTION(RuntimeException, Exception, "Runtime exception")
	HYPO_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException, "Not found")
	HYPO_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException, "Exists")
	HYPO_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException, "Timeout")
	HYPO_IMPLEMENT_EXCEPTION(SystemException, RuntimeException, "System exception")
	HYPO_IMPLEMENT_EXCEPTION(RegularExpressionException, RuntimeException, "Error in regular expression")
	HYPO_IMPLEMENT_EXCEPTION(LibraryLoadException, RuntimeException, "Cannot load library")
	HYPO_IMPLEMENT_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException, "Library already loaded")
	HYPO_IMPLEMENT_EXCEPTION(NoThreadAvailableException, RuntimeException, "No thread available")
	HYPO_IMPLEMENT_EXCEPTION(PropertyNotSupportedException, RuntimeException, "Property not supported")
	HYPO_IMPLEMENT_EXCEPTION(PoolOverflowException, RuntimeException, "Pool overflow")
	HYPO_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException, "No permission")
	HYPO_IMPLEMENT_EXCEPTION(OutOfMemoryException, RuntimeException, "Out of memory")
	HYPO_IMPLEMENT_EXCEPTION(DataException, RuntimeException, "Data error")

	HYPO_IMPLEMENT_EXCEPTION(DataFormatException, DataException, "Bad data format")
	HYPO_IMPLEMENT_EXCEPTION(SyntaxException, DataException, "Syntax error")
	HYPO_IMPLEMENT_EXCEPTION(CircularReferenceException, DataException, "Circular reference")
	HYPO_IMPLEMENT_EXCEPTION(PathSyntaxException, SyntaxException, "Bad path syntax")
	HYPO_IMPLEMENT_EXCEPTION(IOException, RuntimeException, "I/O error")
	HYPO_IMPLEMENT_EXCEPTION(ProtocolException, IOException, "Protocol error")
	HYPO_IMPLEMENT_EXCEPTION(FileException, IOException, "File access error")
	HYPO_IMPLEMENT_EXCEPTION(FileExistsException, FileException, "File exists")
	HYPO_IMPLEMENT_EXCEPTION(FileNotFoundException, FileException, "File not found")
	HYPO_IMPLEMENT_EXCEPTION(PathNotFoundException, FileException, "Path not found")
	HYPO_IMPLEMENT_EXCEPTION(FileReadOnlyException, FileException, "File is read-only")
	HYPO_IMPLEMENT_EXCEPTION(FileAccessDeniedException, FileException, "Access to file denied")
	HYPO_IMPLEMENT_EXCEPTION(CreateFileException, FileException, "Cannot create file")
	HYPO_IMPLEMENT_EXCEPTION(OpenFileException, FileException, "Cannot open file")
	HYPO_IMPLEMENT_EXCEPTION(WriteFileException, FileException, "Cannot write file")
	HYPO_IMPLEMENT_EXCEPTION(ReadFileException, FileException, "Cannot read file")
	HYPO_IMPLEMENT_EXCEPTION(DirectoryNotEmptyException, FileException, "Directory not empty")
	HYPO_IMPLEMENT_EXCEPTION(UnknownURISchemeException, RuntimeException, "Unknown URI scheme")
	HYPO_IMPLEMENT_EXCEPTION(TooManyURIRedirectsException, RuntimeException, "Too many URI redirects")
	HYPO_IMPLEMENT_EXCEPTION(URISyntaxException, SyntaxException, "Bad URI syntax")

	HYPO_IMPLEMENT_EXCEPTION(ApplicationException, Exception, "Application exception")
	HYPO_IMPLEMENT_EXCEPTION(BadCastException, RuntimeException, "Bad cast exception")
}