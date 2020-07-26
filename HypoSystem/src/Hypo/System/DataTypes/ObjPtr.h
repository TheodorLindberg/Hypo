#pragma once
#include <iostream>
#include <atomic>
#include <mutex>
namespace Hypo
{
	class ReferenceCounter
		/// Simple ReferenceCounter object, does not delete itself when count reaches 0
	{
	public:
		ReferenceCounter() : _cnt(1)
		{
		}

		void duplicate()
		{
			_mutex.lock();
			++_cnt;
			_mutex.unlock();
		}

		int release()
		{
			_mutex.lock();
			 --_cnt;
			_mutex.unlock();
			return _cnt;
		}

	private:
		std::mutex _mutex;
		int _cnt;
	};

	class Deleter
		/// Deleter base
	{
	public:
		virtual ~Deleter() {}
		virtual void operator()(void* p) = 0;
	};

	template <class T>
	class DefaultDeleter : public Deleter
		/// Default Deleter 
	{
	public:
		~DefaultDeleter() {}
		virtual void operator()(void* p)
		{
			delete static_cast<T*>(p);
		}
	};

	template <class T, class D>
	class CustomDeleter : public Deleter
		/// ShardPtrDeleter accepts both the object pointer and concrete deleter.
		/// The deleter can be function pointer or even functor which provide "operator ()".
		/// note the deleter shall be default constructible and its constructor
		/// shall never throw exceptions.
	{
	public:

		CustomDeleter(D deleter) : _pDeleter(deleter) {}
		virtual ~CustomDeleter() {}
		virtual void operator()(void* p)
		{
			(this->_pDeleter)(static_cast<T*>(p));
		}

	private:
		D  _pDeleter;
	};

	template<class T>
	struct ObjPtrTraits
	{
		typedef T& reference;
	};

	template<>
	struct ObjPtrTraits<void>
	{
		typedef void reference;
	};

	template <class C, class RC = ReferenceCounter>
	class ObjPtr
		/// ObjPtr is a "smart" pointer for classes implementing
		/// reference counting based garbage collection.
		/// ObjPtr is thus similar to AutoPtr. Unlike the
		/// AutoPtr template, which can only be used with
		/// classes that support reference counting, ObjPtr
		/// can be used with any class. For this to work, a
		/// ObjPtr manages a reference count for the object
		/// it manages.
		/// 
		/// ObjPtr works in the following way:
		/// If an ObjPtr is Assigned an ordinary pointer to
		/// an object (via the constructor or the Assignment operator),
		/// it takes ownership of the object and the object's reference 
		/// count is initialized to one.
		/// If the ObjPtr is Assigned another ObjPtr, the
		/// object's reference count is incremented by one.
		/// The destructor of ObjPtr decrements the object's
		/// reference count by one and deletes the object if the
		/// reference count reaches zero.
		/// ObjPtr supports dereferencing with both the ->
		/// and the * operator. An attempt to dereference a null
		/// ObjPtr results in a NullPointerException being thrown.
		/// ObjPtr also implements all relational operators and
		/// a cast operator in case dynamic casting of the encapsulated data types
		/// is required.
		///
	{

		typedef typename ObjPtrTraits<C>::reference reference;

	public:
		ObjPtr() : _pCounter(new RC), _ptr(0),
			_pDeleter(new DefaultDeleter<C>())
			/// Constructs an empty ObjPtr. Throw std::bad_alloc if construction fails.
		{
		}

		ObjPtr(C* ptr) : _pCounter(0), _ptr(ptr), _pDeleter(0)
			/// Constructs ObjPtr that owns pointer ptr.
			/// Here ptr must be convertible to C*, and type A shall be a complete type. Also ptr 
			/// should be deletable and no exception shall be thrown.
			/// If the construction fails, the incoming pointer ptr will be deleted, and 
			/// Poco::OutOfMemoryException will be thrown.
		{
			try
			{
				_pCounter = new RC;
				_pDeleter = new DefaultDeleter<C>();
			}
			catch (std::bad_alloc) {
				delete _pCounter;
				delete _pDeleter;
				delete ptr;
				throw "ObjPtr construction failed: Out of memory.";
			}
		}
		template<typename A>
		ObjPtr(A* ptr) : _pCounter(0), _ptr(ptr), _pDeleter(0)
			/// Constructs ObjPtr that owns pointer ptr.
			/// Here ptr must be convertible to C*, and type A shall be a complete type. Also ptr 
			/// should be deletable and no exception shall be thrown.
			/// If the construction fails, the incoming pointer ptr will be deleted, and 
			/// Poco::OutOfMemoryException will be thrown.
		{
			try
			{
				_pCounter = new RC;
				_pDeleter = new DefaultDeleter<A>();
			}
			catch (std::bad_alloc) {
				delete _pCounter;
				delete _pDeleter;
				delete ptr;
				throw "ObjPtr construction failed: Out of memory.";
			}
		}

		template <typename A, typename D>
		ObjPtr(A* ptr, D deleter) : _pCounter(0), _ptr(ptr), _pDeleter(0)
			/// Constructs ObjPtr that owns pointer ptr and deleter.
			/// Here ptr must be convertible to C*, and type A shall be a complete type. Also ptr 
			/// should be deletable and no exception shall be thrown.
			/// The deleter's constructor must not throw any exception.
			/// If the construction fails, the incoming pointer ptr will be deleted by the
			/// provided deleter, and Poco::OutOfMemoryException will be thrown.
		{
			try
			{
				_pCounter = new RC;
				_pDeleter = new CustomDeleter<A, D>(deleter);
			}
			catch (std::bad_alloc)
			{
				delete _pCounter;
				delete _pDeleter;
				deleter(ptr);
				throw "ObjPtr construction failed: Out of memory.";
			}
		}

		template <class Other>
		ObjPtr(const ObjPtr<Other, RC>& ptr) : _pCounter(ptr._pCounter), _ptr(const_cast<Other*>(ptr.Get())),
			_pDeleter((Deleter*)(ptr._pDeleter))
			/// Constructs ObjPtr share the ownership with ptr. 
		{
			_pCounter->duplicate();
		}

		ObjPtr(const ObjPtr& ptr) : _pCounter(ptr._pCounter), _ptr(ptr._ptr), _pDeleter(ptr._pDeleter)
			/// Constructs ObjPtr share the ownership with ptr.
		{
			_pCounter->duplicate();
		}

		~ObjPtr()
		{
			release();
		}

		void Reset()
		{
			ObjPtr().Swap(*this);
		}

		template<class A>
		void Reset(A* ptr)
		{
			poco_assert(ptr == 0 || ptr != _ptr);
			ObjPtr(ptr).Swap(*this);
		}

		template<class A, class D>
		void Reset(A* ptr, D deleter)
		{
			poco_assert(ptr == 0 || ptr != _ptr);
			ObjPtr(ptr, deleter).Swap(*this);
		}

		ObjPtr& Assign(C* ptr)
		{
			if (Get() != ptr)
			{
				RC* pTmp = new RC;
				release();
				_pCounter = pTmp;
				_ptr = ptr;
				_pDeleter = new DefaultDeleter<C>();
			}
			return *this;
		}

		ObjPtr& Assign(const ObjPtr& ptr)
		{
			if (&ptr != this)
			{
				ObjPtr tmp(ptr);
				Swap(tmp);
			}
			return *this;
		}

		template <class Other>
		ObjPtr& Assign(const ObjPtr<Other, RC>& ptr)
		{
			if (ptr.Get() != _ptr)
			{
				ObjPtr tmp(ptr);
				Swap(tmp);
			}
			return *this;
		}

		ObjPtr& operator = (C* ptr)
		{
			return Assign(ptr);
		}

		ObjPtr& operator = (const ObjPtr& ptr)
		{
			return Assign(ptr);
		}

		template <class Other>
		ObjPtr& operator = (const ObjPtr<Other, RC>& ptr)
		{
			return Assign<Other>(ptr);
		}

		void Swap(ObjPtr& ptr)
		{
			std::swap(_ptr, ptr._ptr);
			std::swap(_pCounter, ptr._pCounter);
			std::swap(_pDeleter, ptr._pDeleter);
		}

		template <class Other>
		Other* Cast()
		{
			return reinterpret_cast<Other*>(_ptr);
		}
		template <class Other>
		Other& CastToRef()
		{
			return *reinterpret_cast<Other*>(_ptr);
		}

		C* operator -> ()
		{
			return deref();
		}

		const C* operator -> () const
		{
			return deref();
		}

		reference operator * ()
		{
			return *deref();
		}

		C* Get()
		{
			return _ptr;
		}

		const C* Get() const
		{
			return _ptr;
		}
		const C& GetRef() const
		{
			return *_ptr;
		}
		operator C* ()
		{
			return _ptr;
		}

		operator const C* () const
		{
			return _ptr;
		}

		bool operator ! () const
		{
			return _ptr == 0;
		}

		bool IsNull() const
		{
			return _ptr == 0;
		}

		bool operator == (const ObjPtr& ptr) const
		{
			return Get() == ptr.Get();
		}

		bool operator == (const C* ptr) const
		{
			return Get() == ptr;
		}

		bool operator == (C* ptr) const
		{
			return Get() == ptr;
		}

		bool operator != (const ObjPtr& ptr) const
		{
			return Get() != ptr.Get();
		}

		bool operator != (const C* ptr) const
		{
			return Get() != ptr;
		}

		bool operator != (C* ptr) const
		{
			return Get() != ptr;
		}

		bool operator < (const ObjPtr& ptr) const
		{
			return Get() < ptr.Get();
		}

		bool operator < (const C* ptr) const
		{
			return Get() < ptr;
		}

		bool operator < (C* ptr) const
		{
			return Get() < ptr;
		}

		bool operator <= (const ObjPtr& ptr) const
		{
			return Get() <= ptr.Get();
		}

		bool operator <= (const C* ptr) const
		{
			return Get() <= ptr;
		}

		bool operator <= (C* ptr) const
		{
			return Get() <= ptr;
		}

		bool operator > (const ObjPtr& ptr) const
		{
			return Get() > ptr.Get();
		}

		bool operator > (const C* ptr) const
		{
			return Get() > ptr;
		}

		bool operator > (C* ptr) const
		{
			return Get() > ptr;
		}

		bool operator >= (const ObjPtr& ptr) const
		{
			return Get() >= ptr.Get();
		}

		bool operator >= (const C* ptr) const
		{
			return Get() >= ptr;
		}

		bool operator >= (C* ptr) const
		{
			return Get() >= ptr;
		}

	private:

		C* deref() const
		{
			if (!_ptr)
				throw "Nullptr";

			return _ptr;
		}

		void release()
		{
			int i = _pCounter->release();
			if (i == 0)
			{
				if (_pDeleter) {
					(*_pDeleter)(_ptr);
					_ptr = 0;
					delete _pDeleter;
					_pDeleter = 0;
				}
				delete _pCounter;
				_pCounter = 0;
			}
		}

		template<class A>
		ObjPtr(RC* pCounter, A* ptr) : _pCounter(pCounter), _ptr(ptr),
			_pDeleter(new DefaultDeleter<A>())
			/// for cast operation
		{
			poco_assert_dbg(_pCounter);
			_pCounter->duplicate();
		}

	private:

		RC* _pCounter;
		C* _ptr;
		Deleter* _pDeleter;

		template <class OtherC, class OtherRC> friend class ObjPtr;
	};


	template <class C, class RC>
	inline void Swap(ObjPtr<C, RC>& p1, ObjPtr<C, RC>& p2)
	{
		p1.Swap(p2);
	}

	template<typename T, class ...Args>
	ObjPtr<T> MakeObj(Args&& ... args)
	{
		return ObjPtr<T>(new T(args...));
	}

	template<typename T>
	ObjPtr<T> MakeNullPtr()
	{
		return ObjPtr<T>();
	}


	class RefCountedObject
		/// A base class for objects that employ
		/// reference counting based garbage collection.
		///
		/// Reference-counted objects inhibit construction
		/// by copying and Assignment.
	{
	public:
		RefCountedObject() = default;
		/// Creates the RefCountedObject.
		/// The initial reference count is one.

		void Duplicate() const;
		/// Increments the object's reference count.

		void Release() const throw();
		/// Decrements the object's reference count
		/// and deletes the object if the count
		/// reaches zero.

		int ReferenceCount() const;
		/// Returns the reference count.

	protected:
		virtual ~RefCountedObject() = default;
		/// Destroys the RefCountedObject.

	private:
		RefCountedObject(const RefCountedObject&);
		RefCountedObject& operator = (const RefCountedObject&);

		mutable std::atomic_int m_Counter = 1;
	};


	//
	// inlines
	//
	inline int RefCountedObject::ReferenceCount() const
	{
		return m_Counter;
	}


	inline void RefCountedObject::Duplicate() const
	{
		++m_Counter;
	}


	inline void RefCountedObject::Release() const throw()
	{
		try
		{
			if (--m_Counter == 0) delete this;
		}
		catch (...)
		{
			std::cout << "ERROR REALEASING" << std::endl;
		}
	}
}
