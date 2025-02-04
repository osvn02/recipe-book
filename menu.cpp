#include "menu.h"
using namespace std;

Menu::Menu(){}

void Menu::start()
{
    char pick;
    cout << "Bienvenido al programa!" << endl << endl;
    do{
        cout << "\nSeleccione una opcion:\n";
        cout << "[a] Mostrar lista." << endl;
        cout << "[b] Insertar receta." << endl;
        cout << "[c] Mostrar receta." << endl;
        cout << "[d] Borrar una receta." << endl;
        cout << "[e] Ordenar lista." << endl;
        cout << "[f] Modificar ingredientes de una receta." << endl;
        cout << "[g] Modificar procedimiento de una receta." << endl;
        cout << "[h] Borrar recetario." << endl;
        cout << "[i] Leer recetario del disco." << endl;
        cout << "[j] Escribir recetario al disco." << endl;
        cout << "[s] Salir\n-> ";
        cin >> pick;

        cin.ignore();

        switch(pick){
            case 'a': displayList(); break;
            case 'b': addRecipe(); break;
            case 'c': displayRecipe(); break;
            case 'd': removeRecipe(); break;
            case 'e': sortList(); break;
            case 'f': modifyIngredients(); break;
            case 'g': modifyProcedure(); break;
            case 'h': recipeList.nullify(); cout << "\nLista borrada" << endl; break;
            case 'i': recipeList.readFromDisk("listado.txt"); cout << "\nRecetario leido" << endl; break;
            case 'j': recipeList.writeToDisk("listado.txt"); cout << "\nRecetario escrito" << endl; break;
            case 's': cout << "\nHasta pronto!"; getchar(); break;
        }

    } while(pick != 's');
}

void Menu::displayList()
{
    char pick;
    Recipe myRecipe;
    if(recipeList.isEmpty()){
        cout << "La lista se encuentra vacia" << endl << endl;
        return;
    }
    cout << "\nDesplegar:\n[a]Toda la lista\n[b]Desayunos\n[c]Comidas\n[d]Cenas\n[e]Navidenos\n->";
    cin >> pick;
    cin.ignore();
    cout << "Lista actual:" << endl;
    switch(pick){
    case 'a':
        cout << recipeList.toString() << endl << endl;
        break;
    case 'b':
        myRecipe.setCategory("Desayuno");
        cout << recipeList.categoricToString(myRecipe, Recipe::compareByCategory) << endl << endl;
        break;
    case 'c':
        myRecipe.setCategory("Comida");
        cout << recipeList.categoricToString(myRecipe, Recipe::compareByCategory) << endl << endl;
        break;
    case 'd':
        myRecipe.setCategory("Cena");
        cout << recipeList.categoricToString(myRecipe, Recipe::compareByCategory) << endl << endl;
        break;
    case 'e':
        myRecipe.setCategory("Navideno");
        cout << recipeList.categoricToString(myRecipe, Recipe::compareByCategory) << endl << endl;
        break;
    }

}

void Menu::addRecipe()
{
    Recipe myRecipe;
    Name myName;
    string myStr;
    char pick;
    DLList<Recipe>::Position pos = recipeList.getLastPos();

    cout << "Nombre del platillo: ";
    getline(cin, myStr);
    myRecipe.setName(myStr);

    cout << "\nCategoria:\n[a]Desayuno\n[b]Comida\n[c]Cena\n[d]Navideno\n-> ";
    cin >> pick;
    cin.ignore();
    switch(pick){
        case 'a': myStr = "Desayuno"; break;
        case 'b': myStr = "Comida"; break;
        case 'c': myStr = "Cena"; break;
        case 'd': myStr = "Navideno"; break;
        default: myStr = "s/c"; break;
    }
    myRecipe.setCategory(myStr);

    cout << "Tiempo de preparacion (en minutos): ";
    getline(cin, myStr);
    myRecipe.setPrepTime(stoi(myStr));

    cout << "Nombre del autor: ";
    getline(cin, myStr);
    myName.setFirst(myStr);
    cout << "Apellido del autor: ";
    getline(cin, myStr);
    myName.setLast(myStr);
    myRecipe.setAuthor(myName);

    myRecipe.setIngredients(addIngredients());

    cout << "Procedimiento: ";
    getline(cin, myStr);
    myRecipe.setProcedure(myStr);

    try{
        recipeList.insertData(pos, myRecipe);
    }catch(typename DLList<Recipe>::Exception ex){
        cout << "Error al ingresar receta: " << ex.what() << endl;
    }
}

void Menu::displayRecipe()
{
    Recipe myRecipe;
    string myStr;
    DLList<Recipe>::Position pos;
    char pick;
    cout << "\nSeleccione el criterio de busqueda:\n[a]Nombre de la receta\n[b]Categoria de la receta\n-> ";
    cin >> pick;
    cin.ignore();
    switch(pick){
        case 'a':
            cout << "Nombre de la receta: ";
            getline(cin, myStr);
            myRecipe.setName(myStr);
            pos = recipeList.findData(myRecipe, Recipe::compareByName);
            break;
        case 'b':
            cout << "\nCategoria:\n[a]Desayuno\n[b]Comida\n[c]Cena\n[d]Navideno\n-> ";
            cin >> pick;
            cin.ignore();
            switch(pick){
                case 'a': myStr = "Desayuno"; break;
                case 'b': myStr = "Comida"; break;
                case 'c': myStr = "Cena"; break;
                case 'd': myStr = "Navideno"; break;
                default: myStr = "s/c"; break;
            }
            myRecipe.setCategory(myStr);
            pos = recipeList.findData(myRecipe, Recipe::compareByCategory);
            break;
    }
    cout << "\nLa busqueda de " << myStr << " ";
    if(pos == nullptr){
        cout << "no fue encontrada en la lista";
    }
    else{
        cout << "\nSe muestra a continuacion: \n" << recipeList.getElement(pos)->displayRecipe() << endl << endl;
    }
}

void Menu::removeRecipe()
{
    Recipe myRecipe;
    string myStr;
    DLList<Recipe>::Position pos;
    cout << "Nombre de la receta: ";
    getline(cin, myStr);
    myRecipe.setName(myStr);
    pos = recipeList.findData(myRecipe, Recipe::compareByName);
    try{
        recipeList.deleteData(pos);
    }catch(typename DLList<Recipe>::Exception ex){
        cout << "Error al borrar receta: " << ex.what() << endl;
    }

}

void Menu::deleteList()
{
    recipeList.nullify();
    cout << "Lista anulada" << endl;
}

void Menu::sortList()
{
    char pick;
    cout << "Seleccione el criterio de ordenamiento:\n[a]Nombre\n[b]Tiempo de preparacion\n->";
    cin >> pick;
    cin.ignore();
    if(pick == 'b'){
        recipeList.sortList(&Recipe::compareByPrepTime);
    }else{
        recipeList.sortList(&Recipe::compareByName);
    }
}

void Menu::modifyIngredients()
{
    Recipe myRecipe;
    Ingredient myIngredient;
    string myStr;
    DLList<Recipe>::Position pos;
    SLList<Ingredient>::Position internalPos;
    char pick;

    cout << "\nIngrese el nombre de la receta cuyos ingredientes desea modificar: ";
    getline(cin, myStr);
    myRecipe.setName(myStr);
    pos = recipeList.findData(myRecipe, Recipe::compareByName);
    if(pos == nullptr){
        cout << "No se encontro la receta buscada" << endl;
        return;
    }
    myRecipe = *(recipeList.getElement(pos));
    SLList<Ingredient> myIngredients = myRecipe.getIngredients();

    cout << myRecipe.displayRecipe() << endl;
    cout << "\nSeleccione una opcion:\n[a]Agregar un ingrediente\n[b]Eliminar un ingrediente\n[c]Modificar la cantidad de un ingrediente\n[d]Borrar todos los ingredientes\n->";
    cin >> pick;
    cin.ignore();
    switch(pick){
    case 'a':
        myIngredients = addIngredients(myRecipe.getIngredients());
        break;
    case 'b':
        cout << "\nIngrese el nombre del ingrediente que desea borrar: ";
        getline(cin, myStr);
        myIngredient.setName(myStr);
        internalPos = myIngredients.findData(myIngredient, Ingredient::compareByName);
        try{
            myIngredients.deleteData(internalPos);
        }catch(typename SLList<Recipe>::Exception ex){
            cout << "Error al borrar receta: " << ex.what() << endl;
        }
        break;
    case 'c':
        cout << "\nIngrese el nombre del ingrediente que desea modificar: ";
        getline(cin, myStr);
        myIngredient.setName(myStr);
        cout << "Nuevo nombre de la unidad: ";
        getline(cin, myStr);
        myIngredient.setUnit(myStr);
        cout << "Nueva cantidad: ";
        getline(cin, myStr);
        myIngredient.setQuantity(stoi(myStr));
        internalPos = myIngredients.findData(myIngredient, Ingredient::compareByName);
        myIngredients.insertData(internalPos, myIngredient);
        myIngredients.deleteData(internalPos);
        break;
    case 'd':
        myIngredients.nullify();
        break;
    default:
        return;
    }
    myRecipe.setIngredients(myIngredients);
    *(recipeList.getElement(pos)) = myRecipe;
}

void Menu::modifyProcedure()
{
    Recipe myRecipe;
    string myStr;
    DLList<Recipe>::Position pos;

    cout << "\nIngrese el nombre de la receta cuyo procedimiento desea modificar: ";
    getline(cin, myStr);
    myRecipe.setName(myStr);
    pos = recipeList.findData(myRecipe, Recipe::compareByName);
    if(pos == nullptr){
        cout << "No se encontro la receta buscada" << endl;
        return;
    }
    myRecipe = *(recipeList.getElement(pos));

    cout << "Nuevo procedimiento: ";
    getline(cin, myStr);
    myRecipe.setProcedure(myStr);
    *(recipeList.getElement(pos)) = myRecipe;
}

SLList<Ingredient> Menu::addIngredients() const
{
    SLList<Ingredient> result;
    string myStr;
    char pick;
    bool flag;
    SLList<Ingredient>::Position pos;
    int comparison;

    cout << "A continuacion ingrese los ingredientes" << endl;
    do{
        Ingredient myIngredient;

        cout << "Nombre del ingrediente: ";
        getline(cin, myStr);
        myIngredient.setName(myStr);

        cout << "Nombre de la unidad: ";
        getline(cin, myStr);
        myIngredient.setUnit(myStr);

        cout << "Cantidad: ";
        getline(cin, myStr);
        myIngredient.setQuantity(stoi(myStr));

        pos = result.getFirstPos();

        if(pos != nullptr){
            while(pos != nullptr){
                comparison = Ingredient::compareByName(myIngredient, result.getElement(pos));
                if(comparison < 0){
                    try{
                        result.insertData(result.getPrevPos(pos), myIngredient);
                    }catch(typename SLList<Ingredient>::Exception ex){
                        cout << "Error al ingresar ingrediente: " << ex.what() << endl;
                    }
                    break;
                }

                if(result.getNextPos(pos) == nullptr){
                    try{
                        result.insertData(pos, myIngredient);
                    }catch(typename SLList<Ingredient>::Exception ex){
                        cout << "Error al ingresar ingrediente: " << ex.what() << endl;
                    }
                    break;
                }
                pos = result.getNextPos(pos);
            }
        }
        else{
            try{
                result.insertData(pos, myIngredient);
            }catch(typename SLList<Ingredient>::Exception ex){
                cout << "Error al ingresar ingrediente: " << ex.what() << endl;
            }
        }


        cout << "Ingresar otro ingrediente?(s/n): ";
        cin >> pick;
        cin.ignore();
        switch(pick){
            case 's': flag = true; break;
            case 'n': flag = false; break;
        }
    }while(flag);
    return result;
}

SLList<Ingredient> Menu::addIngredients(const SLList<Ingredient>& current) const
{
    SLList<Ingredient> result = current;
    string myStr;
    char pick;
    bool flag;
    SLList<Ingredient>::Position pos;
    int comparison;

    cout << "A continuacion ingrese los ingredientes" << endl;
    do{
        Ingredient myIngredient;

        cout << "Nombre del ingrediente: ";
        getline(cin, myStr);
        myIngredient.setName(myStr);

        cout << "Nombre de la unidad: ";
        getline(cin, myStr);
        myIngredient.setUnit(myStr);

        cout << "Cantidad: ";
        getline(cin, myStr);
        myIngredient.setQuantity(stoi(myStr));

        pos = result.getFirstPos();

        if(pos != nullptr){
            while(pos != nullptr){
                comparison = Ingredient::compareByName(myIngredient, result.getElement(pos));
                if(comparison < 0){
                    try{
                        result.insertData(result.getPrevPos(pos), myIngredient);
                    }catch(typename SLList<Ingredient>::Exception ex){
                        cout << "Error al ingresar ingrediente: " << ex.what() << endl;
                    }
                    break;
                }

                if(result.getNextPos(pos) == nullptr){
                    try{
                        result.insertData(pos, myIngredient);
                    }catch(typename SLList<Ingredient>::Exception ex){
                        cout << "Error al ingresar ingrediente: " << ex.what() << endl;
                    }
                    break;
                }
                pos = result.getNextPos(pos);
            }
        }
        else{
            try{
                result.insertData(pos, myIngredient);
            }catch(typename SLList<Ingredient>::Exception ex){
                cout << "Error al ingresar ingrediente: " << ex.what() << endl;
            }
        }

        cout << "Ingresar otro ingrediente?(s/n): ";
        cin >> pick;
        cin.ignore();
        switch(pick){
            case 's': flag = true; break;
            case 'n': flag = false; break;
        }
    }while(flag);
    return result;
}
