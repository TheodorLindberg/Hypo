#pragma once
#include <Hypo/Config.h>
#include <Hypo/System/Exports.h>
#include <gsl/span>
#include <Hypo/System/Streams/MemoryStream.h>
#include <Hypo/System/Buffer/Buffer.h>

namespace Hypo
{
	class HYPO_SYSTEM_API BinaryReader
	{
	public:
		BinaryReader(std::istream& stream);

		BinaryReader& operator >>(uInt8& value);
		BinaryReader& operator >>(uInt16& value);
		BinaryReader& operator >>(uInt32& value);
		BinaryReader& operator >>(uInt64& value);
		BinaryReader& operator >>(Int8& value );
		BinaryReader& operator >>(Int16& value);
		BinaryReader& operator >>(Int32& value);
		BinaryReader& operator >>(Int64& value);
		
		BinaryReader& operator >>(std::string& value);

		template<typename T>
		BinaryReader& operator >>(std::vector<T>& value)
		{
			uInt32 size = 0;
			*this >> size;
			
			for (int i = 0; i < size; i++)
			{
				T elem;
				*this >> elem;
				value.push_back(elem);
			}
			return *this;
		}

		std::vector<unsigned char> ReadRaw(int size);
		void ReadRaw(void* buffer, int size);

		void ReadBOM();

		void Read7BitEncoded(uInt32& value);
		void Read7BitEncoded(uInt64& value);

		bool Good()const { return m_Stream.good(); }
		bool Bad()const { return m_Stream.bad(); }
		bool Fail() const { return m_Stream.fail(); }
		bool Eof() const { return m_Stream.eof(); }

		std::istream& GetStream() const { return m_Stream; }

	private:
		std::istream& m_Stream;
	};

	template <typename T>
	class BasicMemoryBinaryReader : public BinaryReader
		/// A convenient wrapper for using Buffer and MemoryStream with BinaryReader.
	{
	public:
		BasicMemoryBinaryReader(const Buffer<T>& data) :
			BinaryReader(_istr),
			_data(data),
			_istr(data.begin(), data.Capacity())
		{
		}


		~BasicMemoryBinaryReader()
		{
		}

		const Buffer<T>& data() const
		{
			return _data;
		}

		const MemoryInputStream& stream() const
		{
			return _istr;
		}

		MemoryInputStream& stream()
		{
			return _istr;
		}

	private:
		const Buffer<T>& _data;
		MemoryInputStream _istr;
	};


	typedef BasicMemoryBinaryReader<char> MemoryBinaryReader;



}

