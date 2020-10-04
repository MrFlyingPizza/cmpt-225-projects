// Employee.cpp

#include "Employee.h"

/* Constructs an employee object with given name & id,
name defaults to 'unknown' and id defaults to '-1' */
Employee::Employee(const std::string name, const int id)
: employee_name(name), employee_id(id)
{}

/* returns employee name */
std::string Employee::getName() const
{
    return employee_name;
}

/* returns employee id */
int Employee::getId() const
{
    return employee_id;
}

/* returns a string of employee name followed by id */
std::string Employee::toString() const
{
    return employee_name + ' ' + std::to_string(employee_id);
}