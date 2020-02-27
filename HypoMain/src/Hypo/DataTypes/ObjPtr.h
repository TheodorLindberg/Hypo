#pragma once

#include "Core.h"
#include "ObjPtrMemoryManager.h"
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

	class ObjPtr
	{
	private:
		T* data;
		RefCounter* counter;
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
}