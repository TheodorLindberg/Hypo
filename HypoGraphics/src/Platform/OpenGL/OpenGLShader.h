#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/Graphics/Shader/Shader.h"

namespace Hypo
{
	class HYPO_GRAPHICS_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const ShaderData& shaderData);
		~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;

		uInt32 GetRendererID() const { return m_RendererID; };

		void SetUniform1f(const std::string& name, float v0) override;
		void SetUniform2f(const std::string& name, float v0, float v1) override;
		void SetUniform3f(const std::string& name, float v0, float v1, float v2) override;
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;
		void SetUniform1i(const std::string& name, int v0) override;
		void SetUniform2i(const std::string& name, int v0, int v1) override;
		void SetUniform3i(const std::string& name, int v0, int v1, int v2) override;
		void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3) override;

		void SetUniform2f(const std::string& name, Vec2F vec) override;
		void SetUniform3f(const std::string& name, Vec3F vec) override;
		void SetUniform4f(const std::string& name, Vec4F vec) override;

		void SetUniformMat3f(const std::string& name, glm::mat3& mat3) override;
		void SetUniformMat4f(const std::string& name, glm::mat4& mat4) override;

		void SetAttributeLayout(AttributeLayout& layout) override;


		bool CompatibleWithVertexArray(ObjPtr<class VertexArray>& vertexArray);

		void SetAttribute(const BufferElement& element, int stride, bool perInstance = false);

	private:
		static constexpr uInt8 ATTRIBUTE_MAX_LENGTH = 40;
		static constexpr uInt8 UNIFORM_MAX_LENGTH = 40;
		int GetUniformLocation(const std::string& name);
		int GetAttributeLocation(const std::string& name);

		int GetUniformType(const std::string& name);
		int GetAttributeType(const std::string& name);


		uInt32 CompileShaderProgram(const std::string& src, int shaderType);
		void LinkShader(std::vector<uInt32> shaders);
		void SetupUniformsAndAttributesLocation();


	private:
		std::unordered_map<std::string, std::pair<int,int>> m_UniformLocation;
		std::unordered_map<std::string, std::pair<int, int>> m_AttributeLocation;
		uInt32 m_RendererID;
	};

}
