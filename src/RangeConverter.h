#ifndef RANGE_CONVERTER_H
#define RANGE_CONVERTER_H

#include <map>
#include <string>
#include "InputConstants.h"

class RangeConverter
{
private:
    struct Converter
    {
        double minInput;
        double maxInput;
        double minOutput;
        double maxOutput;
        
        template <typename RangeType>
        RangeType convert(RangeType invalue) const
        {
            double v = static_cast<double>(invalue);
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

    typedef std::map<Input::Range, Converter> ConversionMapT;

public:
    explicit RangeConverter(std::string const &s);

    template <typename RangeType>
    RangeType convert(Input::Range rangeID, RangeType invalue) const
    {
        ConversionMapT::const_iterator iter = converters.find(rangeID);
        if(iter == converters.end())
        {
            return invalue;
        }
        return iter->second.convert<RangeType>(invalue);
    }

private:
    ConversionMapT converters;
};

#endif
