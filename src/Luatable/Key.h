#pragma once

#include <string>

namespace Luatable
{
    struct Key
    {
        Key(int i);
        Key(const std::string& s);
        Key(const char* s);

        bool
        operator<(const Key& other) const;

        bool
        operator==(const Key& other) const;

        friend std::ostream&
        operator<<(std::ostream& stream, const Key& key);

        private:
            std::string
            key;
    };
}    //    Luatable

