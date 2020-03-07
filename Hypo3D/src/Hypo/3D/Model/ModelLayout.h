#pragma once
#include "Mesh.h"
#include <string>
namespace Hypo
{

	class ModelLayoutNode
	{
	public:
		ModelLayoutNode(const char* name, std::vector<ModelLayoutNode> childs)
		{
			
		}
		ModelLayoutNode(std::string name, std::vector<ModelLayoutNode> childs)
		{

		}
		ModelLayoutNode(const char* name) {};
		ModelLayoutNode(std::string name) {};
		ModelLayoutNode(std::initializer_list<ModelLayoutNode> childs)
		{
			
		}
	};
	class ModelLayout
	{
	public:
		ModelLayout(std::initializer_list<ModelLayoutNode> nodes = {})
		{
			
		}
		ModelLayout() = default;
	};
	void c()
	{
		ModelLayout my = {
			{"Hello", {"Hello", "test","Hello","Test"} },
			{"Hello", {} }
		};
	}
}