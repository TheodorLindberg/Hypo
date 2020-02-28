#pragma once
#include <vector>

namespace Hypo
{
	typedef unsigned short RefCounter;
	class ObjPtrMemoryManager
	{

	public:
		struct MemoryBlock
		{
			//Current write location of the block
			RefCounter* write;

			//Remaining size of the memory block
			int size;
			//Pointer to the MemoryPage counter
			unsigned short* counter;

			MemoryBlock(RefCounter* write, int size, unsigned short* counter)
				: write(write), size(size), counter(counter)
			{}
		};
		struct Page
		{
			//Pointer to start of the page
			RefCounter* begin;
			//Size of the page
			int size;

			//The count of the allocated RefCounters
			unsigned short allocatedCount;

			//Vector of the MemoryBlocks available inside the page
			std::vector<MemoryBlock> availableBlocks;

			Page(int size)
				: begin(new RefCounter[size]), size(size), allocatedCount(0), availableBlocks({ std::move(MemoryBlock(begin, size, &allocatedCount)) })
			{}

			RefCounter* Allocate()
			{
				if (availableBlocks.empty() || availableBlocks[0].size == 0)
				{
					return nullptr;
				}
				auto& block = availableBlocks[0];
				(*block.counter)++;
				block.size--;
				return block.write++;
			}
		};

		ObjPtrMemoryManager()
		{
			AddPage();
		}
		~ObjPtrMemoryManager()
		{
			for (auto* page : m_Pages)
			{
				delete page;
			}
		}

		RefCounter* Allocate()
		{
			RefCounter* ref = m_AllocatablePage->Allocate();
			if (!ref)
			{
				AddPage();
				return m_AllocatablePage->Allocate();
			}
			return ref;
		}
		void Deallocate(RefCounter* counter)
		{
			(*counter) = 0xFFFF;
		}
		static ObjPtrMemoryManager& Get()
		{
			static ObjPtrMemoryManager mm;
			return mm;
		}
	private:
		void AddPage()
		{
			int pageSize = static_cast<int>((m_Pages.size() + 1) * 40);
			Page* page = new Page(pageSize);

			m_Pages.push_back(page);
			m_AllocatablePage = page;

		}

		std::vector<Page*> m_Pages;
		Page* m_AllocatablePage;
	};
}