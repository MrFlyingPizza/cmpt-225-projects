#include <string>

#include "Entry.h"

const Entry Entry::END_ENTRY = Entry(InfKey::END);
const Entry Entry::P_INF = Entry(InfKey::PLUS);
const Entry Entry::M_INF = Entry(InfKey::MINUS);

Entry::Entry(const InfKey inf_key)
: inf_key_(inf_key), key_(inf_key), value_("###")
{}

Entry::Entry(const int key, const std::string value)
: inf_key_(NONE), key_(key), value_(value)
{}

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
    if (this->inf_key_ == InfKey::END)
        return std::string("(END)");
    
    if (this->inf_key_ == InfKey::MINUS)
        return std::string("(M_INF)");
    
    if (this->inf_key_ == InfKey::PLUS)
        return std::string("(P_INF)");
    
    std::string result("(");
    return result.append(std::to_string(key_)).append(", ").append(value_).append(")");
}

void Entry::random()
{
    key_ = rand()%100;
    char c_str[4] = {0};
    for (short i = 0; i < 3; i++) c_str[i] = 'a'+rand()%26;
    value_ = std::string(c_str);
}

bool Entry::operator<(Entry const& entry) const
{
    return (entry.inf_key_ != 0 || inf_key_ != 0) ? (inf_key_ < entry.inf_key_) : (key_ < entry.key_);
}

bool Entry::operator>(Entry const& entry) const
{
    return (entry.inf_key_ != 0 || inf_key_ != 0) ? (inf_key_ > entry.inf_key_) : (key_ > entry.key_);
}

bool Entry::operator==(Entry const& entry) const
{
    return (entry.inf_key_ != 0 || inf_key_ != 0) ? (inf_key_ == entry.inf_key_) : (key_ == entry.key_);
}

bool Entry::operator!=(Entry const& entry) const
{
    return !(*this == entry);
}

bool Entry::operator<=(Entry const& entry) const
{
    return !(*this > entry);
}

bool Entry::operator>=(Entry const& entry) const
{
    return !(*this < entry);
}

bool Entry::isKeyEqual(int const& n) const
{
    return (inf_key_ != Entry::InfKey::NONE) ? false : key_ == n;
}

bool Entry::isKeyLessThan(int const& n) const
{
    if (inf_key_ == Entry::InfKey::PLUS || inf_key_ == Entry::InfKey::END)
        return false;
    else if (inf_key_ == Entry::InfKey::MINUS)
        return true;
    else
        return key_ < n;
}

bool Entry::isKeyGreaterThan(int const& n) const
{
    if (inf_key_ == Entry::InfKey::PLUS)
        return true;
    else if (inf_key_ == Entry::InfKey::MINUS || inf_key_ == Entry::InfKey::END)
        return false;
    else
        return key_ > n;
}