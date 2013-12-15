#pragma once

#include <string>

namespace Luatable
{
    enum Type
    {
        None,
        Boolean,
        Number,
        String
    };

    struct Key
    {
        Key(double d);
        Key(bool b);
        Key(const std::string& s);
        Key(const char* s);

        double asNumber() const;
        int asInt() const;
        bool asBool() const;
        std::string asString() const;
        
        bool
        operator<(const Key& other) const;

        bool
        operator==(const Key& other) const;

        friend std::ostream&
        operator<<(std::ostream& stream, const Key& key);

        private:
            bool boolKey;
            double numKey;
            std::string strKey;

            Type type;
    };
}    //    Luatable

