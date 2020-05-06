#include "hypo3dpch.h"
#include "AssetLoader.h"
#include "Hypo/Graphics/Shader/ShaderAsset.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hypo
{
	Texture2DAsset AssetLoader::LoadTexture2DAsset(const std::string& path)
	{
		auto data = TextureFromFile(path);
		auto texture2D = Texture2D::Create(data, TextureUsage::Static);

		Texture2DAsset asset;
		asset.asset = texture2D;



		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		auto name = path.substr(lastSlash, count);

		asset.name = std::move(name);
		return asset;
	}

	ShaderAsset AssetLoader::LoadShaderAsset(const std::string& path)
	{
		auto data = ShaderFromFile(path);
		auto shader = Shader::Create(data);

		ShaderAsset asset;
		asset.asset = shader;
		asset.name = data.GetName();
		return asset;
	}

}
