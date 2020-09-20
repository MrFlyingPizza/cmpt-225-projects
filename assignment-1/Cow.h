class Cow : public Animal {
public:
    // default constructor
    Cow();

    // constructor with age
    Cow(int age);

    // return string of noise of cow
    std::string noise();

    // return number of times cow repeats noise()
    int repeats();
};