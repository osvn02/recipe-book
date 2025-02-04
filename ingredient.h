#ifndef INGREDIENT_H_INCLUDED
#define INGREDIENT_H_INCLUDED
#include <string>
#include <iostream>

class Ingredient{
private:
    std::string name;
    int quantity;
    std::string unit;

public:
    Ingredient();
    Ingredient(const Ingredient&);

    void setName(const std::string&);
    void setQuantity(const int&);
    void setUnit(const std::string&);

    std::string getName() const;
    int getQuantity() const;
    std::string getUnit() const;

    std::string txtString() const;
    std::string toString() const;

    Ingredient& operator = (const Ingredient&);
    bool operator == (const Ingredient&) const;
    bool operator != (const Ingredient&) const;
    bool operator < (const Ingredient&) const;
    bool operator > (const Ingredient&) const;
    bool operator <= (const Ingredient&) const;
    bool operator >= (const Ingredient&) const;

    static int compareByName(const Ingredient&, const Ingredient&);
    static int compareByQuantity(const Ingredient&, const Ingredient&);
    static int compareByUnit(const Ingredient&, const Ingredient&);

    friend std::ostream& operator << (std::ostream&, Ingredient&);
    friend std::istream& operator >> (std::istream&, Ingredient&);
};

#endif // INGREDIENT_H_INCLUDED
