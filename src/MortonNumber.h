#ifndef MORTONNUMBER_H
#define MORTONNUMBER_H

#include <climits>
#include <cstdint>

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

    MortonNumber();
    MortonNumber(uint64_t value);
    MortonNumber(int32_t x, int32_t y, int32_t z);
    bool operator<(const MortonNumber& m) const;
    void setX(int32_t x);
    void setY(int32_t y);
    void setZ(int32_t z);
private:
    uint64_t value;

    int32_t convertTo21BitAndXorMSB(int32_t number) const;
    int32_t convertTo21BitAndXorMSBv2(int32_t number) const;
    uint64_t convertToUInt64(int32_t number) const;
    uint64_t spreadBits(int64_t number) const;

};

#endif
