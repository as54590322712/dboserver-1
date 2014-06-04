#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "Def.h"

struct sPACKETHEADER
{
	sPACKETHEADER(WORD opcode) :
	OpCode(opcode) {}
	WORD			OpCode;
};

#pragma pack(push, 1)
#define BEGIN_PACKET(opcode) \
struct s##opcode :			 \
	public sPACKETHEADER	 \
{							 \
	s##opcode() : \
	sPACKETHEADER(opcode)	 \
{						 \
}
#define END_PACKET() };
#pragma pack(pop)

#endif