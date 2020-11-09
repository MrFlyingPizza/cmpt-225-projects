#include <string>

#include "Entry.h"
#include "SkipList.h"


const Entry Entry::MINUS_INF = Entry(-2);
const Entry Entry::PLUS_INF = Entry(-1);
const Entry Entry::END = Entry(-3);


Entry::Entry()
: key_(0), value_("")
{}

Entry::Entry(const int inf_key)
: key_(inf_key), value_("")
{}

Entry::Entry(const int key, const std::string value)
: key_(key), value_(value)
{
    if (key < 0) throw NegativeKeyException();
}

int Entry::getKey() const
{
    return key_;
}

std::string Entry::getValue() const
{
    return value_;
}

std::string Entry::toString() const
{
    std::string result("(");
    return result.append(std::to_string(key_)).append(", ").append(value_).append(")");
}

void Entry::random()
{
    key_ = rand() % 100;
    char c_str[4] = {0};
    for (short i = 0; i < 3; i++) c_str[i] = 'a'+rand()%26;
    value_ = std::string(c_str);
}