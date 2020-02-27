#pragma once
#include "Hypo/Graphics/Exports.h"
#include "gsl/span"
namespace Hypo
{
	class OpenGLBuffer
	{
		~OpenGLBuffer();
		
		template<int type>
		bool LoadEmpty(uInt32 size);
		
		template<int type>
		bool Load(gsl::span<float> data);
		
		template<int type>
		bool Update(gsl::span<float> data, uInt32 offset = 0);

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
