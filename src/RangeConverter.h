#ifndef RANGE_CONVERTER_H
#define RANGE_CONVERTER_H

#include <map>
#include "InputConstants.h"

class RangeConverter
{
private:
    struct Converter
    {
        float minInput;
        float maxInput;
        float minOutput;
        float maxOutput;
        
        template <typename RangeType>
        RangeType Convert(RangeType invalue) const
        {
            float v = static_cast<float>(invalue);
            if(v < minInput)
            {
                v = minInput;
            }
            if(v > maxInput)
            {
                v = maxInput;
            }
            double interpFactor = (v - minInput) / (maxInput - minInput);
            return static_cast<RangeType>(
                (interpFactor * (maxOutput - minOutput)) + minOutput);
        }
    };

    typedef std::map<Range, Converter> ConversionMapT;

public:
    explicit RangeConverter();

    template <typeName RangeType>
    RangeType Convert(Range rangeID, RangeType invalue) const
    {
        ConversionMapT::const_iterator iter = converters.find(rangeID);
        if(iter == converters.end())
        {
            return invalue;
        }
        return iter->second.Convert<RangeType>(invalue);
    }

private:
    ConversionMapT converters;
};

#endif
