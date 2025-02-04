#include "recipe.h"
using namespace std;

Recipe::Recipe(){}

Recipe::Recipe(const Recipe& r) : name(r.name), ingredients(r.ingredients), prepTime(r.prepTime), procedure(r.procedure), author(r.author), category(r.category){}

void Recipe::setName(const std::string& s)
{
    name = s;
}

void Recipe::setIngredients(const SLList<Ingredient>& i)
{
    ingredients = i;
}

void Recipe::setPrepTime(const int& t)
{
    prepTime = t;
}

void Recipe::setProcedure(const std::string& s)
{
    procedure = s;
}

void Recipe::setAuthor(const Name& n)
{
    author = n;
}

void Recipe::setCategory(const std::string& s)
{
    category = s;
}

string Recipe::getName() const
{
    return name;
}

SLList<Ingredient> Recipe::getIngredients() const
{
    return ingredients;
}

int Recipe::getprepTime() const
{
    return prepTime;
}

string Recipe::getProcedure() const
{
    return procedure;
}

Name Recipe::getAuthor() const
{
    return author;
}

string Recipe::getCategory() const
{
    return category;
}

string Recipe::toString() const
{
    string result;
    result += "Nombre: ";
    result += name;
    result += " | ";
    result += "Categoria: ";
    result += category;
    result += " | ";
    result += "Autor: ";
    result += author.toString();
    result += " | ";
    result += "Tiempo de preparacion: ";
    result += to_string(prepTime);
    result += " minutos";
    return result;
}

string Recipe::displayRecipe() const
{
    string result;
    result += toString();
    result += "\nIngredientes:\n";
    result += ingredients.toString();
    result += "\nProcedimiento:\n";
    result += procedure;
    return result;
}

Recipe& Recipe::operator=(const Recipe& r)
{
    name = r.name;
    ingredients = r.ingredients;
    prepTime = r.prepTime;
    procedure = r.procedure;
    author = r.author;
    category = r.category;
    return *this;
}

bool Recipe::operator==(const Recipe& r) const
{
    return *this == r;
}

bool Recipe::operator!=(const Recipe& r) const
{
    return *this != r;
}

bool Recipe::operator<(const Recipe& r) const
{
    return *this < r;
}

bool Recipe::operator>(const Recipe& r) const
{
    return *this > r;
}

bool Recipe::operator<=(const Recipe& r) const
{
    return (*this < r) or (*this == r);
}

bool Recipe::operator>=(const Recipe& r) const
{
    return (*this > r) or (*this == r);
}

int Recipe::compareByName(const Recipe& r1, const Recipe& r2)
{
    int result;
    result = r1.name.compare(r2.name);
    return result;
}

int Recipe::compareByPrepTime(const Recipe& r1, const Recipe& r2)
{
    return r1.prepTime - r2.prepTime;
}

int Recipe::compareByCategory(const Recipe& r1, const Recipe& r2)
{
    int result;
    result = r1.category.compare(r2.category);
    return result;
}

ostream& operator << (ostream& os, Recipe& r)
{
    os << r.name << endl;
    os << r.category << endl;
    os << r.author << endl;
    os << r.prepTime << endl;
    os << r.ingredients.txtString();
    os << r.procedure;
    return os;
}

istream& operator >> (istream& is, Recipe& r)
{
    string auxNameIngredient, myStr;
    Ingredient auxIngredient;
    int entero;
    char last;
    r.ingredients.nullify();

    getline(is, r.name);
    if(r.name.empty()){
        return is;
    }
    getline(is, r.category);
    is >> r.author;

    getline(is, myStr);
    entero = stoi(myStr);
    r.setPrepTime(entero);

    do{
        is >> auxIngredient;
        r.ingredients.insertData(r.ingredients.getLastPos(), auxIngredient);
        myStr = auxIngredient.getName();
        last = myStr[myStr.length()-1];
    }while(last != ' ');



    getline(is, r.procedure);
    return is;
}
