#include <iostream>
#include <map>
#include <string>
#include <cassert>

#include "sql_query_builder.h"


int main()
{
  
    query_builders::SqlSelectQueryBuilder query_builder;
    query_builder.addColumns({ "name", "phone" });
    query_builder.addFrom("students");
    query_builder.addWhereConditions({ { "id", "42" }, { "name", "John" } });

    //std::cout << query_builder.buildQuery() << std::endl;
    assert(query_builder.buildQuery() == 
        "\"SELECT name, phone FROM students WHERE id=42 AND name=John;\"");
    
    query_builder.addFrom("students");
    query_builder.addWhereCondition("name", "John");

    //std::cout << query_builder.buildQuery() << std::endl;
    assert(query_builder.buildQuery() == 
        "\"SELECT * FROM students WHERE name=John;\"");

    query_builder.addColumn("surname")
        .addWhereCondition("name", "John")
        .addFrom("students")
        .addColumns({ "name", "phone" })
        .addWhereConditions({ { "id", "42" }, { "name", "John" } });

    //std::cout << query_builder.buildQuery() << std::endl;
    assert(query_builder.buildQuery() == 
        "\"SELECT surname, name, phone FROM students WHERE id=42 AND name=John;\"");
}
