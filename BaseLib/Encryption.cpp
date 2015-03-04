#include "Encryption.h"

int Encrypt(BYTE * pPlain, int nLength, DWORD dwCipherKey, BYTE * pbyCheckSum = NULL)
{
	if (NULL == pPlain)
	{
		return 0;
	}

	if (pbyCheckSum)
	{
		*pbyCheckSum = CHECKSUM_INITIAL_VALUE;
	}

	int nRound = nLength / sizeof(DWORD);
	DWORD * pdwRoundPlain = (DWORD*)pPlain;
	for (int i = 0; i < nRound; i++)
	{
		if (pbyCheckSum)
		{
			*pbyCheckSum = checksumTbl[*pbyCheckSum ^ (BYTE)pdwRoundPlain[i]];
		}

		pdwRoundPlain[i] ^= (DWORD)dwCipherKey;
	}

	int nRest = nLength % sizeof(DWORD);
	BYTE * pbyRestPlain = (BYTE*)(pdwRoundPlain + nRound);
	for (int i = 0; i < nRest; i++)
	{
		if (pbyCheckSum)
		{
			*pbyCheckSum = checksumTbl[*pbyCheckSum ^ pbyRestPlain[i]];
		}

		pbyRestPlain[i] ^= (BYTE)dwCipherKey;
	}
	return nLength;
}

int Decrypt(BYTE * pPlain, int nLength, DWORD dwCipherKey, BYTE * pbyCheckSum = NULL)
{
	if (NULL == pPlain)
	{
		return 0;
	}

	if (pbyCheckSum)
	{
		*pbyCheckSum = CHECKSUM_INITIAL_VALUE;
	}

	int nRound = nLength / sizeof(DWORD);
	DWORD * pdwRoundPlain = (DWORD*)pPlain;
	for (int i = 0; i < nRound; i++)
	{
		pdwRoundPlain[i] ^= (DWORD)dwCipherKey;

		if (pbyCheckSum)
		{
			*pbyCheckSum = checksumTbl[*pbyCheckSum ^ (BYTE)pdwRoundPlain[i]];
		}
	}


	int nRest = nLength % sizeof(DWORD);
	BYTE * pbyRestPlain = (BYTE*)(pdwRoundPlain + nRound);
	for (int i = 0; i < nRest; i++)
	{
		pbyRestPlain[i] ^= (BYTE)dwCipherKey;

		if (pbyCheckSum)
		{
			*pbyCheckSum = checksumTbl[*pbyCheckSum ^ pbyRestPlain[i]];
		}
	}
	return nLength;
}

PacketEncoder::PacketEncoder(bool bSeedSwap)
{
	if (bSeedSwap)
	{
		m_rxHeaderKeyGenerator = s_txHeaderKeyGenerator;
		m_txHeaderKeyGenerator = s_rxHeaderKeyGenerator;
		m_rxBodyKeyGenerator = s_txBodyKeyGenerator;
		m_txBodyKeyGenerator = s_rxBodyKeyGenerator;
	}
	else
	{
		m_rxHeaderKeyGenerator = s_rxHeaderKeyGenerator;
		m_txHeaderKeyGenerator = s_txHeaderKeyGenerator;
		m_rxBodyKeyGenerator = s_rxBodyKeyGenerator;
		m_txBodyKeyGenerator = s_txBodyKeyGenerator;
	}
}

int PacketEncoder::RxDecrypt(void * pvPacketHeader)
{
	PACKETHEADER* pPacketHeader = (PACKETHEADER*)pvPacketHeader;
	if (pPacketHeader->bEncrypt)
	{
		Decrypt((BYTE*)pPacketHeader, HEADER_SIZE, m_rxHeaderKeyGenerator.Generate());
		pPacketHeader->bEncrypt = false;
	}
	return 0;
}

int PacketEncoder::TxEncrypt(void * pvPacketHeader)
{
	PACKETHEADER* pPacketHeader = (PACKETHEADER*)pvPacketHeader;
	if (false == pPacketHeader->bEncrypt)
	{
		Encrypt((BYTE*)pPacketHeader, HEADER_SIZE, m_txHeaderKeyGenerator.Generate());
		pPacketHeader->bEncrypt = true;
	}

	return 0;
}

int PacketEncoder::RxDecrypt(Packet& rPacket)
{
	// Decrypt Header
	RxDecrypt(rPacket.GetPacketHeader());
	// Decrypt Body
	BYTE byCheckSum = CHECKSUM_INITIAL_VALUE;
	if (rPacket.GetPacketDataSize() != Decrypt(rPacket.GetPacketData(), rPacket.GetPacketDataSize(), m_rxBodyKeyGenerator.Generate(), &byCheckSum))
	{
		return 1;
	}
	// Checksum
	Logger::Log("Rx PacketLen[%u] Sequence[%u] Checksum[%u]", rPacket.GetPacketHeader()->wPacketLen, rPacket.GetPacketHeader()->bySequence, rPacket.GetPacketHeader()->byChecksum);
	if (byCheckSum != rPacket.GetPacketHeader()->byChecksum)
	{
		return 2;
	}
	return 0;
}

int PacketEncoder::TxEncrypt(Packet& rPacket)
{
	// Encrypt Body
	BYTE byCheckSum = CHECKSUM_INITIAL_VALUE;
	if (rPacket.GetPacketDataSize() != Encrypt(rPacket.GetPacketData(), rPacket.GetPacketDataSize(), m_txBodyKeyGenerator.Generate(), &byCheckSum))
	{
		return 1;
	}
	// Checksum
	rPacket.GetPacketHeader()->byChecksum = byCheckSum;
	Logger::Log("TxEncryptPacketLen[%u] Sequence[%u] Checksum[%u]", rPacket.GetPacketHeader()->wPacketLen, rPacket.GetPacketHeader()->bySequence, rPacket.GetPacketHeader()->byChecksum);
	// Encrypt Header
	TxEncrypt(rPacket.GetPacketHeader());
	return 0;
}

RandomGen::RandomGen(unsigned int seed)
{
	Init(seed);
}

RandomGen& RandomGen::operator=(RandomGen & rRandGen)
{
	m_seed = rRandGen.m_seed;
	m_nState = rRandGen.m_nState;
	m_nIndex1 = rRandGen.m_nIndex1;
	m_nIndex2 = rRandGen.m_nIndex2;
	memcpy(m_table, rRandGen.m_table, sizeof(unsigned int) * TABLE_SIZE);
	return *this;
}

void RandomGen::Init(unsigned int seed)
{
	m_seed = seed;
	m_nState = seed;
	GenerateSeeds();
}

void RandomGen::Reset()
{
	m_nState = m_seed;
	GenerateSeeds();
}

unsigned int RandomGen::Generate()
{
	unsigned int retval = (m_table[m_nIndex1] ^= m_table[m_nIndex2]);
	m_nIndex1++;
	if (m_nIndex1 == TABLE_SIZE)
		m_nIndex1 = 0;
	m_nIndex2++;
	if (m_nIndex2 == TABLE_SIZE)
		m_nIndex2 = 0;
	return retval;
}

void RandomGen::GenerateSeeds()
{
	int n;
	unsigned int msk, bit;
	m_nIndex1 = 0;
	m_nIndex2 = 103;
	for (n = TABLE_SIZE - 1; n >= 0; n--)
		m_table[n] = GenerateSimple();
	for (n = 3, msk = 0xffffffff, bit = 0x80000000; bit; n += 7)
	{
		m_table[n] = (m_table[n] & msk) | bit;
		msk >>= 1;
		bit >>= 1;
	}
}

unsigned int RandomGen::GenerateSimple()
{
	unsigned int n, bit, temp;
	temp = m_nState;
	for (n = 0; n < 32; n++)
	{
		bit = ((temp >> 0) ^ (temp >> 1) ^ (temp >> 2) ^ (temp >> 3) ^ (temp >> 5) ^ (temp >> 7)) & 1;
		temp = (((temp >> 1) | (temp << 31)) & ~1) | bit;
	}
	m_nState = temp;
	return m_nState;
}
