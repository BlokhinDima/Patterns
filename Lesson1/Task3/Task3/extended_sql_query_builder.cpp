#include <string>
#include <vector>
#include <map>

#include "extended_sql_query_builder.h"


namespace query_builders
{
	ExtendedSqlSelectQueryBuilder& ExtendedSqlSelectQueryBuilder::addColumn(
		const std::string& col_name)
	{
		cols_names.push_back(col_name);
		return *this;
	}


	ExtendedSqlSelectQueryBuilder& ExtendedSqlSelectQueryBuilder::addColumns(
		const std::vector<std::string>& columns) noexcept
	{
		cols_names.insert(cols_names.end(), columns.begin(), columns.end());
		return *this;
	}


	ExtendedSqlSelectQueryBuilder& ExtendedSqlSelectQueryBuilder::addFrom(
		const std::string& table_name)
	{
		from_table = table_name;
		return *this;
	}


	ExtendedSqlSelectQueryBuilder& ExtendedSqlSelectQueryBuilder::addWhereCondition(
		const std::string& col_name, const std::string& value)
	{
		std::pair<std::string, Conditions> value_conition{ value, Conditions::EQUAL };
		where_conditions[col_name] = value_conition;
		return *this;
	}


	ExtendedSqlSelectQueryBuilder& ExtendedSqlSelectQueryBuilder::addWhereConditions(const std::map<std::string, std::string>& kv) noexcept
	{
		for (auto it = kv.begin(); it != kv.end(); it++)
		{
			auto col_name = it->first;
			auto value = it->second;
			std::pair<std::string, Conditions> value_conition{ value, Conditions::EQUAL };
			where_conditions[col_name] = value_conition;
		}
		return *this;
	}


	ExtendedSqlSelectQueryBuilder& ExtendedSqlSelectQueryBuilder::addExtendedWhereCondition
		(const std::string& col_name, const std::string& value, Conditions condition)
	{
		std::pair<std::string, Conditions> value_conition{ value, condition };
		where_conditions[col_name] = value_conition;
		return *this;
	}


	void ExtendedSqlSelectQueryBuilder::buildWhereConditions()
	{
		query += "WHERE ";

		for (auto it = where_conditions.begin(); it != where_conditions.end(); it++)
		{
			auto field = it->first;
			auto value = it->second.first;
			auto condition = it->second.second;
			
			query = query + field + getConditionChar(condition) + value;
			if (std::next(it) != where_conditions.end())
				query += " AND ";
		}
	}


	const char* ExtendedSqlSelectQueryBuilder::getConditionChar(const Conditions condition) const
	{
		switch (condition)
		{
		case query_builders::Conditions::EQUAL:
			return "=";
		case query_builders::Conditions::BIGGER:
			return ">";
		case query_builders::Conditions::LESS:
			return "<";
		default:
			break;
		}
	}
}