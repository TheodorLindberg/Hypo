#pragma once
#include "Hypo/Graphics/Exports.h"
#include "gsl/gsl"

namespace Hypo
{

	void HYPO_GRAPHICS_API init(void*);
	
	class HYPO_GRAPHICS_API VertexBuffer
	{
	public:
		using Ptr = std::shared_ptr<VertexBuffer>;
		static Ptr Create(gsl::span<float> data, bool dynamic = false);
		static Ptr Create(unsigned int size, bool dynamic = false);

		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;

		virtual void Update(gsl::span<float>, uInt32 offset) = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		
	};

}
