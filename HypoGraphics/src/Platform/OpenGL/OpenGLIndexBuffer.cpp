#include "graphicspch.h"
#include "OpenGLIndexBuffer.h"
#include "glad/glad.h"


Hypo::OpenGLIndexBuffer::OpenGLIndexBuffer(uInt32 size)
{

	m_Count = size / sizeof(ElementIndex);
	m_Buffer.LoadEmpty<GL_ELEMENT_ARRAY_BUFFER>(size);
}

Hypo::OpenGLIndexBuffer::OpenGLIndexBuffer(gsl::span<ElementIndex> data)
{
	m_Count = data.size();
	m_Buffer.Load<GL_ELEMENT_ARRAY_BUFFER>(ConvertSpanToBytes(data));
}

void Hypo::OpenGLIndexBuffer::Bind()
{
	m_Buffer.Bind<GL_ELEMENT_ARRAY_BUFFER>();
}

void Hypo::OpenGLIndexBuffer::Unbind()
{
	m_Buffer.UnBind<GL_ELEMENT_ARRAY_BUFFER>();
}


Hypo::OpenGLIndexBufferDynamic::OpenGLIndexBufferDynamic(uInt32 size)
{
	m_Count = size / sizeof(ElementIndex);
	m_Buffer.LoadEmpty<GL_ELEMENT_ARRAY_BUFFER>(size, true);
}

Hypo::OpenGLIndexBufferDynamic::OpenGLIndexBufferDynamic(gsl::span<ElementIndex> data)
{
	m_Count = data.size();
	m_Buffer.Load<GL_ELEMENT_ARRAY_BUFFER>(ConvertSpanToBytes(data), true);
}

void Hypo::OpenGLIndexBufferDynamic::Update(gsl::span<ElementIndex> data, uInt32 offset)
{
	m_Buffer.Update<GL_ELEMENT_ARRAY_BUFFER>(ConvertSpanToBytes(data), offset);
}

