#pragma once
#include <Hypo/System/Exports.h>
#include <Hypo/Config.h>
#include <ostream>
#include <gsl/span>
#include <Hypo/System/Exports.h>

#include <Hypo/System/Buffer/Buffer.h>
#include <Hypo/System/Streams/MemoryStream.h>

namespace Hypo
{
	class HYPO_SYSTEM_API BinaryWriter
	{
	public:
		BinaryWriter(std::ostream& stream);
	
		BinaryWriter& operator <<(uInt8 value);
		BinaryWriter& operator <<(uInt16 value);
		BinaryWriter& operator <<(uInt32 value);
		BinaryWriter& operator <<(uInt64 value);

		BinaryWriter& operator <<(Int8 value);
		BinaryWriter& operator <<(Int16 value);
		BinaryWriter& operator <<(Int32 value);
		BinaryWriter& operator <<(Int64 value);

		BinaryWriter& operator <<(const std::string& value);
		BinaryWriter& operator <<(const char* value);

		template<typename T>
		BinaryWriter& operator <<(const std::vector<T>& value)
		{
			const uInt32 size(static_cast<uInt32>(value.size()));
			*this << size;
			for (auto& element : value)
			{
				*this << element;
			}
			return *this;
		}

		void WriteRaw(const std::string& data);
		void WriteRaw(const gsl::span<uInt8>& data);
		void WriteRaw(const void* data, int size);
		
		void WriteBOM();
	
		void Write7BitEncoded(uInt32 value);
		void Write7BitEncoded(uInt64 value);

		void Flush()const { m_Stream.flush(); }
		bool Good()const { return m_Stream.good(); }
		bool Bad()const { return m_Stream.bad(); }
		bool Fail() const { return m_Stream.fail(); }

		std::ostream& GetStream() const {return m_Stream;}	
	private:
		std::ostream& m_Stream;
	};


	template <typename T>
	class BasicMemoryBinaryWriter : public BinaryWriter
		/// A convenient wrapper for using Buffer and MemoryStream with BinarWriter.
	{
	public:
		BasicMemoryBinaryWriter(Buffer<T>& data) :
			BinaryWriter(_ostr),
			_data(data),
			_ostr(data.begin(), data.Capacity())
		{
		}

		~BasicMemoryBinaryWriter()
		{
			try
			{
				Flush();
			}
			catch (...)
			{
			}
		}

		Buffer<T>& data()
		{
			return _data;
		}

		const Buffer<T>& data() const
		{
			return _data;
		}

		const MemoryOutputStream& stream() const
		{
			return _ostr;
		}

		MemoryOutputStream& stream()
		{
			return _ostr;
		}

	private:
		Buffer<T>& _data;
		MemoryOutputStream _ostr;
	};


	typedef BasicMemoryBinaryWriter<char> MemoryBinaryWriter;

}
