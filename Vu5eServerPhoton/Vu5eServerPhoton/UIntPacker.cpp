#include "UIntPacker.h"

unsigned char UIntPacker::Pack(unsigned char value, unsigned int bitCount)
{
	if (totalBitCount + bitCount > MAX_BITSIZE)
	{
		return false;
	}
	else
	{
		value = value << totalBitCount;
		m_data += value;
		totalBitCount += bitCount;
		return true;
	}
}

unsigned char UIntPacker::Extract(unsigned int bitCount)
{
	unsigned char temp = m_data >> bitCount;
	temp <<= bitCount;
	unsigned char output = m_data - temp;
	m_data >>= bitCount;

	totalBitCount -= bitCount;

	return output;
}


void UIntPacker::ResetTotalBitCount()
{
	totalBitCount = 0;
}

void UIntPacker::Start()
{

}