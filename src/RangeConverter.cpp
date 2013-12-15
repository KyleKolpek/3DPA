#include <iostream>
#include <string>
#include "RangeConverter.h"
#include "Luatable/Value.h"

using namespace Input;

RangeConverter::RangeConverter(std::string const &s)
{
    Luatable::Value converterTable;
    if(!converterTable.loadFromFile("../assets/input/rangeConverters/" + s))
    {
        std::cerr << "Error opening input converter file \""
                  << s << "\"" << std::endl;
    }

    std::map<Luatable::Key, Luatable::Value>::iterator i;
    for(i = converterTable.begin(); i != converterTable.end(); i++)
    {
        Converter converter;
        converter.minInput  = i->second["minInput"].asDouble();
        converter.maxInput  = i->second["maxInput"].asDouble();
        converter.minOutput = i->second["minOutput"].asDouble();
        converter.maxOutput = i->second["maxOutput"].asDouble();
        converters.insert(std::make_pair(static_cast<Range>(i->first.asInt()),
                                         converter));
    }
    // TODO: Add range conversions here
}
