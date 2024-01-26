#include <iostream>
#include <string>
#include <cassert>

#include "sql_query_builder.h"
#include "extended_sql_query_builder.h"


int main()
{
    query_builders::SqlSelectQueryBuilder query_builder;
    query_builder.addColumns({ "name", "phone" });
    query_builder.addFrom("students");
    query_builder.addWhereConditions({ {"id", "42"}, {"name", "John"} });

    //std::cout << query_builder.buildQuery() << std::endl;
    assert(query_builder.buildQuery() == 
        "\"SELECT name, phone FROM students WHERE id=42 AND name=John;\"");
    

    query_builders::ExtendedSqlSelectQueryBuilder extended_query_builder;
    extended_query_builder.addColumn("surname")
        .addExtendedWhereCondition("id", "42", query_builders::Conditions::BIGGER)
        .addFrom("students")
        .addColumns({ "name", "phone" })
        .addWhereConditions({ {"name", "John"} });

    //std::cout << extended_query_builder.buildQuery() << std::endl;
    assert(extended_query_builder.buildQuery() ==
        "\"SELECT surname, name, phone FROM students WHERE id>42 AND name=John;\"");
}
