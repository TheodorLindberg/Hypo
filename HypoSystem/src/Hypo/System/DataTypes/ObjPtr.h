#pragma once
#include "Hypo/System/Exports.h"
#include "ObjPtrMemoryManager.h"
#include <atomic>
#include <iostream>

namespace Hypo
{
	template<typename T>
	inline T Increment(T* obj)
	{
		return ++(*obj);
	}
	template<typename T>
	inline T Decrement(T* obj)
	{
		return --(*obj);
	}
	template<typename T>

	class  ObjPtr
	{
	private:
		T* data = nullptr;
		RefCounter* counter = nullptr;
	public:
		using Type = T;
		ObjPtr()
			:data(nullptr)
		{
			counter = ObjPtrMemoryManager::Get().Allocate();
			(*counter) = 1;
		}
		ObjPtr(T* data)
			: data(data)
		{
			counter = ObjPtrMemoryManager::Get().Allocate();
			(*counter) = 1;
		}
		ObjPtr(const ObjPtr<T>& ptr)
			: data(ptr.data), counter(ptr.counter)
		{
			Increment(counter);
		}
		~ObjPtr()
		{
			if (Decrement(counter) == 0)
			{
				delete data;
				data = nullptr;
				ObjPtrMemoryManager::Get().Deallocate(counter);
			}
		}
		ObjPtr<T>& operator = (const ObjPtr<T>& ptr)
		{
			if (this != &ptr)
			{
				if (Decrement(counter) == 0)
				{
					delete data;
					data = nullptr;
					ObjPtrMemoryManager::Get().Deallocate(counter);
				}

				data = ptr.data;
				counter = ptr.counter;
				Increment(counter);
			}
			return *this;
		}

		bool Reset()
		{
			if (Decrement(counter) == 0)
			{
				delete data;
				data = nullptr;
				ObjPtrMemoryManager::Get().Deallocate(counter);
				return true;
			}
			return false;
		}
		
		T* operator->() const
		{
				return data;
		}
		T* Get() const
		{
			return data;
		}
		T& GetRef() const
		{
			return *data;
		}
		operator T& ()
		{
			return *data;
		}
		T& operator*()
		{
			return *data;
		}
		template<typename T2>
		T2* Cast() const
		{
			return static_cast<T2*>(data);
		}
		template<typename T2>
		T2& CastToRef() const
		{
			return *static_cast<T2*>(data);
		}
		operator bool() const
		{
			return data != nullptr;
		}
		bool operator!=(const ObjPtr<T>& other) const
		{
			return !(*this == other);
		}
		bool operator ==(const ObjPtr<T>& other) const
		{
			return data == other.data;
		}
	};

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


	class HYPO_SYSTEM_API RefCountedObject
		/// A base class for objects that employ
		/// reference counting based garbage collection.
		///
		/// Reference-counted objects inhibit construction
		/// by copying and assignment.
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
