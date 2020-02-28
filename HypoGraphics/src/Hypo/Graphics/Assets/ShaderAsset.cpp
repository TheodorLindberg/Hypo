#include "graphicspch.h"
#include "Hypo/Graphics/Shader.h"

#include <fstream>

#include "Hypo/System/Util/Log.h"
#include "Hypo/Graphics/Assets/ShaderAsset.h"

namespace Hypo
{

	ShaderData ShaderFromSources(const std::string& vertex, const std::string& frag, const std::string& name)
	{
		ShaderData::ShaderSources sources;
		sources[ShaderType::Vertex] = vertex;
		sources[ShaderType::Fragment] = frag;
		return ShaderData(sources, frag);
	}
	
	ShaderData ShaderFromFile(const std::string& path)
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
 			HYPO_CORE_WARN("Could not load shader {}", path);
			file.close();
			return ShaderData();
		}
		
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		auto name = path.substr(lastSlash, count);
		
		auto data =  ShaderFromMemory(file, name);
		file.close();
		return data;
	}
	
	ShaderData ShaderFromMemory(std::istream& stream, const std::string& name)
	{

		ShaderData::ShaderSources shaderSources;
		std::unordered_map<std::string, std::string> tokens;
		std::string line;

		static const std::vector<std::string> fragmentShaderTokens = { "Frag", "frag", "Pixel", "pixel", "Fragment", "fragment" };
		static const std::vector<std::string> vertexShaderTokens = { "Vert", "vert", "Vertex", "vertex" };
		static const std::vector<std::string> geometryShaderTokens = { "Geom", "geom", "Geometry", "geometry" };

		std::string shader;
		ShaderType shaderType;
		bool readShader = false;
		while (std::getline(stream, line))
		{
			if (line.size() == 0) continue;
			if (line.at(0) == '#')
			{
				if (readShader)
				{
					shaderSources[shaderType] = shader;
					readShader = false;
				}
				auto size = line.find_first_of(' ');
				std::string token = line.substr(1, size - 1);

				std::string value = line.substr(size + 1);

				if (token == "type")
				{
					readShader = true;
					shader = "";
					if (std::find(fragmentShaderTokens.begin(), fragmentShaderTokens.end(), value) != fragmentShaderTokens.end())
					{
						shaderType = ShaderType::Fragment;
					}
					else if (std::find(vertexShaderTokens.begin(), vertexShaderTokens.end(), value) != vertexShaderTokens.end())
					{
						shaderType = ShaderType::Vertex;
					}
					else if (std::find(geometryShaderTokens.begin(), geometryShaderTokens.end(), value) != geometryShaderTokens.end())
					{
						shaderType = ShaderType::Geometry;
					}
					else
					{
						readShader = false;
						HYPO_CORE_WARN("Shader type {} is not supported", value);
					}
				}

				tokens[token] = value;
			}
			else if (readShader)
			{
				shader += line + "\n";
			}
		}
		if (readShader)
		{
			shaderSources[shaderType] = shader;
			readShader = false;
		}
		std::string version = "#version 300 core";
		if (auto it = tokens.find("version"); it != tokens.end())
		{
			version = "#version " + it->second;
		}
		for (auto& shader : shaderSources)
		{
			shader.second = version + "\n" + shader.second;
		}
		std::string shaderName = name;
		if (auto it = tokens.find("name"); it != tokens.end())
		{
			shaderName = it->second;
		}
		return ShaderData(shaderSources, shaderName);
	}

}
