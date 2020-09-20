class Cat : public Animal {
public:
    // default constructor
    Cat();

    // constructor with age
    Cat(int age);

    // return string of noise of cat
    std::string noise();

    // return number of times cat repeats noise()
    int repeats();
};