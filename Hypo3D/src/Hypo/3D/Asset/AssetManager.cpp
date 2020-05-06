#include "hypo3dpch.h"
#include "AssetManager.h"
#include "AssetLoader.h"

namespace Hypo
{
	std::unordered_map<std::string, Texture2D::Ptr> AssetManager::m_Texture2DAssets;
	std::unordered_map<std::string, Shader::Ptr> AssetManager::m_ShaderAssets;

	Texture2D::Ptr AssetManager::RetrieveTexture2DAsset(const std::string& name, const std::string& path)
	{
		if(auto it = m_Texture2DAssets.find(name); it != m_Texture2DAssets.end())
		{
			return it->second;
		}
		auto asset = AssetLoader::LoadTexture2DAsset(path);
		m_Texture2DAssets[name] = asset.asset;
		return asset.asset;
	}

	Shader::Ptr AssetManager::RetrieveShaderAsset(const std::string& name, const std::string& path)
	{
		if (auto it = m_ShaderAssets.find(name); it != m_ShaderAssets.end())
		{
			return it->second;
		}
		auto asset = AssetLoader::LoadShaderAsset(path);
		m_ShaderAssets[name] = asset.asset;
		return asset.asset;
	}

	bool AssetManager::Texture2DAssetLoaded(const std::string& name)
	{
		return m_Texture2DAssets.find(name) != m_Texture2DAssets.end();
	}

	bool AssetManager::ShaderAssetLoaded(const std::string& name)
	{
		return m_ShaderAssets.find(name) != m_ShaderAssets.end();
	}
}
