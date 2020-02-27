#include "graphicspch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"
#include "Hypo/System/Util/Log.h"

namespace Hypo
{
	template <int type>
	bool OpenGLBuffer::LoadEmpty(uInt32 size)
	{
#ifdef BUFFER_TYPE_CHECK
		_debug_buffer_type = type;
		_debug_buffer_size = data.size();
#endif

		glGenBuffers(1, &m_RendererID);
		glBufferData(type, size, nullptr, GL_STATIC_DRAW);
	}

	template <int type>
	bool OpenGLBuffer::Load(gsl::span<float> data)
	{
		#ifdef BUFFER_TYPE_CHECK
			_debug_buffer_type = type;
			_debug_buffer_size = data.size();
		#endif

		glGenBuffers(1, &m_RendererID);
		glBufferData(type, data.size(), reinterpret_cast<void*>(data.data()), GL_STATIC_DRAW);
	}

	template <int type>
	bool OpenGLBuffer::Update(gsl::span<float> data, unsigned int offset)
	{
#ifdef BUFFER_TYPE_CHECK
		HYPO_CORE_ASSERT(_debug_buffer_type == type, "Updating OpenGL buffer using diffrent target type");
		HYPO_CORE_ASSERT(data.size() + offset > _debug_buffer_size, "Buffer overflow");
		
#endif

		glBufferSubData(type, offset, data.size(), static_cast<const void*>(data.data()));
	}

	template <int type>
	bool OpenGLBuffer::Bind()
	{
#ifdef BUFFER_TYPE_CHECK
		HYPO_CORE_ASSERT(_debug_buffer_type == type, "Binding OpenGL buffer using diffrent target type")
#endif
		
		glBindBuffer(type, m_RendererID);
	}

	template <int type>
	bool OpenGLBuffer::UnBind()
	{
#ifdef BUFFER_TYPE_CHECK
		HYPO_CORE_ASSERT(_debug_buffer_type == type, "Unbinding OpenGL buffer using diffrent target type")
#endif
		glBindBuffer(type, 0);
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}
