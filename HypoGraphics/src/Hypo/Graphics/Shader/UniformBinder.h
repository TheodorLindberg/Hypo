#pragma once
#include "Hypo/Graphics/Exports.h"
#include <unordered_map>
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "Hypo/Graphics/BufferLayout.h"
#include "Hypo/Graphics/NestedBufferLayout.h"

namespace Hypo
{	
	class  UniformBinder
	{
	public:
		using Ptr = ObjPtr<UniformBinder>;

		friend class AssetManager;

		using Ptr = ObjPtr<UniformBinder>;
		HYPO_GRAPHICS_API UniformBinder() = delete;

		HYPO_GRAPHICS_API uInt32 GetUniformOffset(const std::string& name, ShaderDataType type) const;
		HYPO_GRAPHICS_API uInt32 GetUniformOffset(const std::string& name, ShaderDataType type, uInt32 index) const;

		HYPO_GRAPHICS_API const UniformLayout& GetLayout() const { return m_Layout; }

		HYPO_GRAPHICS_API const std::string& GetName() const { return m_Name; }
		HYPO_GRAPHICS_API uInt32 GetBufferSize() const { return m_Layout.GetStride(); }
	private:
		friend class UniformBinderManager;
		UniformBinder(const std::string& name, const UniformLayout& layout);
	private:
		std::unordered_map<std::string, BufferElement> m_OffsetCache;
		const UniformLayout m_Layout;
		std::string m_Name;
	};



	class UniformBinderManager
	{
	public:
		static HYPO_GRAPHICS_API bool HasUniformBinder(const std::string& name);
		static HYPO_GRAPHICS_API UniformBinder::Ptr GetUniformBinder(const std::string& name);

		static HYPO_GRAPHICS_API UniformBinder::Ptr AddUniformBinder(const std::string& name, const UniformLayout& layout);
	private:
		static std::unordered_map<std::string, UniformBinder::Ptr> m_Binders;
		
	};
}

