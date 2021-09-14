#pragma once
#include <variant>
#include <map>
#include <yaml-cpp/yaml.h>
#include "logs.h"
namespace shelllet {
	enum Columns {
		Name,
		Type,
		Value,
		Ref, // ref count
		Desc,
		Count
	};
	struct Var {
		std::string name;
		std::string type;
		std::string value; // js data types[https://developer.mozilla.org/en-US/docs/Web/JavaScript/Data_structures]
		std::int32_t ref;
		std::string desc;

		static inline std::map<Columns, std::string> keys = { {Name, "name"}, {Type, "type"}, {Value, "value"}, {Ref, "ref"}, {Desc, "desc"} };
	};
}
namespace YAML {
	using namespace shelllet;
	template<>
	struct convert<Var> {
		static Node encode(const Var& rhs) {
			Node node;
			node[Var::keys[Name]] = rhs.name;
			node[Var::keys[Type]] = rhs.type;
			node[Var::keys[Columns::Value]] = rhs.value;
			node[Var::keys[Ref]] = rhs.ref;
			node[Var::keys[Desc]] = rhs.desc;

			return node;
		}

		static bool decode(const Node& node, Var& rhs) {
			try
			{
				rhs.name = node[Var::keys[Name]].as<std::string>();
			}
			catch (const std::exception& err)
			{
				LOG_FATAL("rpa") << "# parse variables error: " << err.what();
			}

			try
			{
				rhs.type = node[Var::keys[Type]].as<std::string>();
			}
			catch (const std::exception& err)
			{
				LOG_FATAL("rpa") << "# parse variables error: " << err.what();
			}
			try
			{
				rhs.value = node[Var::keys[Columns::Value]].as<std::string>();
			}
			catch (const std::exception& err)
			{
				LOG_FATAL("rpa") << "# parse variables error: " << err.what();
			}
			try
			{
				rhs.ref = node[Var::keys[Ref]].as<std::int32_t>();
			}
			catch (const std::exception& err)
			{
				rhs.ref = 0;
				LOG_FATAL("rpa") << "# parse variables error: " << err.what();
			}
			try
			{
				rhs.desc = node[Var::keys[Desc]].as<std::string>();
			}
			catch (const std::exception& err)
			{
				LOG_FATAL("rpa") << "# parse variables error: " << err.what();
			}

			return true;
		}
	};
}
