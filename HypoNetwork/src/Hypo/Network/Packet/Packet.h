#pragma once
#include <Hypo/Core.h>
#include <Hypo/System/Streams/BinaryReader.h>
#include <Hypo/System/Streams/BinaryWriter.h>
#include <string>

namespace Hypo
{
	using PacketID = int;

	class Packet
	{
	public:
		Packet() = default;
		virtual ~Packet() = default;

		virtual int GetPacketSize() = 0;
		virtual PacketID GetID() = 0;
		virtual std::string GetName() = 0;

		static PacketID GetStaticID() { return 0; }
		static int GetStaticPacketSize() { return 0; }

		virtual void Write(BinaryWriter& writer) {};
		virtual void Read(BinaryReader& writer) {};
	};

	static inline BinaryWriter& operator <<(BinaryWriter&  writer, Packet* packet)
	{
		writer << packet->GetID();
		auto sizePos = writer.GetStream().tellp();
		
		writer << uInt32(0);

		auto contentBeginPos = writer.GetStream().tellp();
		packet->Write(writer);
		auto contentEndPos = writer.GetStream().tellp();

		uInt32 contentSize = contentEndPos - contentBeginPos;
		writer.GetStream().seekp(sizePos);
		writer << contentSize;

		writer.GetStream().seekp(contentEndPos);
		return writer;
	}


#define HYPO_NEXT_PACKET_ID()  (int)1
#define HYPO_PACKET_DATA(name, type) name, type


#define EXPAND(x) x
#define FOR_EACH_1(what, x,y, ...) what(x,y)
#define FOR_EACH_2(what, x,y, ...)\
  what(x,y);\
  EXPAND(FOR_EACH_1(what,  __VA_ARGS__))
#define FOR_EACH_3(what, x,y, ...)\
  what(x,y);\
  EXPAND(FOR_EACH_2(what, __VA_ARGS__))
#define FOR_EACH_4(what, x,y, ...)\
  what(x,y);\
  EXPAND(FOR_EACH_3(what,  __VA_ARGS__))
#define FOR_EACH_5(what, x,y, ...)\
  what(x,y);\
  EXPAND(FOR_EACH_4(what,  __VA_ARGS__))
#define FOR_EACH_6(what, x,y, ...)\
  what(x,y);\
  EXPAND(FOR_EACH_5(what,  __VA_ARGS__))
#define FOR_EACH_7(what, x,y, ...)\
  what(x,y);\
  EXPAND(FOR_EACH_6(what,  __VA_ARGS__))
#define FOR_EACH_8(what, x,y, ...)\
  what(x,y);\
  EXPAND(FOR_EACH_7(what,  __VA_ARGS__))
#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_RSEQ_N() 4, 4, 3, 3, 2, 2, 1, 1, 0
#define CONCATENATE(x,y) x##y
#define FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__))
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)






#define HYPO_DECLARE_MEMBER(type, name) type name;
#define HYPO_DEFINE_MEMBERS(...) FOR_EACH(HYPO_DECLARE_MEMBER, __VA_ARGS__)

#define HYPO_WRITE_MEMBER(type, name) writer << (name);
#define HYPO_PACKET_WRITE_MEMBERS(...)FOR_EACH(HYPO_WRITE_MEMBER, __VA_ARGS__)

#define HYPO_READ_MEMBER(type, name) reader >> (name);
#define HYPO_PACKET_READ_MEMBERS(...)FOR_EACH(HYPO_READ_MEMBER, __VA_ARGS__)


#define HYPO_PACKET(Name, Base, ...)							\
	class Name : public Base									\
	{															\
	public:														\
		int GetPacketSize() override							\
		{														\
			return sizeof(Name);								\
		}														\
		Hypo::PacketID GetID() override								\
		{														\
			return 1;							\
		}														\
		std::string GetName() override							\
		{														\
			return #Name;										\
		}														\
																\
		void Write(Hypo::BinaryWriter& writer) override				\
		{														\
		Base::Write(writer); \
			HYPO_PACKET_WRITE_MEMBERS(__VA_ARGS__)			\
		}														\
		void Read(Hypo::BinaryReader& reader) override				\
		{														\
		Base::Read(reader); \
			HYPO_PACKET_READ_MEMBERS(__VA_ARGS__)			\
		}														\
		HYPO_DEFINE_MEMBERS(__VA_ARGS__)						\
	};															\





}
