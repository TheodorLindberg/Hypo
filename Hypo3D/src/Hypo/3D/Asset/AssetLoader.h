#pragma once
#include "Hypo/3D/Exports.h"
#include "AssetManager.h"

namespace Hypo
{
	template<typename AssetPtr>
	class  HYPO_3D_API Asset
	{
	public:
		AssetPtr asset;
		std::string name;
	};
	using ShaderAsset = Asset<Shader::Ptr>;
	using Texture2DAsset = Asset<Texture2D::Ptr>;

	class HYPO_3D_API AssetLoader
	{
	public:
		static Texture2DAsset LoadTexture2DAsset(const std::string& path);
		static ShaderAsset LoadShaderAsset(const std::string& path);

	private:
	};

}
