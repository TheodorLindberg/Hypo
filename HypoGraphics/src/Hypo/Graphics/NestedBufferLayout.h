#pragma once
#include "Hypo/Graphics/Exports.h"
#include "BufferLayout.h"
#include <unordered_map>
#include <iostream>


namespace Hypo
{
	
	struct NodePathSection
	{
		std::string name;
		int index = 1;
	};
	
	using NodePath = std::vector<NodePathSection>;

	static NodePathSection ParseSection(const std::string& section)
	{
		auto pos = section.find_first_of('[');
		NodePathSection data;
		if (pos != std::string::npos)
		{
			data.name = section.substr(0, pos);
			int end = section.find_first_of(']');
			int count = end - pos;
			data.index = std::stoi(section.substr(pos + 1, count - 1));
		}
		else
		{
			data.name = section;
		}
		return data;
	}

	static NodePath ParsePath(const std::string& string)
	{
		NodePath sections;

		std::string::const_iterator iter = string.begin();
		std::string::const_iterator sectionBegin = string.begin();
		while ((iter = std::find_if(iter, string.end(), [](char c) { return c == '.';  })) != string.end())
		{
			std::string::const_iterator sectionEnd = iter;
			sections.push_back(NodePathSection{ std::string(sectionBegin, sectionEnd), 1}/*ParseSection()*/);
			sectionBegin = sectionEnd + 1;
			iter++;
		}
		sections.push_back(ParseSection(std::string(sectionBegin, string.end())));
		return sections;
	}





	using NodeList = std::unordered_map<std::string, std::unique_ptr<class BufferMemoryLayoutNode>>;
	class BufferMemoryLayoutNode
	{
	public:

		BufferMemoryLayoutNode(uInt32 offset, uInt32 size, ShaderDataType type)
			: m_Offset(offset), m_Size(size),  m_Type(type)
		{}

		const BufferMemoryLayoutNode* GetElement(NodePath path) const
		{
			//Check if final element
			if (path.empty())
			{
				return this;
			}
			else
			{
				auto& next = path.begin();

				auto nextNode = m_Children.find(next->name);

				if (nextNode == m_Children.end())
				{
					return nullptr;
				}
				else
				{
					//TODO: Make more efficient path stack system
					path.erase(path.begin());
					return nextNode->second->GetElement(path);
				}
			}
		}
		bool AddElement(NodePath path, uInt32 offset, uInt32 size,  ShaderDataType type)
		{
			auto it = m_Children.find(path.begin()->name);
			if(it != m_Children.end())
			{
				path.erase(path.begin());
				it->second->AddElement(path, offset, size, type);
			} 
			else
			{
				if(path.size() > 1)
				{
					auto object = std::make_unique<BufferMemoryLayoutNode>(BufferMemoryLayoutNode{ offset, 0,  ShaderDataType::Struct });
					auto pathSection = path[0];
					path.erase(path.begin());
					object->AddElement(path, offset, size, type);
					m_Children[pathSection.name] = std::move(object);
					
				} 
				else if(path.size()  == 1)
				{

					m_Children[path[0].name] = std::make_unique<BufferMemoryLayoutNode>(BufferMemoryLayoutNode{ offset, 0,  type });
				}
			}

			return true;
		}

		NodeList::iterator begin() { return m_Children.begin(); }
		NodeList::iterator end() { return m_Children.end(); }
		NodeList::const_iterator begin() const { return m_Children.begin(); }
		NodeList::const_iterator end() const { return m_Children.end(); }
	public:
		uInt32 m_Offset = -1;
		uInt32 m_Size = -1;

		ShaderDataType m_Type = ShaderDataType::None;

		NodeList m_Children;
		

	};


	class BufferMemoryLayout
	{
	public:

		BufferMemoryLayout(uInt32 bufferSize = 0)
			: m_Base(std::make_shared< BufferMemoryLayoutNode>(0, bufferSize, ShaderDataType::None)), m_Size(bufferSize)
		{}

		const BufferMemoryLayoutNode* GetElement(const std::string& path) const { return m_Base->GetElement(ParsePath(path)); }

		bool AddElement(const std::string& path, uInt32 offset, uInt32 size, ShaderDataType type)
		{
			
			return m_Base->AddElement(ParsePath(path), offset, size,type);
		}

		uInt32 GetStride() const
		{
			return m_Size;
		}

		bool operator!=(const BufferMemoryLayout& other) const
		{
			return m_Base != other.m_Base;
		}

		NodeList::iterator begin() { return m_Base->begin(); }
		NodeList::iterator end() { return m_Base->end();}
		NodeList::const_iterator begin() const { return m_Base->begin(); }
		NodeList::const_iterator end() const { return m_Base->end();}
	private:
		uInt32 m_Size;
		std::shared_ptr<BufferMemoryLayoutNode> m_Base;
	};

	using UniformLayout = BufferMemoryLayout;
	

}
