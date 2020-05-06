#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"

namespace Hypo {

	class HYPO_GRAPHICS_API UniformBuffer
	{
	public:
		using Ptr = ObjPtr<UniformBuffer>;

		static Ptr Create(UniformBinder::Ptr& binder);

		virtual ~UniformBuffer() {}
		virtual const UniformBinder::Ptr GetBinderForBuffer() = 0;
		virtual const std::string& GetBinderName() = 0;

		virtual bool Set(const char* name, int value) = 0;

		virtual bool Set(const char* name, int value1, int value2) = 0;

		virtual bool Set(const char* name, int value1, int value2, int value3) = 0;

		virtual bool Set(const char* name, int value1, int value2, int value3, int value4) = 0;

		virtual bool Set(const char* name, const Vec2I value) = 0;

		virtual bool Set(const char* name, const Vec3I& value) = 0;

		virtual bool Set(const char* name, const Vec4I& value) = 0;

		virtual bool Set(const char* name, float value) = 0;

		virtual bool Set(const char* name, float value1, float value2) = 0;

		virtual bool Set(const char* name, float value1, float value2, float value3) = 0;

		virtual bool Set(const char* name, float value1, float value2, float value3, float value4) = 0;

		virtual bool Set(const char* name, const Vec2F value) = 0;

		virtual bool Set(const char* name, const Vec3F& value) = 0;

		virtual bool Set(const char* name, const Vec4F& value) = 0;

		virtual bool Set(const char* name, bool value) = 0;

		virtual bool Set(const char* name, const glm::mat3& value) = 0;

		virtual bool Set(const char* name, const glm::mat4& value) = 0;

		virtual bool Set(const char* name, Byte* data, int size) = 0;

		//////////////////////////////////////////////
		//// Array Set Functions
		//////////////////////////////////////////////
		virtual bool SetArray(const char* name, int value, int index) = 0;

		virtual bool SetArray(const char* name, int value1, int value2, int index) = 0;

		virtual bool SetArray(const char* name, int value1, int value2, int value3, int index) = 0;

		virtual bool SetArray(const char* name, int value1, int value2, int value3, int value4, int index) = 0;

		virtual bool SetArray(const char* name, Vec2I value, int index) = 0;

		virtual bool SetArray(const char* name, Vec3I& value, int index) = 0;

		virtual bool SetArray(const char* name, Vec4I& value, int index) = 0;

		virtual bool SetArray(const char* name, float value, int index) = 0;

		virtual bool SetArray(const char* name, float value1, float value2, int index) = 0;

		virtual bool SetArray(const char* name, float value1, float value2, float value3, int index) = 0;

		virtual bool SetArray(const char* name, float value1, float value2, float value3, float value4, int index) = 0;

		virtual bool SetArray(const char* name, Vec2F value, int index) = 0;

		virtual bool SetArray(const char* name, Vec3F& value, int index) = 0;

		virtual bool SetArray(const char* name, Vec4F& value, int index) = 0;

		virtual bool SetArray(const char* name, bool value, int index) = 0;

		virtual bool SetArray(const char* name, const glm::mat3& value, int index) = 0;

		virtual bool SetArray(const char* name, const glm::mat4& value, int index) = 0;

		virtual bool SetArray(const char* name, Byte* data, int size, int index) = 0;

	};
}
