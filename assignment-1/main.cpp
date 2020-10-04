#include <iostream>
#include <sstream>

#include "Animal.h"
#include "Cow.h"
#include "Dog.h"
#include "Cat.h"
#include "Duck.h"

using namespace std;

/* parent animal */

// default constructor of animal
Animal::Animal() : age_in_months(0) {};

// constructor with age
Animal::Animal(int age) : age_in_months(age) {};

// virtual destructor of animal
Animal::~Animal() {};

// noise() of animal
std::string Animal::noise() {
    return "grunt";
}

// repeats() of animal's noise
int Animal::repeats() {
    return 5;
}

// ageInMonths() of animals, to be inherited
int Animal::ageInMonths() {
    return age_in_months;
}

// print() of animals, to be inherited
void Animal::print() {
    /* age print */
    std::cout << ageInMonths();

    /* noise print */
    for (int i = 0; i < repeats(); i++)
    {
        std::cout << ' ' << noise();
    }
    std::cout << std::endl;
}

/* cow */

// default constructor of cow
Cow::Cow():Animal() {};

// cow constructor with age
Cow::Cow(int age):Animal(age) {};

// noise of cow
std::string Cow::noise() {
    return "moo";
}

// repeats() of cow's noise
int Cow::repeats() {
    return 1;
}

/* dog */

// default constructor of dog
Dog::Dog():Animal() {};

// dog constructor with age
Dog::Dog(int age):Animal(age) {};

// noise() of dog
std::string Dog::noise() {
    return "woof";
}

// repeats() of dog's noise
int Dog::repeats() {
    return 2;
}

/* cat */

// default constructor of cat
Cat::Cat():Animal() {};

// cat constructor with age
Cat::Cat(int age):Animal(age) {};

// nosie() of cat
std::string Cat::noise() {
    return "meow";
}

// repeats() of cat's noise
int Cat::repeats() {
    return 1;
}

/* duck */

// default constructor of duck
Duck::Duck():Animal() {};

// duck constructor with age
Duck::Duck(int age):Animal(age) {};

// noise() of duck
std::string Duck::noise() {
    return "quack";
}

// repeats() of duck's noise
int Duck::repeats() {
    return 4;
}

/* MAIN */
int main() {
    /* create instances */
    Animal animal = Animal(12);
    Cow cow = Cow(6);
    Dog dog = Dog(14);
    Cat cat = Cat(6);
    Duck duck = Duck(20);

    /* print instances */
    animal.print();
    cow.print();
    dog.print();
    cat.print();
    duck.print();
    std::cout << std::endl;

    /* create an array of animal pointers */
    Animal* animals[10];
    animals[0] = new Animal(12);
    animals[1] = new Cat(20);
    animals[2] = new Dog(12);
    animals[3] = new Cow(11);
    animals[4] = new Cow(30);
    animals[5] = new Duck(6);
    animals[6] = new Cat(11);
    animals[7] = new Dog(40);
    animals[8] = new Duck(20);
    animals[9] = new Cat(17);

    /* run print for every animal pointer */
    for (int i = 0; i < 10; i++)
    {
        animals[i]->print();
    }
    
    /* free the memory allocated */
    for (int i = 0; i < 10; i++)
    {
        delete animals[i];
    }

}