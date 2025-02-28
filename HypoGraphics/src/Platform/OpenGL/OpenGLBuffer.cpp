#include "graphicspch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"
#include "Hypo/System/Util/Log.h"

namespace Hypo
{

	template <int type>
	bool OpenGLBuffer::LoadEmpty(uInt32 size, bool dynamic)
	{

#ifdef BUFFER_TYPE_CHECK
		_debug_buffer_type = type;
		_debug_buffer_size = size;
#endif
		m_BufferSize = size;
		glGenBuffers(1, &m_RendererID);
		Bind<type>();

		
		glBufferData(type, size, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		return true;
	}
	template bool OpenGLBuffer::LoadEmpty<GL_ARRAY_BUFFER>(uInt32 size, bool dynamic);
	template bool OpenGLBuffer::LoadEmpty<GL_ELEMENT_ARRAY_BUFFER>(uInt32 size, bool dynamic);
	template bool OpenGLBuffer::LoadEmpty<GL_UNIFORM_BUFFER>(uInt32 size, bool dynamic);

	
	template <int type>
	bool OpenGLBuffer::Load(gsl::span<const Byte> data, bool dynamic)
	{
		#ifdef BUFFER_TYPE_CHECK
			_debug_buffer_type = type;
			_debug_buffer_size = data.size_bytes();
		#endif
		m_BufferSize = data.size_bytes();

		glGenBuffers(1, &m_RendererID);
		Bind<type>();
		glBufferData(type, data.size_bytes(), reinterpret_cast<const void*>(data.data()), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		return true;
	}

	template bool OpenGLBuffer::Load<GL_ARRAY_BUFFER>(gsl::span<const Byte> data, bool dynamic);
	template bool OpenGLBuffer::Load<GL_ELEMENT_ARRAY_BUFFER>(gsl::span<const Byte> data, bool dynamic);
	template bool OpenGLBuffer::Load<GL_UNIFORM_BUFFER>(gsl::span<const Byte> data, bool dynamic);
	
	template <int type>
	bool OpenGLBuffer::Update(gsl::span<const Byte> data, unsigned int offset)
	{
#ifdef BUFFER_TYPE_CHECK
		HYPO_CORE_ASSERT(_debug_buffer_type == type, "Updating OpenGL buffer using diffrent target type");
		HYPO_CORE_ASSERT(data.size_bytes() + offset > _debug_buffer_size, "Buffer overflow");
		
#endif
		
		Bind<type>();
		glBufferSubData(type, offset, data.size_bytes(), static_cast<const void*>(data.data()));
		return true;
	}

	template bool OpenGLBuffer::Update<GL_ARRAY_BUFFER>(gsl::span<const Byte> data, unsigned int offset);
	template bool OpenGLBuffer::Update<GL_ELEMENT_ARRAY_BUFFER>(gsl::span<const Byte> data, unsigned int offset);
	template bool OpenGLBuffer::Update<GL_UNIFORM_BUFFER>(gsl::span<const Byte> data, unsigned int offset);


	template <int type>
	bool OpenGLBuffer::Update(uInt32 offset, const void* data, uInt32 size)
	{
#ifdef BUFFER_TYPE_CHECK
		HYPO_CORE_ASSERT(_debug_buffer_type == type, "Updating OpenGL buffer using diffrent target type");
		HYPO_CORE_ASSERT(data.size_bytes() + offset > _debug_buffer_size, "Buffer overflow");
#endif
		Bind<type>();
		glBufferSubData(type, offset, size, data);
		return true;
	}
	
	template bool OpenGLBuffer::Update<GL_ARRAY_BUFFER>(uInt32 offset, const void* data, uInt32 size);
	template bool OpenGLBuffer::Update<GL_ELEMENT_ARRAY_BUFFER>(uInt32 offset, const void* data, uInt32 size);
	template bool OpenGLBuffer::Update<GL_UNIFORM_BUFFER>(uInt32 offset, const void* data, uInt32 size);
	
	template <int type>
	bool OpenGLBuffer::Bind()
	{
#ifdef BUFFER_TYPE_CHECK
		HYPO_CORE_ASSERT(_debug_buffer_type == type, "Binding OpenGL buffer using diffrent target type")
#endif
		
		glBindBuffer(type, m_RendererID);
		return true;
	}

	template bool OpenGLBuffer::Bind<GL_ARRAY_BUFFER>();
	template bool OpenGLBuffer::Bind<GL_ELEMENT_ARRAY_BUFFER>();
	template bool OpenGLBuffer::Bind<GL_UNIFORM_BUFFER>();

	
	template <int type>
	bool OpenGLBuffer::UnBind()
	{
#ifdef BUFFER_TYPE_CHECK
		HYPO_CORE_ASSERT(_debug_buffer_type == type, "Unbinding OpenGL buffer using diffrent target type")
#endif
		glBindBuffer(type, 0);
		return true;
	}

	template bool OpenGLBuffer::UnBind<GL_ARRAY_BUFFER>();
	template bool OpenGLBuffer::UnBind<GL_ELEMENT_ARRAY_BUFFER>();
	template bool OpenGLBuffer::UnBind<GL_UNIFORM_BUFFER>();

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}
