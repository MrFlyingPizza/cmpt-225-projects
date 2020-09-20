class Dog : public Animal {
public:
    // default constructor
    Dog();

    // constructor with age
    Dog(int age);
    
    // return string of noise of dog
    std::string noise();

    // return number of times dog repeats noise()
    int repeats();
};