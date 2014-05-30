#ifndef _PACKET_H
#define _PACKET_H

#include "Def.h"



struct PACKETHEADER
{
	PACKETHEADER(WORD GivenOpcode) :
		OpCode(GivenOpcode) {}
	WORD Size;
	BYTE Count;
	BYTE Hash;
	WORD OpCode;
};

#pragma pack(push, 1)
#define BEGIN_PACKET(opcode) \
struct s##opcode :			 \
	public PACKETHEADER		 \
{							 \
	s##opcode() :			 \
	PACKETHEADER(opcode)	 \
	{						 \
	}
#define END_PACKET() };
#pragma pack(pop)

#endif