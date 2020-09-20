#include <string>

class Animal {
private:

    int age_in_months; // the age of the animal in months

public:
    // default constructor
    Animal();

    // constructor with age
    Animal(int age);

    // return noise of the animal
    virtual std::string noise();

    // return the number of times the animal repeats its noise
    int repeats();

    // return the age of the animal in months
    int ageInMonths();

    // print the ageInMonths() and the noise repeated repeats() times
    void print();
};