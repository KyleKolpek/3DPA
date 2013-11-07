#include "RangeConverter.h"

using namespace Input;

RangeConverter::RangeConverter()
{
    // TODO: Add range conversions here
    Converter converter;

    converter.minInput = -512.0;
    converter.maxInput = 512.0;
    converter.minOutput = -180;
    converter.maxOutput = 180;

    converters.insert(std::make_pair(RANGE_ROTATE_CAMERA_X, converter));
    converters.insert(std::make_pair(RANGE_ROTATE_CAMERA_Y, converter));
}
