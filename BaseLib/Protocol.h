#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#pragma once

#include <string>
#include "Def.h"

struct sPACKETHEADER
{
	sPACKETHEADER(WORD opcode) :
	OpCode(opcode) {}
	WORD			OpCode;
};

#define BEGIN_PACKET(opcode) \
struct s##opcode :			 \
	public sPACKETHEADER	 \
{							 \
	s##opcode() : \
	sPACKETHEADER(opcode)	 \
{						 \
}
#define END_PACKET() };

#endif