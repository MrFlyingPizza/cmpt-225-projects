// Employee.h
#include <string>

class Employee {

private:

    std::string employee_name;
    int employee_id;

public:
    /* Constructs an employee object with given name & id,
    name defaults to 'unknown' and id defaults to '-1' */
    Employee(const std::string name = "unknown", const int id = -1);

    /* getters */
    std::string getName() const;
    int getId() const;

    std::string toString() const;
};