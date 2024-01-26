#pragma once

#include <string>
#include <vector>
#include <map>


namespace query_builders
{
	class SqlSelectQueryBuilder
	{
	public:
		SqlSelectQueryBuilder& addColumn(const std::string& col_name);
		SqlSelectQueryBuilder& addFrom(const std::string& table_name);
		SqlSelectQueryBuilder& addWhere(const std::string& col_name, const std::string& value);
		std::string buildQuery();

	private:
		std::string query{};
		std::vector<std::string> cols_names{};
		std::string from_table{};
		std::map<std::string, std::string> where_conditions{};
		void buildSelect();
		void buildFrom();
		void buildWhereConditions();
		void reset();
	};
}