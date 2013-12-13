#include "Value.h"
#include "Key.h"

#include <fstream>
#include <sstream>
#include "lua/lua.hpp"

namespace
{
	static std::string
	indented(const int indent)
	{
		std::string result;

		for (int i = indent; i > 0; --i)
		{
			result += "\t";
		}

		return result;
	}

	static std::string
	quoted(const std::string& in)
	{
		return "\"" + in + "\"";
	}
}

namespace Luatable
{
	class LuaState
	{
		public:
			LuaState()
			{
				state = luaL_newstate();
			}

			~LuaState()
			{
				lua_close(state);
			}

			operator lua_State*()
			{
				return state;
			}

			lua_State*
			state;
	};
}

namespace Luatable
{
	Value::Value()
	{
		type = None;
	}

	Value::Value(const Value& other)
	{
		*this = other;
	}

	Value::Value(const bool value)
	{
		b = value;
		type = Boolean;
	}

	Value::Value(const char* value)
	{
		s = value;
		type = String;
	}

	Value::Value(const int value)
	{
		n = value;
		type = Number;
	}

	Value::Value(const float value)
	{
		n = value;
		type = Number;
	}

	Value::Value(const double value)
	{
		n = value;
		type = Number;
	}

	Value::Value(const std::string& value)
	{
		s = value;
		type = String;
	}

	Value::Value(const std::initializer_list<Value>& list)
	{
		for (auto& it : list)
		{
			push(it);
		}
	}

	Value::~Value()
	{
	}

	Value&
	Value::operator=(const Value& other)
	{
		type = other.type;
		b = other.b;
		s = other.s;
		n = other.n;

		clear();

		for (auto& p : other)
		{
			(*this)[p.first] = p.second;
		}

		return *this;
	}

	Value&
	Value::operator[](const Key& key)
	{
		return std::map<Key, Value>::operator[](key);
	}

	Value
	Value::operator[](const Key& key) const
	{
		auto it = find(key);
		if (it == end())
		{
			return Value();
		}

		return it->second;
	}

	std::ostream&
	operator<<(std::ostream& stream, const Value& value)
	{
		stream << value.formatted();
		return stream;
	}

	bool
	Value::loadFromString(const std::string& source)
	{
		LuaState L;

		if (luaL_dofile(L, source.c_str()) == 1)
		{
			return false;
		}

		lua_pushglobaltable(L);
		fillTable(L, -1, *this);

		return true;
	}

	bool
	Value::loadFromFile(const std::string& file)
	{
		LuaState L;

		if (luaL_dofile(L, file.c_str()) == 1)
		{
			return false;
		}

		lua_pushglobaltable(L);
		fillTable(L, -1, *this);

		return true;
	}

	void
	Value::saveToFile(const std::string& filename) const
	{
		std::ofstream out(filename);
		out << formatted();
	}

	int
	Value::getType() const
	{
		return type;
	}

	bool
	Value::asBool() const
	{
		switch (type)
		{
			case Value::Number:
			{
				return static_cast<bool>(n);
			}
			case Value::String:
			{
				return (s == "true");
			}
			case Value::Boolean:
			{
				return b;
			}
			default:
			{
				//	Wrong
				break;
			}
		}

		return false;
	}

	int
	Value::asInt() const
	{
		switch (type)
		{
			case Value::Number:
			{
				return static_cast<int>(n);
			}
			case Value::String:
			{
				int result;
				return (std::stringstream(s) >> result) ? result : 0;
			}
			case Value::Boolean:
			{
				return b ? 1 : 0;
			}
			default:
			{
				//	Wrong
				break;
			}
		}

		return 0;
	}

	double
	Value::asDouble() const
	{
		switch (type)
		{
			case Value::Number:
			{
				return n;
			}
			case Value::String:
			{
				double result;
				return (std::stringstream(s) >> result) ? result : 0;
			}
			case Value::Boolean:
			{
				return b ? 1 : 0;
			}
			default:
			{
				//	Wrong
				break;
			}
		}

		return 0;
	}

	std::string
	Value::asString() const
	{
		switch (type)
		{
			case Value::Number:
			{
				std::stringstream ss;
				ss << n;
				return ss.str();
			}
			case Value::String:
			{
				return s;
			}
			case Value::Boolean:
			{
				return b ? "true" : "false";
			}
			default:
			{
				//	Wrong
				break;
			}
		}

		return "";
	}

	std::string
	Value::formatted() const
	{
		return iterateFormatted(*this, 0);
	}

	std::string
	Value::iterateFormatted(const Value& value, const int indent)
	{
		std::stringstream stream;

		if (value.size() > 0 || value.type == Array)
		{
			//	Stream a table begin
			if (indent > 0)
			{
				stream << "{\n";
			}

			if (value.type == Array)
			{
				for (unsigned i = 0; i < value.size(); ++i)
				{
					//	Set the initial indent
					stream << indented(indent);

					//	Process any children this table has
					stream << iterateFormatted(value.at(i), indent + 1);

					//	Commas are required between elements, but not after the last one
					if (indent > 0 && i < value.size() - 1)
					{
						stream << ", ";
					}

					stream << "\n";
				}
			}
			else
			{
				unsigned count = 0;
				for (auto& pair : value)
				{
					///	pair.first is the key, which is a string
					///	pair.second is the value, which may be a table

					//	Set the initial indent
					stream << indented(indent);

					//	Stream the key
					stream << pair.first << " = ";

					//	Process any children this table has
					stream << iterateFormatted(pair.second, indent + 1);

					//	Commas are required between elements, but not after the last one
					if (indent > 0 && count < value.size() - 1)
					{
						stream << ", ";
					}

					stream << "\n";
					++count;
				}
			}

			//	Stream a table end
			if (indent > 0)
			{
				stream << indented(indent - 1);
				stream << "}";
			}
		}
		else
		{
			switch (value.type)
			{
				case Boolean:
					stream << std::boolalpha << value.b;
					break;
				case Number:
					stream << value.n;
					break;
				case String:
					stream << quoted(value.s);
					break;
				default:
					break;
					//	wrong
			}
		}

		return stream.str();
	}

	void
	Value::push(const Value& value)
	{
		if (type != Type::Array)
		{
			clear();
			type = Type::Array;
		}

		(*this)[size()] = value;

	}

	void
	Value::fillTable(LuaState& L, int index, Value& value)
	{
		//	Push a reference to the table on to the top of the stack
		lua_pushvalue(L, index);

		//	Push a nil value onto the stack after the table
		//	When the iterator is nil, we know the table is empty and we can stop
		lua_pushnil(L);

		while (lua_next(L, -2))
		{
			std::string key = "";

			lua_pushvalue(L, -2);

			key = lua_tostring(L, -1);

			if (lua_istable(L, -2))
			{
				//	If the indeces are numbers, it's a plain array, not an associative one
				if (lua_isnumber(L, -1))
				{
					Value next;

					fillTable(L, -2, next);

					value.push(next);
				}
				else
				{
					fillTable(L, -2, value[key]);
				}
			}
			else
			{
				key = lua_tostring(L, -1);

				if (lua_isboolean(L, -2))
				{
					//	Read in a boolean value
					if (lua_isnumber(L, -1))
					{
						value.push(static_cast<bool>(lua_toboolean(L, -2)));
					}
					else
					{
						value[key] = static_cast<bool>(lua_toboolean(L, -2));
					}
				}
				else if (lua_isnumber(L, -2))
				{
					//	Read in a number value
					if (lua_isnumber(L, -1))
					{
						value.push(lua_tonumber(L, -2));
					}
					else
					{
						value[key] = lua_tonumber(L, -2);
					}
				}
				else if (lua_isstring(L, -2))
				{
					//	Read in a string value
					if (lua_isnumber(L, -1))
					{
						value.push(lua_tostring(L, -2));
					}
					else
					{
						value[key] = lua_tostring(L, -2);
					}
				}
			}

			lua_pop(L, 2);
		}
		lua_pop(L, 1);
	}
}	//	Luatable
