#pragma once

namespace Hypo
{
	class Material
	{
	public:
	private:
		Texture2D::Ptr texture_;
		Texture2D::Ptr normalMap_;
		Texture2D::Ptr specularMap_;
		float shine;

	};
	class SimpleMaterial
	{
	public:
		SimpleMaterial() = default;
		SimpleMaterial(Texture2D::Ptr texture, Vec4F color = {0,0,0,0})
			: texture(texture), color(color)
		{}
	public:
		Texture2D::Ptr texture;
		Vec4F color;
	};
}