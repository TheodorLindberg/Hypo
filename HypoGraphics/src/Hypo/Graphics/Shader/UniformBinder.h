#pragma once
#include "Hypo/Graphics/Exports.h"
#include <unordered_map>
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "Hypo/Graphics/BufferLayout.h"

namespace Hypo
{	
	class HYPO_GRAPHICS_API UniformBinder
	{
	public:
		using Ptr = ObjPtr<UniformBinder>;

		friend class AssetManager;

		using Ptr = ObjPtr<UniformBinder>;
		UniformBinder() = delete;

		uInt32 GetUniformOffset(const std::string& name, ShaderDataType type) const;
		uInt32 GetUniformOffset(const std::string& name, ShaderDataType type, uInt32 index) const;

		const UniformLayout& GetLayout() const { return m_Layout; }

		const std::string& GetName() const { return m_Name; }
		uInt32 GetBufferSize() const { return m_Layout.GetStride(); }
	private:
		friend class UniformBinderManager;
		UniformBinder(const std::string& name, const UniformLayout& layout);
	private:
		std::unordered_map<std::string, BufferElement> m_OffsetCache;
		const UniformLayout m_Layout;
		std::string m_Name;
	};



	class HYPO_GRAPHICS_API UniformBinderManager
	{
	public:
		static bool HasUniformBinder(const std::string& name);
		static UniformBinder::Ptr GetUniformBinder(const std::string& name);

		static UniformBinder::Ptr AddUniformBinder(const std::string& name, const UniformLayout& layout);
	private:
		static std::unordered_map<std::string, UniformBinder::Ptr> m_Binders;
		
	};
}

