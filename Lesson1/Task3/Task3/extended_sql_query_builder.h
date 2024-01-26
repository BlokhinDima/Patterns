#pragma once

#include <map>
#include <utility>

#include "sql_query_builder.h"


namespace query_builders
{
	enum class Conditions
	{
		EQUAL,
		BIGGER,
		LESS,
	};

	class ExtendedSqlSelectQueryBuilder : public SqlSelectQueryBuilder
	{
	public:
		ExtendedSqlSelectQueryBuilder& addColumn(const std::string& col_name);
		ExtendedSqlSelectQueryBuilder& addColumns(const std::vector<std::string>& columns) noexcept;
		ExtendedSqlSelectQueryBuilder& addFrom(const std::string& table_name);
		ExtendedSqlSelectQueryBuilder& addWhereCondition(const std::string& col_name, const std::string& value);
		ExtendedSqlSelectQueryBuilder& addWhereConditions(const std::map<std::string, std::string>& kv) noexcept;
		ExtendedSqlSelectQueryBuilder& addExtendedWhereCondition
			(const std::string& col_name, const std::string& value, const Conditions condition);

	private:
		std::map<std::string, std::pair<std::string, Conditions>> where_conditions;
		const char* getConditionChar(const Conditions condition) const;
		void buildWhereConditions() override;
	};
}