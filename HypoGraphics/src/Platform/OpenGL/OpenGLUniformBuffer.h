#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"
#include "Hypo/Graphics/Shader/UniformBuffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Hypo
{
	class HYPO_GRAPHICS_API OpenGLUniformBuffer : public UniformBuffer
	{
	private:
		UniformBinder::Ptr m_Binder;
		OpenGLBuffer m_Buffer;

	public:
		OpenGLUniformBuffer(UniformBinder::Ptr& binder);
		~OpenGLUniformBuffer();

		OpenGLBuffer& GetBuffer() { return m_Buffer; }

		const std::string& GetBinderName() override;
		const UniformBinder::Ptr GetBinderForBuffer() override { return m_Binder; }

		//void ClearBuffer() override;

		bool Set(const char* name, int value) override;

		bool Set(const char* name, int value1, int value2) override;

		bool Set(const char* name, int value1, int value2, int value3) override;

		bool Set(const char* name, int value1, int value2, int value3, int value4) override;

		bool Set(const char* name, Vec2I value) override;

		bool Set(const char* name, Vec3I& value) override;

		bool Set(const char* name, Vec4I& value) override;

		bool Set(const char* name, float value) override;

		bool Set(const char* name, float value1, float value2) override;

		bool Set(const char* name, float value1, float value2, float value3) override;

		bool Set(const char* name, float value1, float value2, float value3, float value4) override;

		bool Set(const char* name, Vec2F value) override;

		bool Set(const char* name, Vec3F& value) override;

		bool Set(const char* name, Vec4F& value) override;

		bool Set(const char* name, bool value) override;

		bool Set(const char* name, const glm::mat3& value) override;

		bool Set(const char* name, const glm::mat4& value) override;

		bool Set(const char* name, Byte* data, int size) override;

		//////////////////////////////////////////////
		//// Array Set Functions
		//////////////////////////////////////////////
		bool SetArray(const char* name, int value, int index) override;

		bool SetArray(const char* name, int value1, int value2, int index) override;

		bool SetArray(const char* name, int value1, int value2, int value3, int index) override;

		bool SetArray(const char* name, int value1, int value2, int value3, int value4, int index) override;

		bool SetArray(const char* name, Vec2I value, int index) override;

		bool SetArray(const char* name, Vec3I& value, int index) override;

		bool SetArray(const char* name, Vec4I& value, int index) override;

		bool SetArray(const char* name, float value, int index) override;

		bool SetArray(const char* name, float value1, float value2, int index) override;

		bool SetArray(const char* name, float value1, float value2, float value3, int index) override;

		bool SetArray(const char* name, float value1, float value2, float value3, float value4, int index) override;

		bool SetArray(const char* name, Vec2F value, int index) override;

		bool SetArray(const char* name, Vec3F& value, int index) override;

		bool SetArray(const char* name, Vec4F& value, int index) override;

		bool SetArray(const char* name, bool value, int index) override;

		bool SetArray(const char* name, const glm::mat3& value, int index) override;

		bool SetArray(const char* name, const glm::mat4& value, int index) override;

		bool SetArray(const char* name, Byte* data, int size, int index) override;


	};
}
