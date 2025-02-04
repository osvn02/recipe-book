#include "ingredient.h"
using namespace std;

Ingredient::Ingredient(){}

Ingredient::Ingredient(const Ingredient& i) : name(i.name), quantity(i.quantity), unit(i.unit){}

void Ingredient::setName(const std::string& s)
{
    name = s;
}

void Ingredient::setQuantity(const int& i)
{
    quantity = i;
}

void Ingredient::setUnit(const std::string& s)
{
    unit = s;
}

string Ingredient::getName() const
{
    return name;
}

int Ingredient::getQuantity() const
{
    return quantity;
}

string Ingredient::getUnit() const
{
    return unit;
}

string Ingredient::txtString() const
{
    string result;
    result += to_string(quantity);
    result += "\n";
    result += unit;
    result += "\n";
    result += name;
    return result;
}

string Ingredient::toString() const
{
    string result;
    result += to_string(quantity);
    result += " ";
    result += unit;
    result += " de ";
    result += name;
    return result;
}

Ingredient& Ingredient::operator=(const Ingredient& i)
{
    name = i.name;
    quantity = i.quantity;
    unit = i.unit;
    return *this;
}

bool Ingredient::operator==(const Ingredient& i) const
{
    return *this == i;
}

bool Ingredient::operator!=(const Ingredient& i) const
{
    return *this != i;
}

bool Ingredient::operator<(const Ingredient& i) const
{
    return *this < i;
}

bool Ingredient::operator>(const Ingredient& i) const
{
    return *this > i;
}

bool Ingredient::operator<=(const Ingredient& i) const
{
    return (*this < i) or (*this == i);
}

bool Ingredient::operator>=(const Ingredient& i) const
{
    return (*this > i) or (*this == i);
}

int Ingredient::compareByName(const Ingredient& i1, const Ingredient& i2)
{
    int result;
    result = i1.name.compare(i2.name);
    return result;
}

int Ingredient::compareByQuantity(const Ingredient& i1, const Ingredient& i2)
{
    return i1.quantity - i2.quantity;
}

int Ingredient::compareByUnit(const Ingredient& i1, const Ingredient& i2)
{
    int result;
    result = i1.unit.compare(i2.unit);
    return result;
}

ostream& operator << (ostream& os, Ingredient& i)
{
    os << i.name << endl;
    os << i.quantity << endl;
    os << i.unit;
    return os;
}

istream& operator >> (istream& is, Ingredient& i)
{
    string myStr;
    getline(is, myStr);
    i.quantity = stoi(myStr);
    getline(is, i.unit);
    getline(is, i.name);
    return is;
}
