#include "systempch.h"
#include "BinaryReader.h"


namespace Hypo
{
	BinaryReader::BinaryReader(std::istream& stream)
		: m_Stream(stream)
	{
	}

	BinaryReader& BinaryReader::operator>>(uInt8& value)
	{
		m_Stream.read((char*)(&value), sizeof(uInt8));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(uInt16& value)
	{
		m_Stream.read((char*)(&value), sizeof(uInt16));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(uInt32& value)
	{
		m_Stream.read((char*)(&value), sizeof(uInt32));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(uInt64& value)
	{
		m_Stream.read((char*)(&value), sizeof(uInt64));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(Int8& value)
	{
		m_Stream.read((char*)(&value), sizeof(Int8));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(Int16& value)
	{
		m_Stream.read((char*)(&value), sizeof(Int16));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(Int32& value)
	{
		m_Stream.read((char*)(&value), sizeof(Int32));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(Int64& value)
	{
		m_Stream.read((char*)(&value), sizeof(Int64));
		return *this;
	}

	BinaryReader& BinaryReader::operator>>(std::string& value)
	{
		uInt32 size = 0;
		Read7BitEncoded(size);
		value.reserve(size);

		while(size--)
		{
			char c;
			m_Stream.read(&c, 1);
			value.push_back(c);
		}

		return *this;
	}

	std::vector<unsigned char> BinaryReader::ReadRaw(int size)
	{
		std::vector<unsigned char> buf(size);
		while(size--)
		{
			unsigned char c;
			if (!m_Stream.read((char*)&c, 1).good()) break;
			buf.push_back(c);
		}
		return std::move(buf);

	}

	void BinaryReader::ReadRaw(void* buffer, int size)
	{
		m_Stream.read((char*)buffer, size);
	}

	void BinaryReader::ReadBOM()
	{
		uInt16 BOM;
		m_Stream.read((char*)&BOM, sizeof(uInt16));
	}

	void BinaryReader::Read7BitEncoded(uInt32& value)
	{

		char c;
		value = 0;
		int s = 0;
		do
		{
			c = 0;
			m_Stream.read(&c, 1);
			uInt32 x = (c & 0x7F);
			x <<= s;
			value += x;
			s += 7;
		} while (c & 0x80);
	}

	void BinaryReader::Read7BitEncoded(uInt64& value)
	{
		char c;
		value = 0;
		int s = 0;
		do
		{
			c = 0;
			m_Stream.read(&c, 1);
			uInt64 x = (c & 0x7F);
			x <<= s;
			value += x;
			s += 7;
		} while (c & 0x80);
	}
}
