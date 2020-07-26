#pragma once
#include "Hypo/3D/Exports.h"
#include "Hypo/Graphics/Texture/Texture.h"
#include "Hypo/Graphics/Shader/Shader.h"

namespace Hypo
{
	class  AssetManager
	{
	public:
		static HYPO_3D_API Texture2D::Ptr RetrieveTexture2DAsset(const std::string& name, const std::string& path);
		static HYPO_3D_API Shader::Ptr RetrieveShaderAsset(const std::string& name, const std::string& path);

		static HYPO_3D_API bool Texture2DAssetLoaded(const std::string& name);
		static HYPO_3D_API bool ShaderAssetLoaded(const std::string& name);
	private:
		static std::unordered_map<std::string, Texture2D::Ptr> m_Texture2DAssets;
		static std::unordered_map<std::string, Shader::Ptr> m_ShaderAssets;
	};

}
