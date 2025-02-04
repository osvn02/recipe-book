#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

template <class T>
class SLList{
private:
    class Node{
    private:
        T data;
        Node* next;

    public:
        Node();
        Node(const T&);

        T getData() const;
        Node* getNext() const;

        void setData(const T&);
        void setNext(Node*);
    };

    Node* anchor;
    void copyAll(const SLList<T>&);
    bool isValidPos(Node*) const;

public:
    typedef Node* Position;

    class Exception : public std::exception{
    private:
        std::string msg;
    public:
        explicit Exception(const char* message) : msg(message){}
        explicit Exception(const std::string& message) : msg(message){}
        virtual ~Exception() throw(){}
        virtual const char* what() const throw(){
            return msg.c_str();
        }
    };

    SLList();
    SLList(const SLList<T>&);
    ~SLList();

    bool isEmpty() const;
    void insertData(Node*, const T&);

    void deleteData(Node*);

    Node* getFirstPos() const;
    Node* getLastPos() const;
    Node* getPrevPos(Node*) const;
    Node* getNextPos(Node*) const;

    Node* findData(const T&, int cmp(const T&, const T&)) const;

    T getElement(Node*) const;

    std::string txtString() const;
    std::string toString() const;
    std::string categoricToString(const T&, int cmp(const T&, const T&)) const;

    void nullify();
    SLList<T>& operator = (const SLList<T>&);
};

//Nodo
template <class T>
SLList<T>::Node::Node() : next(nullptr){}

template <class T>
SLList<T>::Node::Node(const T& e) : data(e), next(nullptr){}

template <class T>
T SLList<T>::Node::getData() const
{
    return data;
}

template <class T>
typename SLList<T>::Node* SLList<T>::Node::getNext() const
{
    return next;
}

template <class T>
void SLList<T>::Node::setData(const T& e)
{
    data = e;
}

template <class T>
void SLList<T>::Node::setNext(Node* p)
{
    next = p;
}

//Lista
template <class T>
void SLList<T>::copyAll(const SLList<T>& l)
{
    Node* aux(l.anchor);
    Node* last(nullptr);
    Node* newNode;

    while(aux != nullptr){
        newNode = new Node(aux->getData());
        if(newNode == nullptr){
            throw Exception("Memoria no disponible, no se pudo insertar el dato");
        }

        if(last == nullptr){
            anchor = newNode;
        }
        else{
            last->setNext(newNode);
        }

        last = newNode;

        aux = aux->getNext();
    }
}

template <class T>
bool SLList<T>::isValidPos(Node* p) const
{
    Node* aux(anchor);

    while(aux != nullptr){
        if(aux==p){
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template <class T>
SLList<T>::SLList() : anchor(nullptr){}

template <class T>
SLList<T>::SLList(const SLList<T>& l) : anchor(nullptr)
{
    copyAll(l);
}

template <class T>
SLList<T>::~SLList()
{
    nullify();
}

template <class T>
bool SLList<T>::isEmpty() const
{
    return anchor == nullptr;
}

template <class T>
void SLList<T>::insertData(Node* p, const T& e)
{
    if(p != nullptr and !isValidPos(p)){
        throw Exception("Posicion Invalida, no se pudo insertar el dato");
    }

    Node* aux(new Node(e));

    if(aux == nullptr){
        throw Exception("Memoria no disponible, no se pudo insertar el dato");
    }

    if(p == nullptr){
        aux->setNext(anchor);
        anchor = aux;
    }
    else{
        aux->setNext(p->getNext());
        p->setNext(aux);
    }
}

template <class T>
void SLList<T>::deleteData(Node* p)
{
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, no se pudo eliminar el dato");
    }

    if(p == anchor){
        anchor = anchor->getNext();
    }
    else{
        getPrevPos(p)->setNext(p->getNext());
    }
    delete p;
}

template <class T>
typename SLList<T>::Node* SLList<T>::getFirstPos() const
{
    return anchor;
}

template <class T>
typename SLList<T>::Node* SLList<T>::getLastPos() const
{
    if(isEmpty()){
        return nullptr;
    }
    Node* aux(anchor);
    while(aux->getNext() != nullptr){
        aux = aux->getNext();
    }
    return aux;
}

template <class T>
typename SLList<T>::Node* SLList<T>::getPrevPos(Node* p) const
{
    if(p == anchor){
        return nullptr;
    }
    Node* aux(anchor);

    while(aux != nullptr and aux->getNext() != p){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename SLList<T>::Node* SLList<T>::getNextPos(Node* p) const
{
    if(!isValidPos(p)){
        return nullptr;
    }

    return p->getNext();
}

template <class T>
typename SLList<T>::Node* SLList<T>::findData(const T& e, int cmp(const T&, const T&)) const
{
    Node* aux(anchor);

    while(aux != nullptr and cmp(aux->getData(), e) != 0){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
T SLList<T>::getElement(Node* p) const
{
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, no se pudo obtener el elemento");
    }

    return p->getData();
}

template <class T>
std::string SLList<T>::txtString() const
{
    std::string result;
    Node* aux(anchor);

    while(aux != nullptr){
        result += aux->getData().txtString();
        if(aux->getNext() == nullptr){
            result += " \n";
        }
        else{
            result += "\n";
        }
        aux = aux->getNext();
    }
    return result;
}

template <class T>
std::string SLList<T>::toString() const
{
    std::string result;
    Node* aux(anchor);

    while(aux != nullptr){
        result += aux->getData().toString() + "\n";
        aux = aux->getNext();
    }
    return result;
}

template <class T>
std::string SLList<T>::categoricToString(const T& e, int cmp(const T&, const T&)) const
{
    std::string result;
    Node* pos = anchor;
    Node* last = getLastPos();
    do{
        if(cmp(e, pos->getData()) == 0){
            result += pos->getData().toString() + "\n";
        }
        pos = pos->getNext();
    }while(pos != last);
    return result;
}

template <class T>
void SLList<T>::nullify()
{
    Node* aux;

    while(anchor != nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
}

template <class T>
SLList<T>& SLList<T>::operator=(const SLList<T>& l)
{
    nullify();
    copyAll(l);
    return *this;
}
#endif // SLIST_H_INCLUDED
