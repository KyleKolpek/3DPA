#include "MortonNumber.h"


#define BITS_PER_DIMENSION 21
#define MSB_MASK   0x00100000
#define LSBS_MASK  0x000FFFFF
#define INT21_MASK 0x001FFFFF

MortonNumber::MortonNumber():value(0)
{
}

MortonNumber::MortonNumber(uint64_t value):value(value)
{
}

bool MortonNumber::operator<(const MortonNumber& m) const
{
    return value < m.value;
}

void MortonNumber::setX(int32_t x)
{
    value = (value & 0xB6DB6DB6DB6DB6DB) |
        (spreadBits(convertToUInt64(convertTo21BitAndXorMSB(x))) << 2);
}

void MortonNumber::setY(int32_t y)
{
    value = (value & 0xDB6DB6DB6DB6DB6D) |
    (spreadBits(convertToUInt64(convertTo21BitAndXorMSB(y))) << 1);
}

void MortonNumber::setZ(int32_t z)
{
    value = (value & 0xEDB6DB6DB6DB6DB6) |
    spreadBits(convertToUInt64(convertTo21BitAndXorMSB(z)));
}

// Moves the MSB to it's new position (21st bit). Then flip the new MSB and
// keep the remaining 20 LSBs.
int32_t MortonNumber::convertTo21BitAndXorMSB(int32_t number) const
{
    return (((number >> 32 - BITS_PER_DIMENSION)
           & MSB_MASK) ^ MSB_MASK) | (number & LSBS_MASK);
}

// NOTE: This version is ~2% faster in tests with -O0, but ~1% slower with
// -O3, and <1% slower with -O2. Also, this one should not be affected by
// endianness.
int32_t MortonNumber::convertTo21BitAndXorMSBv2(int32_t number) const
{
    return (number + (1 << (BITS_PER_DIMENSION - 1))) & 0x001FFFFF;
}

uint64_t MortonNumber::convertToUInt64(int32_t number) const
{
    Custom64 c;
    c.whole = 0;
    c.half.low = number;
    return c.whole;
}

uint64_t MortonNumber::spreadBits(int64_t number) const
{
    uint64_t v = number;
    v = (v | (v << 32)) & 0x7fff00000000ffff; 
    v = (v | (v << 16)) & 0x00ff0000ff0000ff; 
    v = (v | (v <<  8)) & 0x700f00f00f00f00f; 
    v = (v | (v <<  4)) & 0x30c30c30c30c30c3; 
    v = (v | (v <<  2)) & 0x1249249249249249;
    return v;
}
