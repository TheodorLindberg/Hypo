#pragma once
#include <Hypo/Network/Packet/Packet.h>


HYPO_PACKET(SendChatMessagePacket, Hypo::Packet, std::string, name)

HYPO_PACKET(SetUsernamePacket, Hypo::Packet, std::string, name)