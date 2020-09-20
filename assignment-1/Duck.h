class Duck : public Animal {
public:
    // default constructor
    Duck();

    // constructor with age
    Duck(int age);

    // return string of noise of duck
    std::string noise();

    // return number of times duck repeats noise()
    int repeats();
};