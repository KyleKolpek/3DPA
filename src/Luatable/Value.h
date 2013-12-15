#pragma once

#include <map>
#include <string>
#include <stdexcept>

#include "Key.h"

namespace Luatable
{

class LuaState;

class Value : public std::map<Key, Value>
{
    public:
        Value();

        Value(const Value& other);
        Value(const bool value);
        Value(const char* value);
        Value(const int value);
        Value(const float value);
        Value(const double value);
        Value(const std::string& value);
        Value(const std::initializer_list<Value>& list);
        ~Value();

        Value&
        operator=(const Value& other);

        Value&
        operator[](const Key& key);

        Value
        operator[](const Key& key) const;

        friend std::ostream&
        operator<<(std::ostream& stream, const Value& value);

        std::string
        formatted() const;

        int
        getType() const;

        bool
        asBool() const;

        int
        asInt() const;

        double
        asDouble() const;

        std::string
        asString() const;

        void
        push(const Value& value);

        bool
        loadFromString(const std::string& source);

        bool
        loadFromFile(const std::string& filename);

        void
        saveToFile(const std::string& filename) const;

    private:
        Type
        type;

        bool
        b;

        std::string
        s;

        double
        n;

        static std::string
        iterateFormatted(const Value& value, const int indent);

        static void
        fillTable(LuaState& L, int index, Value& value);
};

}    //    Luatable
