#include <iostream>
#include <cassert>

#include "sql_query_builder.h"


int main()
{
    query_builders::SqlSelectQueryBuilder query_builder;
    query_builder.addColumn("name").addColumn("phone");
    query_builder.addFrom("students");
    query_builder.addWhere("id", "42").addWhere("name", "John");

    std::cout << query_builder.buildQuery() << std::endl;
    //assert(query_builder.buildQuery() == 
        //"\"SELECT name, phone FROM students WHERE id=42 AND name=John;\"");
    
    query_builder.addFrom("students");
    query_builder.addWhere("name", "John");

    std::cout << query_builder.buildQuery() << std::endl;
    //assert(query_builder.buildQuery() == 
        //"\"SELECT * FROM students WHERE name=John;\"");


    query_builder.addColumn("surname")
        .addWhere("name", "John")
        .addFrom("students")
        .addColumn("name")
        .addColumn("phone");

    std::cout << query_builder.buildQuery() << std::endl;
    //assert(query_builder.buildQuery() == 
        //"\"SELECT surname, name, phone FROM students WHERE name=John;\"");
}
