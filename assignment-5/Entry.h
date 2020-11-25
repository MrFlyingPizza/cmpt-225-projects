#ifndef ENTRY_H
#define ENTRY_H

#include <string>

class Entry {
    friend class SkipList;
private:
    enum InfKey
    {
        NONE = 0,
        PLUS = 1,
        MINUS = -1,
        END = -2
    };

    InfKey inf_key_;

    int key_;
    std::string value_;

    explicit Entry(InfKey inf_key);
    
public:
    const static Entry END_ENTRY;
    const static Entry M_INF;
    const static Entry P_INF;

    Entry(int key = 0, std::string value = "");

    int getKey() const;
    std::string getValue() const;
    std::string toString() const;
    
    void random();

    bool operator>(Entry const& entry) const;
    bool operator<(Entry const& entry) const;
    bool operator==(Entry const& entry) const;
    bool operator!=(Entry const& entry) const;
    bool operator>=(Entry const& entry) const;
    bool operator<=(Entry const& entry) const; 

    bool isKeyEqual(int const& n) const;
    bool isKeyLessThan(int const& n) const;
    bool isKeyGreaterThan(int const& n) const;
};

#endif