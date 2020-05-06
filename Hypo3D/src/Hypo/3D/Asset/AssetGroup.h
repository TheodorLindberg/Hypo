#pragma once
#include "Hypo/3D/Exports.h"
#include "Hypo/Graphics/Texture/Texture.h"
#include "Hypo/Graphics/Shader/Shader.h"

namespace Hypo
{
	class AssetGroup
	{
	public:
		Texture2D::Ptr GetTexture2DAsset();
		Shader::Ptr GetShaderAsset();


	private:
		std::unordered_map<std::string, Texture2D::Ptr> m_Texture2DAssets;
		std::unordered_map<std::string, Texture2D::Ptr> m_ShaderAssets;
	};

	class SceneAssets: public AssetGroup
	{
		
	};
}
