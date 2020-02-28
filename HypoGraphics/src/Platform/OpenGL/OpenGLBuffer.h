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
		
		template<int type>
		bool LoadEmpty(uInt32 size, bool dynamic = false);
		
		template<int type>
		bool Load(gsl::span<Byte> data, bool dynamic = false);
		
		template<int type>
		bool Update(gsl::span<Byte> data, uInt32 offset = 0);

		template<int type>
		bool Bind();
		
		template<int type>
		bool UnBind();

#ifdef BUFFER_TYPE_CHECK
		int _debug_buffer_type;
		int _debug_buffer_size;
#endif
		uInt32 m_RendererID = 0;
	};
}
