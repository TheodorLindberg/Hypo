#include "graphicspch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

Hypo::OpenGLVertexBuffer::OpenGLVertexBuffer(uInt32 size)
{
	m_Buffer.LoadEmpty<GL_ARRAY_BUFFER>(size);
}


Hypo::OpenGLVertexBuffer::OpenGLVertexBuffer(gsl::span<float> data)
{
	m_Buffer.Load<GL_ARRAY_BUFFER>(ConvertSpanToBytes(data));
}


void Hypo::OpenGLVertexBuffer::Bind()
{
	m_Buffer.Bind<GL_ARRAY_BUFFER>();
}

void Hypo::OpenGLVertexBuffer::Unbind()
{
	m_Buffer.UnBind<GL_ARRAY_BUFFER>();
}

Hypo::OpenGLVertexBufferDynamic::OpenGLVertexBufferDynamic(uInt32 size)
{
	m_Buffer.LoadEmpty<GL_ARRAY_BUFFER>(size);
}

Hypo::OpenGLVertexBufferDynamic::OpenGLVertexBufferDynamic(gsl::span<float> data)
{
	m_Buffer.Load<GL_ARRAY_BUFFER>(ConvertSpanToBytes(data), true);
}

void Hypo::OpenGLVertexBufferDynamic::Update(gsl::span<float> data, uInt32 offset)
{
	m_Buffer.Update<GL_ARRAY_BUFFER>(ConvertSpanToBytes(data), offset);
}
