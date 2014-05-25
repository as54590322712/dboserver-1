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

#define BEGIN_PACKET(opcode) \
struct s##opcode :			 \
	public PACKETHEADER		 \
{							 \
	s##opcode() :			 \
	PACKETHEADER(opcode)	 \
	{						 \
	}
#define END_PACKET() };

#define DECLARE_PACKET_NAME(opcode) { #opcode }

#endif