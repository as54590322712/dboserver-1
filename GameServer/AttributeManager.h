#ifndef _ATTRIBUTEMANAGER
#define _ATTRIBUTEMANAGER

#include "Base.h"
#include "Def.h"
#include <TableAll.h>

class GameServer;
class GameClient;

class AttributeManager
{
private:
	void CompressAttributes();
public:
	AttributeManager();
	~AttributeManager();
	void LoadAttribute(sAVATAR_ATTRIBUTE* pAttribute);
	sGU_AVATAR_ATTRIBUTE_UPDATE PrepareUpdatePacket(HOBJECT playerSerialID);
private:
	sAVATAR_ATTRIBUTE_LINK pAvatarAttributeLink;//Compressed
	sAVATAR_ATTRIBUTE pAvatarMaintAttribute;//Uncompressed
};

#endif