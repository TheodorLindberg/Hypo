#pragma once
#include "Hypo/Graphics/Exports.h"
#include <unordered_map>
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "Hypo/Graphics/BufferLayout.h"

namespace Hypo
{	
	class UniformBinder
	{
	public:
		using Ptr = ObjPtr<UniformBinder>;
	private:
	};


	class UniformBinderManager
	{
	public:
		static bool HasUniformBinder(const std::string& name);
		static UniformBinder::Ptr GetUniformBinder(const std::string& name);

		static void AddUniformBinder(const std::string& name, const UniformLayout& layout);
	private:
		static std::unordered_map<std::string, UniformBinder::Ptr> m_Binders;
		
	};
}

