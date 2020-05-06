#include "graphicspch.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"
#include "Hypo/System/Util/Log.h"

namespace Hypo
{
	uInt32 UniformBinder::GetUniformOffset(const std::string& name, ShaderDataType type) const
	{
		auto element = m_Layout.GetElement(name);
		if (element)
		{
			if (element->m_Type != type)
			{
				return -1;
			}
			return  element->m_Offset;
		}
		return -1;
	}

	uInt32 UniformBinder::GetUniformOffset(const std::string& name, ShaderDataType type, uInt32 index) const
	{
		//Find the element inside the table
		auto element = m_Layout.GetElement(name);
		if(element)
		{

			if (element->m_Type!= type)
			{
				return -1;
			}
			return  element->m_Offset;
		}
		/*
		if (const auto it = m_OffsetCache.find(name); it != m_OffsetCache.end())
		{
			//Check that it is the correct type
			if (it->second.Type != type)
			{
				return -1;
			}
			if (index > it->second.Count)
			{
				return -1;
			}
			return  it->second.Offset + index * it->second.ArrayElementStride;
		}*/
		return -1;
	}

	UniformBinder::UniformBinder(const std::string& name, const UniformLayout& layout)
		: m_Name(name), m_Layout(layout)
	{
		
		/*for (auto& element : layout)
		{
			m_OffsetCache[element.] = element;
		}*/
	}

	std::unordered_map<std::string, UniformBinder::Ptr>  UniformBinderManager::m_Binders;
	
	bool UniformBinderManager::HasUniformBinder(const std::string& name)
	{
		return m_Binders.find(name) != m_Binders.end();
	}

	UniformBinder::Ptr UniformBinderManager::GetUniformBinder(const std::string& name)
	{
		return m_Binders[name];
	}

	UniformBinder::Ptr UniformBinderManager::AddUniformBinder(const std::string& name, const UniformLayout& layout)
	{
		if(auto it = m_Binders.find(name); it != m_Binders.end())
		{
			if(it->second->GetLayout() != layout)
			{
				HYPO_CORE_CRITICAL("Multiple binders for {}", name);
				return nullptr;
			}
			else
			{
				return it->second;
			}
		}
		auto ptr = UniformBinder::Ptr(new UniformBinder(name, layout));
		m_Binders[name] = ptr;
		return ptr;
	}
}
