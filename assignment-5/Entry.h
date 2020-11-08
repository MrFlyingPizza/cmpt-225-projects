#ifndef ENTRY_H
#define ENTRY_H

class Entry {
    friend class SkipList;

    const static Entry MINUS_INF;
    const static Entry PLUS_INF;
    const static Entry END;
private:
    int key_;
    std::string value_;

    Entry(int inf_key);
public:
    Entry(int key, std::string value);
    Entry();

    int getKey() const;
    std::string getValue() const;
    std::string toString() const;
    
    void random();
};

class NegativeKeyException {};

#endif