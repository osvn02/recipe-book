#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include "recipe.h"
#include "dlist.h"

class Menu{
private:
    DLList<Recipe> recipeList;

public:
    Menu();
    void start();
    void displayList();
    void addRecipe();
    void displayRecipe();
    void removeRecipe();
    void deleteList();
    void sortList();
    void modifyIngredients();
    void modifyProcedure();
    SLList<Ingredient> addIngredients() const;
    SLList<Ingredient> addIngredients(const SLList<Ingredient>&) const;
};


#endif // MENU_H_INCLUDED
