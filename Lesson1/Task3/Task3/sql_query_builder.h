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
		SqlSelectQueryBuilder& addColumns(const std::vector<std::string>& columns) noexcept;
		SqlSelectQueryBuilder& addFrom(const std::string& table_name);
		SqlSelectQueryBuilder& addWhereCondition(const std::string& col_name, const std::string& value);
		SqlSelectQueryBuilder& addWhereConditions(const std::map<std::string, std::string>& kv) noexcept;
		std::string buildQuery();

	protected:
		std::string query{};
		std::vector<std::string> cols_names{};
		std::string from_table{};
		std::map<std::string, std::string> where_conditions{};
		void buildSelect();
		void buildFrom();
		virtual void buildWhereConditions();
		void reset();
	};
}