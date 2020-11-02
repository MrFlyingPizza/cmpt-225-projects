#ifndef ENTRY_H
#define ENTRY_H

class Entry {
private:
    int key_;
    std::string value_;
public:
    Entry(int key = 0, std::string value = "");

    int getKey() const;
    std::string getValue() const;
    std::string toString() const;
    
    void random();
};

#endif