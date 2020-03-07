#include "graphicspch.h"
#include "OpenGLShader.h"
#include "Hypo/System/Util/Log.h"

#include "glad/glad.h"
#include <iostream>

#include "Platform/OpenGL/OpenGLError.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#if HYPO_RUNTIME_CHECK_UNIFORMS == HYPO_ENABLED
#define CHECK_UNIFORM(name, type) if(auto correctType = GetUniformType(name); correctType != type) { HYPO_CORE_ERROR("Uniform {} dosen't match uniform type in shader, uniform type {}, user type {}", name, correctType, type); }
#else
#define CHECK_UNIFORM(x,y)
#endif

namespace Hypo
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		HYPO_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	static ShaderDataType OpenGLToShaderDataType(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT:         return ShaderDataType::Float;
		case GL_FLOAT_VEC2:    return ShaderDataType::Float2;
		case GL_FLOAT_VEC3:    return ShaderDataType::Float3;
		case GL_FLOAT_VEC4:    return ShaderDataType::Float4;
		case GL_FLOAT_MAT3:    return ShaderDataType::Mat3;
		case GL_FLOAT_MAT4:    return ShaderDataType::Mat4;
		case GL_INT:           return ShaderDataType::Int;
		case GL_INT_VEC2:      return ShaderDataType::Int2;
		case GL_INT_VEC3:      return ShaderDataType::Int3;
		case GL_INT_VEC4:      return ShaderDataType::Int4;
		case GL_BOOL:          return ShaderDataType::Bool;
		default:
			HYPO_CORE_WARN("Invalid shader data type");
			return ShaderDataType::None;
		}
	}

	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT_VEC2;
		case ShaderDataType::Float3:   return GL_FLOAT_VEC3;
		case ShaderDataType::Float4:   return GL_FLOAT_VEC4;
		case ShaderDataType::Mat3:     return GL_FLOAT_MAT3;
		case ShaderDataType::Mat4:     return GL_FLOAT_MAT4;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT_VEC2;
		case ShaderDataType::Int3:     return GL_INT_VEC3;
		case ShaderDataType::Int4:     return GL_INT_VEC4;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		HYPO_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const ShaderData& data)
	{
		for(auto& slot :m_TextureSlotBinding)
		{
			slot = -1;
		}
		
		std::vector<uInt32> shaders;
		if (data.HasShader(ShaderType::Vertex))
		{
			shaders.push_back(CompileShaderProgram(data.GetShader(ShaderType::Vertex), GL_VERTEX_SHADER));
		}
		else
		{
			HYPO_CORE_WARN("A shader must have a vertex shader");
		}
		if (data.HasShader(ShaderType::Fragment))
		{
			shaders.push_back(CompileShaderProgram(data.GetShader(ShaderType::Fragment), GL_FRAGMENT_SHADER));
		}
		else
		{
			HYPO_CORE_WARN("A shader must have a fragment shader");
		}
		if (data.HasShader(ShaderType::Geometry))
		{
			shaders.push_back(CompileShaderProgram(data.GetShader(ShaderType::Geometry), GL_GEOMETRY_SHADER));
		}
		LinkShader(shaders);

		SetupUniformsAndAttributesLocation();
		ParseUniformDataFromShaders();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetAttributeLayout(AttributeLayout& layout)
	{
		int location = 0;
		for (auto& element : layout)
		{
			if (m_AttributeLocation.find(element.Name) == m_AttributeLocation.end())
			{
				HYPO_CORE_WARN("Shader attribute layout contains addinal attribute that is not present in the shader: {}, This could be because the attribute is optimized away inside the shader", element.Name);
			}
			GLCall(glBindAttribLocation(m_RendererID, location, element.Name.c_str()));
			location++;
		}
		if (layout.GetElements().size() != m_AttributeLocation.size())
		{
			HYPO_CORE_DEBUG("Shader attribute layout and shader attrubites count dosen't match: layout: {}, shader: {}", layout.GetElements().size(), m_AttributeLocation.size());

		}
	}

	

	void OpenGLShader::LinkShader(std::vector<uInt32> shaders)
	{
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		for (auto i : shaders)
		{
			glAttachShader(m_RendererID, i);
		}
		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);


			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			for (auto i : shaders)
			{
				glDeleteShader(i);
			}
			HYPO_CORE_ERROR("{0}", infoLog.data());
			HYPO_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto i : shaders)
		{
			glDetachShader(m_RendererID, i);
		}
	}

	uInt32 OpenGLShader::CompileShaderProgram(const std::string& src, int shaderType)
	{
		GLuint shaderID = glCreateShader(shaderType);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = src.c_str();
		glShaderSource(shaderID, 1, &source, 0);
		std::cout << "Shader: " << src << std::endl;
		// Compile the vertex shader
		glCompileShader(shaderID);

		GLint isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shaderID);

			HYPO_CORE_ERROR("{0}", infoLog.data());

			if (shaderType == GL_VERTEX_SHADER)
			{
				HYPO_CORE_WARN("Vertex shader compilation failure!");
			}
			else if (shaderType == GL_FRAGMENT_SHADER)
			{

				HYPO_CORE_WARN("Fragment shader compilation failure!");
			}
			else if (shaderType == GL_GEOMETRY_SHADER)
			{
				HYPO_CORE_WARN("Geometry shader compilation failure!");
			}
			return -1;
		}
		return shaderID;
	}


	bool OpenGLIsSamplerType(int type)
	{
		switch (type)
		{
		case GL_SAMPLER_2D:
		case GL_SAMPLER_1D:
		case GL_SAMPLER_2D_ARRAY:
		case GL_SAMPLER_1D_ARRAY:
		case GL_SAMPLER_CUBE:
		case GL_SAMPLER_CUBE_MAP_ARRAY:
			return true;
			break;

		default:
			return false;
			break;
		}
	}
	
	void OpenGLShader::SetupUniformsAndAttributesLocation()
	{
		glUseProgram(m_RendererID);
		GLint count;
		GLint size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)

		GLchar name[ATTRIBUTE_MAX_LENGTH]; // variable name in GLSL
		GLsizei length; // name length
		glGetProgramiv(m_RendererID, GL_ACTIVE_ATTRIBUTES, &count);
		std::vector<BufferElement> elements;
		elements.resize(count);
		for (int i = 0; i < count; i++)
		{
			glGetActiveAttrib(m_RendererID, i, ATTRIBUTE_MAX_LENGTH, &length, &size, &type, name);

			int attribLocation = glGetAttribLocation(m_RendererID, name);
			
			m_AttributeLocation[name] = std::pair<int,int>{attribLocation , (int)type };
		}
		glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &count);

		for (int i = 0; i < count; i++)
		{
			glGetActiveUniform(m_RendererID, i, UNIFORM_MAX_LENGTH, &length, &size, &type, name);
			GLCall(glGetUniformLocation(m_RendererID, name));
			m_UniformLocation[name] = std::pair<int, int>{ glGetUniformLocation(m_RendererID, name), (int)type };
			if(OpenGLIsSamplerType(type))
			{
				m_UniformTextureSamplerLocationMap[name] = SamplerLocationData{ glGetUniformLocation(m_RendererID, name) ,-1};
			}
		}

	}

	void OpenGLShader::ParseUniformDataFromShaders()
	{

		GLint numBlocks;
		glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);

		std::unordered_map<std::string, std::pair<unsigned int, BufferLayout>> uniformBlockData;

		for (int blockIx = 0; blockIx < numBlocks; ++blockIx)
		{
			GLint blockNameLen;
			glGetActiveUniformBlockiv(m_RendererID, blockIx, GL_UNIFORM_BLOCK_NAME_LENGTH, &blockNameLen);

			GLint blockSize;
			glGetActiveUniformBlockiv(m_RendererID, blockIx, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);


			std::vector<GLchar> blockNameData; //Yes, not std::string. There's a reason for that.
			blockNameData.resize(blockNameLen);
			glGetActiveUniformBlockName(m_RendererID, blockIx, blockNameLen, NULL, &blockNameData[0]);
			std::string blockName;
			blockName.assign(blockNameData.begin(), blockNameData.end() - 1); //Remove the null terminator.

			glUniformBlockBinding(m_RendererID, blockIx, blockIx);

			int index = 0;
			if (auto i = blockName.find_first_of('['); i != std::string::npos)
			{
				std::string arrayIndexString = blockName.substr(i + 1, blockName.find_first_of(']', i) - i - 1);
				index = std::stoi(arrayIndexString);

				m_UniformBindData[blockName].blockIdx = blockIx;

				blockName.erase(blockName.begin() + i, blockName.end());

				uniformBlockData[blockName].first = uniformBlockData[blockName].first + 1;
			}

			if (index != 0)
			{
				continue;
			}
			m_UniformBindData[blockName].blockIdx = blockIx;
			uniformBlockData[blockName] = std::pair<uInt32, BufferLayout>{ 1, UniformLayout{std::move(ExtractUniformBufferData(blockIx, blockSize)), static_cast<uInt32>(blockSize)} };
		}

		for (auto it = uniformBlockData.begin(); it != uniformBlockData.end(); ++it)
		{
			auto& bindData = m_UniformBindData[it->first];
			bindData.binder = UniformBinderManager::AddUniformBinder(it->first, it->second.second);
			bindData.count = it->second.first;
		}
	}

	std::vector<BufferElement> OpenGLShader::ExtractUniformBufferData(unsigned int blockIx, unsigned int blockSize)
	{
		int uniformCount;
		GLCall(glGetActiveUniformBlockiv(m_RendererID, blockIx, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uniformCount));

		std::vector<unsigned int> indices(uniformCount);
		glGetActiveUniformBlockiv(m_RendererID, blockIx, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, reinterpret_cast<int*>(indices.data()));

		std::vector<int> uniformOffsets(uniformCount);
		glGetActiveUniformsiv(m_RendererID, uniformCount, indices.data(), GL_UNIFORM_OFFSET, uniformOffsets.data());

		std::vector<BufferElement> elements;

		for (int i = 0; i < uniformCount; i++)
		{
			GLint size; // size of the variable, how many in the array
			GLenum type; // type of the variable (float, vec3 or mat4, etc)

			GLchar uniformNameData[ATTRIBUTE_MAX_LENGTH]; // variable name in GLSL
			GLsizei length; // name length

			glGetActiveUniform(m_RendererID, indices[i], ATTRIBUTE_MAX_LENGTH, &length, &size, &type, uniformNameData);

			int arrayStride;
			glGetActiveUniformsiv(m_RendererID, 1, &indices[i], GL_UNIFORM_ARRAY_STRIDE, &arrayStride);

			//Extract the GSLS name
			std::string uniformName = std::string(uniformNameData);
			auto pos = uniformName.find_last_of('.');
			if (pos != std::string::npos)
			{
				uniformName = uniformName.substr(pos + 1);
			}
			if (auto i = uniformName.find_first_of('['); i != std::string::npos)
			{
				uniformName.erase(uniformName.begin() + i, uniformName.end());
			}

			uInt32 arrayCount = 1;

			if (arrayStride > 0)
			{
				int uniformDataEnd;
				if (static_cast<uInt32>(uniformCount) <= i + 1)
				{
					uniformDataEnd = blockSize;
				}
				else
				{
					uniformDataEnd = uniformOffsets[i + 1];
				}
				int uniformTotalArraySize = uniformDataEnd - uniformOffsets[i];


				arrayCount = static_cast<uInt32>(uniformTotalArraySize / arrayStride);

			}
			elements.push_back(BufferElement{ OpenGLToShaderDataType(type), arrayCount,uniformName, false, static_cast<uInt32>(uniformOffsets[i]), static_cast<uInt32>(arrayStride) });

		}
		return elements;
	}

	bool OpenGLShader::BindUniformBuffer(UniformBuffer::Ptr& buffer)
	{
		auto it = m_UniformBindData.find(buffer->GetBinderName());
		if (it != m_UniformBindData.end())
		{
			auto& data = it->second;

			if (buffer->GetBinderForBuffer() != data.binder)
			{
			HYPO_CORE_WARN("Cannot bind uniform buffer {}", buffer->GetBinderName());
				return false;
			}
			OpenGLUniformBuffer& openGLbuffer = reinterpret_cast<OpenGLUniformBuffer&>(buffer.GetRef());
			glUseProgram(m_RendererID);
			glBindBufferBase(GL_UNIFORM_BUFFER, it->second.blockIdx, openGLbuffer.GetBuffer().GetRendererID());
			return true;
		}
		HYPO_CORE_WARN("Could not find buffer {}", buffer->GetBinderName());
		return false;
	}

	bool OpenGLShader::BindUniformBuffer(UniformBuffer::Ptr& buffer, uInt32 index)
	{
		auto it = m_UniformBindData.find(buffer->GetBinderName());
		if (it != m_UniformBindData.end())
		{
			auto& data = it->second;

			if (buffer->GetBinderForBuffer() != data.binder)
			{
				HYPO_CORE_WARN("Cannot bind uniform buffer {}", buffer->GetBinderName());
				return false;
			}
			OpenGLUniformBuffer& openGLbuffer = reinterpret_cast<OpenGLUniformBuffer&>(buffer.GetRef());
			glUseProgram(m_RendererID);
			glBindBufferBase(GL_UNIFORM_BUFFER, it->second.blockIdx + index, openGLbuffer.GetBuffer().GetRendererID());
			return true;
		}
		HYPO_CORE_WARN("Could not find buffer {}", buffer->GetBinderName());
		return false;
	}

	void OpenGLShader::UpdateAttributeLayout()
	{
	}

	void OpenGLShader::SetUniform1f(const std::string& name, float v0)
	{
		CHECK_UNIFORM(name, GL_FLOAT);
		glUniform1f(GetUniformLocation(name), v0);
	}

	void OpenGLShader::SetUniform2f(const std::string& name, float v0, float v1)
	{
		CHECK_UNIFORM(name, GL_FLOAT_VEC2);
		glUniform2f(GetUniformLocation(name), v0, v1);
	}

	void OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		CHECK_UNIFORM(name, GL_FLOAT_VEC3);
		glUniform3f(GetUniformLocation(name), v0, v1, v2);
	}

	void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		CHECK_UNIFORM(name, GL_FLOAT_VEC4);
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void OpenGLShader::SetUniform1i(const std::string& name, int v0)
	{
		CHECK_UNIFORM(name, GL_INT);
		glUniform1i(GetUniformLocation(name), v0);
	}

	void OpenGLShader::SetUniform2i(const std::string& name, int v0, int v1)
	{
		CHECK_UNIFORM(name, GL_INT_VEC2);
		glUniform2i(GetUniformLocation(name), v0, v1);
	}

	void OpenGLShader::SetUniform3i(const std::string& name, int v0, int v1, int v2)
	{
		CHECK_UNIFORM(name, GL_INT_VEC3);
		glUniform3i(GetUniformLocation(name), v0, v1, v2);
	}

	void OpenGLShader::SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3)
	{
		CHECK_UNIFORM(name, GL_INT_VEC4);
		glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void OpenGLShader::SetUniform2f(const std::string& name, Vec2F vec)
	{
		CHECK_UNIFORM(name, GL_INT_VEC2);
		glUniform2f(GetUniformLocation(name), vec.x, vec.y);
	}

	void OpenGLShader::SetUniform3f(const std::string& name, Vec3F vec)
	{
		CHECK_UNIFORM(name, GL_INT_VEC3);
		glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
	}

	void OpenGLShader::SetUniform4f(const std::string& name, Vec4F vec)
	{
		CHECK_UNIFORM(name, GL_INT_VEC4);
		glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void OpenGLShader::SetUniformMat3f(const std::string& name, glm::mat3& mat3)
	{
		CHECK_UNIFORM(name, GL_FLOAT_MAT3);
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat3[0][0]);
	}

	void OpenGLShader::SetUniformMat4f(const std::string& name, glm::mat4& mat4)
	{
		CHECK_UNIFORM(name, GL_FLOAT_MAT4);
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat4[0][0]);
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (const auto it = m_UniformLocation.find(name); it != m_UniformLocation.end())
			return it->second.first;
		HYPO_CORE_ERROR("Could not find shader uniform location for uniform: {}", name);
		return -1;
	}

	int OpenGLShader::GetAttributeLocation(const std::string& name)
	{
		if (const auto it = m_AttributeLocation.find(name); it != m_AttributeLocation.end())
			return it->second.first;
		HYPO_CORE_ERROR("Could not find shader attribute location for attribute: {}", name);
		return -1;
	}

	int OpenGLShader::GetUniformType(const std::string& name)
	{
		if (const auto it = m_UniformLocation.find(name); it != m_UniformLocation.end())
			return it->second.second;
		HYPO_CORE_ERROR("Could not find shader uniform for uniform: {}", name);
		return -1;
	}

	int OpenGLShader::GetAttributeType(const std::string& name)
	{

		if (auto it = m_AttributeLocation.find(name); it != m_AttributeLocation.end())
			return it->second.second;
		HYPO_CORE_ERROR("Could not find shader attribute type for attribute: {}", name);
		return -1;
	}

	void OpenGLShader::SetAttribute(const BufferElement& element, int stride, bool perInstance)
	{
		glUseProgram(m_RendererID);
		int location = GetAttributeLocation(element.Name);
		if (location == -1)
		{
			HYPO_CORE_ERROR("[SciEngineGL] could not resolve attribute varible {}", element.Name);
			return;
		}
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			stride,
			(const void*)static_cast<uInt64>(element.Offset));
		if (perInstance)
		{
			glVertexAttribDivisor(location, 1);
		}
	}

	//TODO: Fix this function
	int OpenGLShader::GetNextFreeTextureSlot(int favourd)
	{
		if(nextFreeTextureSlot + 2 > OPENGL_TEXTURE_SLOTS)
		{
			nextFreeTextureSlot = 0;
		}
		return ++nextFreeTextureSlot;
	}
	
	void OpenGLShader::BindTexture(ObjPtr<Texture2D> texture, std::string name)
	{
		auto* openGLTexture = texture.Cast<OpenGLTexture2D>();

		auto it = m_UniformTextureSamplerLocationMap.find(name);
		if(it == m_UniformTextureSamplerLocationMap.end())
		{
			HYPO_CORE_ERROR("Unkown texture {}", name);
			return;
		}
		const int textureSamplerLocation = it->second.shaderLocation;
		const int currentBoundTextureSlot = it->second.currentSlotBound;

		
		int currentBoundTextureID = -1;
		if(currentBoundTextureSlot >= 0 && currentBoundTextureSlot <= OPENGL_TEXTURE_SLOTS)
			currentBoundTextureID = m_TextureSlotBinding[currentBoundTextureSlot];
		
		//We need to bind the new texture
		if(openGLTexture->GetRendererID() != currentBoundTextureID)
		{
			Bind();
			int newTextureSlot = GetNextFreeTextureSlot(openGLTexture->GetBoundSlot());
			
			glUniform1i(textureSamplerLocation, newTextureSlot);
			
			openGLTexture->Bind(newTextureSlot);

			it->second.currentSlotBound = newTextureSlot;
			
			m_TextureSlotBinding[newTextureSlot] = openGLTexture->GetRendererID();
			return;
		}

		if(currentBoundTextureSlot != openGLTexture->GetBoundSlot())
		{
			int newTextureSlot = GetNextFreeTextureSlot(openGLTexture->GetBoundSlot());

			glUniform1i(textureSamplerLocation, newTextureSlot);

			openGLTexture->Bind(newTextureSlot);

			it->second.currentSlotBound = newTextureSlot;
			return;
		}
	}

	bool OpenGLShader::CompatibleWithVertexArray(ObjPtr<class VertexArray>& vertexArray)
	{
		/*OpenGLVertexArray& va = vertexArray.CastToRef<OpenGLVertexArray>();
		int location = 0;
		bool error = false;
		for (auto& buffer : va.m_Buffers)
		{
			for (auto& element : buffer->GetLayout())
			{
				if (GetAttributeLocation(element.Name) != location)
				{
					HYPO_CORE_ERROR("VertexArray attribute not linked correctly to shader! {}", element.Name);
					error = true;
				}
				if (GetAttributeType(element.Name) != ShaderDataTypeToOpenGLType(element.Type))
				{
					HYPO_CORE_ERROR("VertexArray attribute {} isen't the same type as in the shader!", element.Name);
					error = true;
				}
				location++;
			}
		}
		return !error;*/
		return true;
	}

}