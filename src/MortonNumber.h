#ifndef MORTONNUMBER_H
#define MORTONNUMBER_H

#include <climits>
#include <cstdint>

#define BITS_PER_DIMENSION 21
#define MSB_MASK  0x00100000
#define LSBS_MASK 0x000FFFFF


// TODO: See if this actually works how I think it does
#define IS_LITTLE_ENDIAN (1 == *(unsigned char *)&(const int){1})

#ifdef IS_LITTLE_ENDIAN
struct uint64_as_int32_t
{
    int32_t low;
    int32_t hi;
};
#else
struct uint64_as_int32_t
{
    int32_t hi;
    int32_t low;
};
#endif

union Custom64
{
    uint64_as_int32_t half;
    uint64_t whole;
};

class MortonNumber
{
public:

    MortonNumber():value(0)
    {
    }
    MortonNumber(uint64_t value):value(value)
    {
    }
    bool operator<(const MortonNumber& m) const
    {
        return value < m.value;
    }
    void setX(int32_t x)
    {
        value = (value & 0xB6DB6DB6DB6DB6DB) |
        (spreadBits(convertToUInt64(convertTo21BitAndXorMSB(x))) << 2);
    }
    void setY(int32_t y)
    {
        value = (value & 0xDB6DB6DB6DB6DB6D) |
        (spreadBits(convertToUInt64(convertTo21BitAndXorMSB(y))) << 1);
    }
    void setZ(int32_t z)
    {
        value = (value & 0xEDB6DB6DB6DB6DB6) |
        spreadBits(convertToUInt64(convertTo21BitAndXorMSB(z)));
    }
private:
    int32_t convertTo21BitAndXorMSB(int32_t number) const
    {
        // Move the MSB to it's new position (21st bit) then flip the new MSB
        // and keep the remaining 20 LSBs.
        // NOTE: This *should* effictively round numbers to a 21 bit range.
        return (((number >> 32 - BITS_PER_DIMENSION)
               & MSB_MASK) ^ MSB_MASK) | (number & LSBS_MASK);

    }
    uint64_t convertToUInt64(int32_t number) const
    {
        Custom64 c;
        c.whole = 0;
        c.half.low = number;
        return c.whole;
    }
    uint64_t spreadBits(int64_t number) const
    {
        uint64_t v = number;
        v = (v | (v << 32)) & 0x7fff00000000ffff; 
        v = (v | (v << 16)) & 0x00ff0000ff0000ff; 
        v = (v | (v <<  8)) & 0x700f00f00f00f00f; 
        v = (v | (v <<  4)) & 0x30c30c30c30c30c3; 
        v = (v | (v <<  2)) & 0x1249249249249249;
        return v;
    }
    uint64_t value;

};

#endif
