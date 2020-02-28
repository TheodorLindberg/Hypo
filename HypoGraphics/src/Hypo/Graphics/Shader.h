#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "Hypo/Graphics/Exports.h"

#include <glm/glm.hpp>

#include "Hypo/Graphics/BufferLayout.h"
#include <unordered_map>

namespace Hypo
{

	enum class ShaderType
	{
		Vertex = 0,
		Fragment,
		Geometry 
	};

	struct EnumClassHash
	{
		template <typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
	};

	class ShaderData
	{
	public:
		using ShaderSources = std::unordered_map<ShaderType, std::string, EnumClassHash>;
		ShaderData() = default;
		ShaderData(ShaderSources shaders, std::string name);

		bool HasShader(ShaderType type) const { return m_Shaders.find(type) != m_Shaders.end(); }
		const std::string& GetShader(ShaderType type) const;
		const std::string& GetName() const { return m_Name; }
	private:
		std::string m_Name;
		ShaderSources m_Shaders;
	};
	
	class Shader
	{
	public:
		using Ptr = Hypo::ObjPtr<Shader>;

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetUniform1f(const std::string& name, float v0) = 0;
		virtual void SetUniform2f(const std::string& name, float v0, float v1) = 0;
		virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) = 0;
		virtual void SetUniform4f(const std::string& name, float v0, float v1, float v3, float v4) = 0;

		virtual void SetUniform1i(const std::string& name, int v0) = 0;
		virtual void SetUniform2i(const std::string& name, int v0, int v1) = 0;
		virtual void SetUniform3i(const std::string& name, int v0, int v1, int v2) = 0;
		virtual void SetUniform4i(const std::string& name, int v0, int v1, int v3, int v4) = 0;

		virtual void SetUniform2f(const std::string& name, Hypo::Vec2F vec) = 0;
		virtual void SetUniform3f(const std::string& name, Hypo::Vec3F vec) = 0;
		virtual void SetUniform4f(const std::string& name, Hypo::Vec4F vec) = 0;

		virtual void SetUniformMat3f(const std::string& name, glm::mat3& mat3) = 0;
		virtual void SetUniformMat4f(const std::string& name, glm::mat4& mat4) = 0;

		virtual void SetAttributeLayout(Hypo::AttributeLayout& layout) = 0;


		static Ptr Create(const ShaderData& data);
	};
}
