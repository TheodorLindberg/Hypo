#pragma once
#include "Hypo/Graphics/Exports.h"
#include "gsl/span"
namespace Hypo
{
	class OpenGLBuffer
	{
	public:
		OpenGLBuffer() = default;
		~OpenGLBuffer();

		uInt32 GetRendererID() const { return m_RendererID; }
		
		template<int type>
		bool LoadEmpty(uInt32 size, bool dynamic = false);
		
		template<int type>
		bool Load(gsl::span<const Byte> data, bool dynamic = false);
		
		template<int type>
		bool Update(gsl::span<const Byte> data, uInt32 offset = 0);

		template<int type>
		bool Update(uInt32 offset, const void* data, uInt32 size);

		template<int type>
		bool Bind();
		
		template<int type>
		bool UnBind();

		uInt32 GetBufferSize() { return m_BufferSize; }

#ifdef BUFFER_TYPE_CHECK
		int _debug_buffer_type;
		int _debug_buffer_size;
#endif
		uInt32 m_RendererID = 0;
		uInt32 m_BufferSize = 0;
	};
}
