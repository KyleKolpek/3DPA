#include "Key.h"

#include <sstream>

namespace Luatable
{
    Key::Key(double d):
        boolKey(false),
        numKey(d),
        strKey(""),
        type(Number)
    {
    }
    Key::Key(bool b):
        boolKey(b),
        numKey(0),
        strKey(""),
        type(Boolean)
    {
    }

    Key::Key(const std::string& s):
        boolKey(false),
        numKey(0),
        strKey(s),
        type(String)
    {
    }

    Key::Key(const char* s):
        boolKey(false),
        numKey(0),
        strKey(s),
        type(String)
    {
    }

    double
    Key::asDouble() const
    {
        return numKey;
    }

    int
    Key::asInt() const
    {
        return static_cast<int>(numKey);
    }

    bool
    Key::asBool() const
    {
        return boolKey;
    }

    std::string
    Key::asString() const
    {
        return strKey;
    }

    bool
    Key::operator<(const Key& other) const
    {
        if(type != other.type)
        {
            return type < other.type;
        }
        switch(type)
        {
            case Boolean:
                return boolKey < other.boolKey;
            case Number:
                return numKey < other.numKey;
            case String:
                return strKey < other.strKey;
            default:
                // I don't think this should happen
                return 0;
        }
    }

    bool
    Key::operator==(const Key& other) const
    {
        if(type != other.type)
        {
            return false;
        }
        switch(type)
        {
            case Boolean:
                return boolKey == other.boolKey;
            case Number:
                return numKey == other.numKey;
            case String:
                return strKey == other.strKey;
            default:
                // I don't think this should happen
                return false;
        }
    }

    std::ostream&
    operator<<(std::ostream& stream, const Key& key)
    {
        switch(key.type)
        {
            case Boolean:
                stream << std::boolalpha << key.boolKey;
            case Number:
                stream << key.numKey;
            case String:
                stream << "\"" << key.strKey << "\"";
            default:
                stream << "null";
        }
        return stream;
    }
}    //    Luatable
