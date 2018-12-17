#define MAX_BITSIZE 32
#include <iostream>

using namespace std;

class UIntPacker
{


public:

	UIntPacker()
	{
	}
	unsigned int totalBitCount = 0;
	unsigned char m_data = 0x00000000;

	unsigned char Pack(unsigned char value, unsigned int bitCount);
	unsigned char Extract(unsigned int bitCount);

	void ResetTotalBitCount();
	void Start();
};