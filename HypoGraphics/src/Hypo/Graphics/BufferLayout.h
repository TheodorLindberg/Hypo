#pragma once
#include "Hypo/Graphics/Exports.h"
#include <string>

#define SHADER_DATA_TYPE_PACK(id, count, size) (((size << 12) | count) << 8) | id
#define SHADER_DATA_TYPE_ID(data) static_cast<uInt8>(data)
#define SHADER_DATA_TYPE_COMPONENTS(data) ((data << 12) >> 20)
#define SHADER_DATA_TYPE_SIZE(data) (data >> 20)

namespace Hypo
{

	enum class ShaderDataType : uInt32
	{
		None = SHADER_DATA_TYPE_PACK(0, 0, 0),
		Struct = SHADER_DATA_TYPE_PACK(1, 0, 0),
		Float = SHADER_DATA_TYPE_PACK(1, 1, 4),
		Float2 = SHADER_DATA_TYPE_PACK(2, 2, 4 * 2),
		Float3 = SHADER_DATA_TYPE_PACK(3, 3, 4 * 3),
		Float4 = SHADER_DATA_TYPE_PACK(4, 4, 4 * 4),
		Mat3 = SHADER_DATA_TYPE_PACK(5, 3 * 3, 4 * 3 * 3),
		Mat4 = SHADER_DATA_TYPE_PACK(6, 4 * 4, 4 * 4 * 4),
		Int = SHADER_DATA_TYPE_PACK(7, 1, 4),
		Int2 = SHADER_DATA_TYPE_PACK(8, 2, 4 * 2),
		Int3 = SHADER_DATA_TYPE_PACK(9, 3, 4 * 3),
		Int4 = SHADER_DATA_TYPE_PACK(10, 4, 4 * 4),
		Bool = SHADER_DATA_TYPE_PACK(11, 1, 4)
	};
	static uInt32 ShaderDataTypeSize(ShaderDataType type)
	{
		return SHADER_DATA_TYPE_SIZE(int(type));
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uInt32 Size;
		uInt32 Count;
		uInt32 Offset;
		uInt32 ArrayElementStride = 0;
		bool Normalized;

		BufferElement()
			: Name(""), Type(ShaderDataType::None), Size(0), Count(0), Offset(0), Normalized(false)
		{}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Count(1), Offset(0), Normalized(normalized)
		{
		}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized, uInt32 offset)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Count(1), Offset(offset), Normalized(normalized)
		{
		}
		BufferElement(ShaderDataType type, uInt32 count, const std::string& name, bool normalized, uInt32 offset, uInt32 arrayElementStride)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Count(count), Offset(offset), Normalized(normalized), ArrayElementStride(arrayElementStride)
		{
		}
		uInt32 GetComponentCount() const
		{
			return SHADER_DATA_TYPE_COMPONENTS(int(Type));
		}

		bool operator!=(const BufferElement& other) const
		{
			if (Name != other.Name) return false;
			if (Type != other.Type) return false;
			if (Size != other.Size) return false;
			if (Count != other.Count) return false;
			if (Offset != other.Offset) return false;
			if (Normalized != other.Normalized) return false;
			return true;
		}
	};

	class _Layout
	{
	public:
		_Layout() = default;
		_Layout(const std::vector<BufferElement>& elements, uInt32 stride)
			: m_Elements(elements), m_Stride(stride)
		{}
		_Layout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}
		_Layout(const std::vector<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		_Layout(const _Layout& other)
			:m_Elements(other.m_Elements), m_Stride(other.m_Stride)
		{}

		inline uInt32 GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		bool operator !=(const _Layout& other) const
		{
			if (m_Stride != other.m_Stride) return false;
			if (m_Elements.size() != other.m_Elements.size()) return false;
			for (uInt32 i = 0; i < m_Elements.size(); i++)
			{
				if (m_Elements[i] != other.m_Elements[i]) return false;
			}
			return true;
		}
	private:
		void CalculateOffsetsAndStride()
		{
			uInt32 offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
			}
			m_Stride = offset;
		}
	private:
		std::vector<BufferElement> m_Elements;
		uInt32 m_Stride = 0;
	};
	using BufferLayout = _Layout;
	using AttributeLayout = _Layout;
	using UniformLayout = _Layout;
}