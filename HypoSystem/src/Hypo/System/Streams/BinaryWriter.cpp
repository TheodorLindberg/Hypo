#include "systempch.h"
#include "BinaryWriter.h"

namespace Hypo
{
	BinaryWriter::BinaryWriter(std::ostream& stream)
		: m_Stream(stream)
	{
	}

	BinaryWriter& BinaryWriter::operator<<(uInt8 value)
	{
		m_Stream.write((const char*)&value, sizeof(uInt8));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(uInt16 value)
	{
		m_Stream.write((const char*)&value, sizeof(uInt16));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(uInt32 value)
	{
		m_Stream.write((const char*)&value, sizeof(uInt32));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(uInt64 value)
	{
		m_Stream.write((const char*)&value, sizeof(uInt64));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(Int8 value)
	{
		m_Stream.write((const char*)&value, sizeof(Int8));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(Int16 value)
	{
		m_Stream.write((const char*)&value, sizeof(Int16));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(Int32 value)
	{
		m_Stream.write((const char*)&value, sizeof(Int32));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(Int64 value)
	{
		m_Stream.write((const char*)&value, sizeof(Int64));
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(const std::string& value)
	{
		uInt32 len = value.size();
		Write7BitEncoded(len);
		m_Stream.write(value.c_str(), len);
		return *this;
	}

	BinaryWriter& BinaryWriter::operator<<(const char* value)
	{
		uInt32 len = std::strlen(value);
		Write7BitEncoded(len);
		m_Stream.write(value, len);
		return *this;
	}

	void BinaryWriter::WriteRaw(const std::string& data)
	{
		m_Stream.write((const char*)data.c_str(), data.size());
	}

	void BinaryWriter::WriteRaw(const gsl::span<uInt8>& data)
	{
		m_Stream.write((const char*)data.data(),  data.size_bytes());
	}

	void BinaryWriter::WriteRaw(const void* data, int size)
	{
		m_Stream.write((const char*)data, size);
	}

	void BinaryWriter::WriteBOM()
	{
		m_Stream.write((const char*)((uInt16)0xFEFF), sizeof(uInt16));
	}

	void BinaryWriter::Write7BitEncoded(uInt32 value)
	{ 
		do
		{
			unsigned char val = value & 0b01111111;
			value >>= 7;
			if (value) val |= 0b10000000;
			m_Stream.write((const char*)&val, 1);
			
		} while (value);

	}

	void BinaryWriter::Write7BitEncoded(uInt64 value)
	{
		do
		{
			unsigned char val = value & 0b01111111;
			value >>= 7;
			if (value) val |= 0b10000000;
			m_Stream.write((const char*)&val, 1);

		} while (value);
	}
}
