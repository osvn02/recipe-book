#include "name.h"
using namespace std;

Name::Name(){}

Name::Name(const Name& n) : first(n.first), last(n.last){}

string Name::getFirst() const
{
    return first;
}

string Name::getLast() const
{
    return last;
}

void Name::setFirst(const std::string& s)
{
    first = s;
}

void Name::setLast(const std::string& s)
{
    last = s;
}

string Name::toString() const
{
    string result;
    result += first;
    result += " ";
    result += last;
    return result;
}

Name& Name::operator=(const Name& n)
{
    first = n.first;
    last = n.last;
    return *this;
}

bool Name::operator==(const Name& n) const
{
    return *this == n;
}

bool Name::operator!=(const Name& n) const
{
    return *this != n;
}

bool Name::operator<(const Name& n) const
{
    return *this < n;
}

bool Name::operator>(const Name& n) const
{
    return *this > n;
}

bool Name::operator<=(const Name& n) const
{
    return (*this < n) or (*this == n);
}

bool Name::operator>=(const Name& n) const
{
    return (*this > n) or (*this == n);
}

int Name::compareByFirst(const Name& n1, const Name& n2)
{
    int result;
    result = n1.first.compare(n2.first);
    return result;
}

int Name::compareByLast(const Name& n1, const Name& n2)
{
    int result;
    result = n1.last.compare(n2.last);
    return result;
}

ostream& operator << (ostream& os, Name& n)
{
    os << n.first << endl;
    os << n.last;

    return os;
}

istream& operator >> (istream& is, Name& n)
{
    getline(is, n.first);
    getline(is, n.last);

    return is;
}
