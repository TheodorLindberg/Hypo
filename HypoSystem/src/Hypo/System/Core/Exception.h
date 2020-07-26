#pragma once
#include <Hypo/Core.h>
#include <Hypo/System/Exports.h>
#include <string>

namespace Hypo
{

	class HYPO_SYSTEM_API Exception : public std::exception
	{
	public:
		Exception(const std::string& msg, int code = 0);

		Exception(const std::string& msg, const std::string& arg, int code = 0);

		Exception(const std::string& msg, const Exception& nested, int code = 0);

		Exception(const Exception& exc);

		~Exception() throw();

		Exception& operator = (const Exception& exc);

		virtual const char* Name() const throw();

		virtual const char* ClassName() const throw();

		virtual const char* What() const throw();

		const Exception* Nested() const;

		const std::string& Message() const;

		int Code() const;

		std::string DisplayText() const;

		virtual Exception* Clone() const;

		virtual void Rethrow() const;

	protected:
		Exception(int code = 0);

		void Message(const std::string& msg);

		void ExtendedMessage(const std::string& arg);

	private:
		std::string _msg;
		Exception* _pNested;
		int			_code;
	};

	inline const Exception* Exception::Nested() const
	{
		return _pNested;
	}


	inline const std::string& Exception::Message() const
	{
		return _msg;
	}


	inline void Exception::Message(const std::string& msg)
	{
		_msg = msg;
	}


	inline int Exception::Code() const
	{
		return _code;
	}

#define HYPO_DECLARE_EXCEPTION_CODE(API, CLS, BASE, CODE) \
	class API CLS: public BASE														\
	{																				\
	public:																			\
		CLS(int code = CODE);														\
		CLS(const std::string& msg, int code = CODE);								\
		CLS(const std::string& msg, const std::string& arg, int code = CODE);		\
		CLS(const std::string& msg, const Hypo::Exception& exc, int code = CODE);	\
		CLS(const CLS& exc);														\
		~CLS() throw();																\
		CLS& operator = (const CLS& exc);											\
		const char* Name() const throw();											\
		const char* ClassName() const throw();										\
		Hypo::Exception* Clone() const;												\
		void Rethrow() const;														\
	};

#define HYPO_DECLARE_EXCEPTION(API, CLS, BASE) \
	HYPO_DECLARE_EXCEPTION_CODE(API, CLS, BASE, 0)

#define HYPO_IMPLEMENT_EXCEPTION(CLS, BASE, NAME)													\
	CLS::CLS(int code): BASE(code)																	\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, int code): BASE(msg, code)										\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, const std::string& arg, int code): BASE(msg, arg, code)		\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, const Hypo::Exception& exc, int code): BASE(msg, exc, code)	\
	{																								\
	}																								\
	CLS::CLS(const CLS& exc): BASE(exc)																\
	{																								\
	}																								\
	CLS::~CLS() throw()																				\
	{																								\
	}																								\
	CLS& CLS::operator = (const CLS& exc)															\
	{																								\
		BASE::operator = (exc);																		\
		return *this;																				\
	}																								\
	const char* CLS::Name() const throw()															\
	{																								\
		return NAME;																				\
	}																								\
	const char* CLS::ClassName() const throw()														\
	{																								\
		return typeid(*this).name();																\
	}																								\
	Hypo::Exception* CLS::Clone() const																\
	{																								\
		return new CLS(*this);																		\
	}																								\
	void CLS::Rethrow() const																		\
	{																								\
		throw *this;																				\
	}


	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, LogicException, Exception)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, AssertionViolationException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, NullPointerException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, NullValueException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, BugcheckException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, InvalidArgumentException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, NotImplementedException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, RangeException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, IllegalStateException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, InvalidAccessException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, SignalException, LogicException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, UnhandledException, LogicException)
						  
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, RuntimeException, Exception)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, NotFoundException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, ExistsException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, TimeoutException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, SystemException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, RegularExpressionException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, LibraryLoadException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, LibraryAlreadyLoadedException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, NoThreadAvailableException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, PropertyNotSupportedException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, PoolOverflowException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, NoPermissionException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, OutOfMemoryException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, DataException, RuntimeException)
						   
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, DataFormatException, DataException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, SyntaxException, DataException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, CircularReferenceException, DataException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, PathSyntaxException, SyntaxException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, IOException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, ProtocolException, IOException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, FileException, IOException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, FileExistsException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, FileNotFoundException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, PathNotFoundException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, FileReadOnlyException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, FileAccessDeniedException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, CreateFileException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, OpenFileException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, WriteFileException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, ReadFileException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, DirectoryNotEmptyException, FileException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, UnknownURISchemeException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, TooManyURIRedirectsException, RuntimeException)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, URISyntaxException, SyntaxException)
						   
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, ApplicationException, Exception)
	HYPO_DECLARE_EXCEPTION(HYPO_SYSTEM_API, BadCastException, RuntimeException)
}