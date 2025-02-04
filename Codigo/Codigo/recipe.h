#ifndef RECIPE_H_INCLUDED
#define RECIPE_H_INCLUDED
#include <string>
#include <iostream>
#include "slist.h"
#include "ingredient.h"
#include "name.h"

class Recipe{
private:
    std::string name;
    SLList<Ingredient> ingredients;
    int prepTime;
    std::string procedure;
    Name author;
    std::string category;

public:
    Recipe();
    Recipe(const Recipe&);

    void setName(const std::string&);
    void setIngredients(const SLList<Ingredient>&);
    void setPrepTime(const int&);
    void setProcedure(const std::string&);
    void setAuthor(const Name&);
    void setCategory(const std::string&);

    std::string getName() const;
    SLList<Ingredient> getIngredients() const;
    int getprepTime() const;
    std::string getProcedure() const;
    Name getAuthor() const;
    std::string getCategory() const;

    std::string toString() const;
    std::string displayRecipe() const;

    Recipe& operator = (const Recipe&);
    bool operator == (const Recipe&) const;
    bool operator != (const Recipe&) const;
    bool operator < (const Recipe&) const;
    bool operator >(const Recipe&) const;
    bool operator <= (const Recipe&) const;
    bool operator >= (const Recipe&) const;

    static int compareByName(const Recipe&, const Recipe&);
    static int compareByPrepTime(const Recipe&, const Recipe&);
    static int compareByCategory(const Recipe&, const Recipe&);

    friend std::ostream& operator << (std::ostream&, Recipe&);
    friend std::istream& operator >> (std::istream&, Recipe&);
};


#endif // RECIPE_H_INCLUDED
