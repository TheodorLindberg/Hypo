#pragma once
#include <Hypo/Graphics/Exports.h>
#include <unordered_map>

namespace Hypo
{

	enum class ShaderType
	{
		Vertex,
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
		ShaderSources m_Shaders;
		std::string m_Name;
	};

	inline ShaderData::ShaderData(ShaderSources shaders, std::string name)
		:
	m_Shaders(shaders), m_Name(name)
	{
	}

	inline const std::string& ShaderData::GetShader(ShaderType type) const
	{
		if (auto it = m_Shaders.find(type); it != m_Shaders.end())
		{
			return it->second;
		}
		else
		{
			return std::string();
		}
	}

	ShaderData HYPO_GRAPHICS_API ShaderFromSources(const std::string& vertex, const std::string& frag, const std::string& name);
	ShaderData HYPO_GRAPHICS_API ShaderFromFile(const std::string& path);
	ShaderData HYPO_GRAPHICS_API ShaderFromMemory(std::istream& stream, const std::string& name);

}
