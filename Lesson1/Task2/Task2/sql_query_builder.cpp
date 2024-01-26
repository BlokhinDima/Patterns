#include <string>

#include "sql_query_builder.h"


namespace query_builders
{
	
	std::string SqlSelectQueryBuilder::buildQuery()
	{
		buildSelect();
		buildFrom();
		buildWhereConditions();
		query += ";\"";
		auto result = query;
		reset();
		return result;
	}

	void SqlSelectQueryBuilder::reset()
	{
		cols_names.clear();
		where_conditions.clear();
		from_table = "";
		query = "";
	}

	void SqlSelectQueryBuilder::buildSelect()
	{
		query += "\"SELECT ";

		if (cols_names.size() == 0)
		{
			query += "* ";
		}
		else
		{
			for (auto it = cols_names.begin(); it != cols_names.end(); it++)
			{
				query += *it;
				if (it != cols_names.end() - 1)
				{
					query += ", ";
				}	
			}
			query += " ";
		}
	}

	void SqlSelectQueryBuilder::buildFrom()
	{
		query = query + "FROM " + from_table + " ";
	}

	void SqlSelectQueryBuilder::buildWhereConditions()
	{
		query += "WHERE ";

		for (auto it = where_conditions.begin(); it != where_conditions.end(); it++)
		{
			query = query + it->first + "=" + it->second;
			if (std::next(it) != where_conditions.end())
				query += " AND ";
		}
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::addColumn(const std::string& col_name)
	{
		cols_names.push_back(col_name);
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::addColumns(const std::vector<std::string>& columns) noexcept
	{
		cols_names.insert(cols_names.end(), columns.begin(), columns.end());
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::addFrom(const std::string& table_name)
	{
		from_table = table_name;
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::addWhereCondition(const std::string& col_name, const std::string& value)
	{
		where_conditions[col_name] = value;
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::addWhereConditions(const std::map<std::string, std::string>& kv) noexcept
	{
		where_conditions.insert(kv.begin(), kv.end());
		return *this;
	}
}
