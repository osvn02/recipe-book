#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

template <class T>
class DLList{
private:
    class Node{
    private:
        T* dataPtr;
        Node* prev;
        Node* next;

    public:
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

        Node();
        Node(const T&);
        ~Node();

        T* getDataPtr() const;
        T getData() const;
        Node* getPrev() const;
        Node* getNext() const;

        void setDataPtr(T*);
        void setData(const T&);
        void setPrev(Node*);
        void setNext(Node*);
    };
    Node* header;
    void copyAll(const DLList<T>&);
    bool isValidPos(Node*) const;
    void swapData(T*, T*);
    Node* sortingPartition(Node* l, Node* h, int cmp(const T&, const T&));
    void sortList(Node*, Node*, int cmp(const T&, const T&));
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

    DLList();
    DLList(const DLList<T>&);
    ~DLList();

    void sortList(int (*cmp)(const T&, const T&));

    bool isEmpty() const;

    void insertData(Node*, const T&);
    void deleteData(Node*);

    Node* getFirstPos() const;
    Node* getLastPos() const;
    Node* getPrevPos(Node*) const;
    Node* getNextPos(Node*) const;

    Node* findData(const T&, int cmp(const T&, const T&)) const;
    T* getElement(Node*) const;

    std::string toString() const;
    std::string categoricToString(const T&, int cmp(const T&, const T&)) const;

    void nullify();

    DLList<T>& operator = (const DLList<T>&);

    void readFromDisk(const std::string&);
    void writeToDisk(const std::string&);
};

//Nodo
template <class T>
DLList<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr){}

template <class T>
DLList<T>::Node::Node(const T& e) : dataPtr(new T(e)), prev(nullptr), next(nullptr)
{
    if (dataPtr == nullptr){
        throw Exception("Memoria insuficiente, no se pudo crear nuevo nodo");
    }
}

template <class T>
DLList<T>::Node::~Node()
{
    delete dataPtr;
}

template <class T>
T* DLList<T>::Node::getDataPtr() const
{
   return dataPtr;
}

template <class T>
T DLList<T>::Node::getData() const
{
   if (dataPtr == nullptr){
    throw Exception("Dato inexistente, getData");
   }
   return *dataPtr;
}

template <class T>
typename DLList<T>::Node* DLList<T>::Node::getPrev() const
{
    return prev;
}

template <class T>
typename DLList<T>::Node* DLList<T>::Node::getNext() const
{
    return next;
}

template <class T>
void DLList<T>::Node::setDataPtr(T* p)
{
    dataPtr = p;
}

template <class T>
void DLList<T>::Node::setData(const T& e)
{
    if(dataPtr == nullptr){
        if((dataPtr = new T(e)) == nullptr){
            throw Exception("Memoria no disponible, setData");
        }
    }
    else{
        *dataPtr = e;
    }
}

template <class T>
void DLList<T>::Node::setPrev(Node* p)
{
    prev = p;
}

template <class T>
void DLList<T>::Node::setNext(Node* p)
{
    next = p;
}

//Lista
template <class T>
void DLList<T>::copyAll(const DLList<T>& l)
{
    Node* aux(l.header->getNext());
    Node* newNode;

    while(aux != l.header){
        try{
            if((newNode = new Node(aux->getData())) == nullptr){
                throw Exception("Memoria no disponible, no se pudo copiar la lista");
            }
        } catch (typename Node::Exception ex){
            throw Exception(ex.what());
            }
        newNode->setPrev(header->getPrev());
        newNode->setNext(header);

        header->getPrev()->setNext(newNode);
        header->setPrev(newNode);

        aux = aux->getNext();
    }
}

template <class T>
bool DLList<T>::isValidPos(Node* p) const
{
    Node* aux(header->getNext());
    while (aux != header){
        if(aux == p){
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template <class T>
DLList<T>::DLList() : header(new Node)
{
    if(header == nullptr){
        throw Exception("Memoria no disponible, no se pudo inicializar la lista");
    }
    header->setPrev(header);
    header->setNext(header);
}

template <class T>
DLList<T>::DLList(const DLList<T>& l) : DLList()
{
    copyAll(l);
}

template <class T>
DLList<T>::~DLList()
{
    nullify();
    delete header;
}

template <class T>
bool DLList<T>::isEmpty() const
{
    return header->getNext() == header;
}

template <class T>
void DLList<T>::insertData(Node* p, const T& e)
{
    if (p != nullptr and !isValidPos(p)){
        throw Exception("Posicion invalida, no se pudo insertar el dato");
    }

    Node* aux;
    try{
        aux = new Node(e);
        }
        catch (typename Node::Exception ex){
            throw Exception(ex.what());
        }

    if (aux == nullptr){
        throw Exception("Memoria no disponible, no se pudo insertar el dato");
    }

    if(p == nullptr){
        p = header;
    }

    aux->setPrev(p);
    aux->setNext(p->getNext());
    p->getNext()->setPrev(aux);
    p->setNext(aux);
}

template <class T>
void DLList<T>::deleteData(Node* p)
{
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, no se pudo borrar el dato");
    }

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());
    delete p;
}

template <class T>
typename DLList<T>::Node* DLList<T>::getFirstPos() const
{
    if(isEmpty()){
        return nullptr;
    }

    return header->getNext();
}

template <class T>
typename DLList<T>::Node* DLList<T>::getLastPos() const
{
    if(isEmpty()){
        return nullptr;
    }

    return header->getPrev();
}

template <class T>
typename DLList<T>::Node* DLList<T>::getPrevPos(Node* p) const
{
    if(!isValidPos(p) or p==header->getNext()){
        return nullptr;
    }
    return p->getPrev();
}

template <class T>
typename DLList<T>::Node* DLList<T>::getNextPos(Node* p) const
{
    if(!isValidPos(p) or p==header->getPrev()){
        return nullptr;
    }
    return p->getNext();
}

template <class T>
typename DLList<T>::Node* DLList<T>::findData(const T& e, int cmp(const T&, const T&)) const
{
    Node* aux(header->getNext());
    while(aux != header){
        if(cmp(aux->getData(), e) == 0){
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

template <class T>
T* DLList<T>::getElement(Node* p) const
{
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, no se pudo recuperar el elemento");
    }

    return p->getDataPtr();
}

template <class T>
std::string DLList<T>::toString() const
{
    Node* aux(header->getNext());
    std::string result;

    while(aux != header){
        result += aux->getData().toString() + "\n";
        aux = aux->getNext();
    }
    return result;
}

template <class T>
std::string DLList<T>::categoricToString(const T& e, int cmp(const T&, const T&)) const
{
    std::string result;
    Node* aux(header->getNext());
    while(aux != header){
        if(cmp(e, aux->getData()) == 0){
            result += aux->getData().toString() + "\n";
        }
        aux = aux->getNext();
    }
    return result;
}

template <class T>
void DLList<T>::nullify()
{
    Node* aux;

    while(header->getNext() != header){
        aux = header->getNext();

        header->setNext(aux->getNext());

        delete aux;
    }
    header->setPrev(header);
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& l)
{
    nullify();
    copyAll(l);
    return *this;
}

template <class T>
void DLList<T>::swapData(T* a, T* b)
{
    T aux = *a;
    *a = *b;
    *b = aux;
}

template <class T>
typename DLList<T>::Node* DLList<T>::sortingPartition(Node* l, Node* h, int cmp(const T&, const T&))
{
    T x = h->getData();
    Node* i = l->getPrev();

    for(Node* j=l; j!=h; j=j->getNext()){
        if(cmp(j->getData(), x) <= 0){
            i = (i == header)? l : i->getNext();
            swapData(i->getDataPtr(), j->getDataPtr());
        }
    }

    i = (i==header)? l : i->getNext();
    swapData(i->getDataPtr(), h->getDataPtr());
    return i;
}

template <class T>
void DLList<T>::sortList(int (*cmp)(const T&, const T&))
{
     Node* h = getLastPos();
     Node* first = getFirstPos();
     sortList(first, h, cmp);
}

template <class T>
void DLList<T>::sortList(Node* l, Node* h, int cmp(const T&, const T&))
{
    if(h!=header and l!=h and l!=h->getNext()){
        Node* p = sortingPartition(l, h, cmp);
        sortList(l, p->getPrev(), cmp);
        sortList(p->getNext(), h, cmp);
    }
}

template <class T>
void DLList<T>::readFromDisk(const std::string& fileName)
{
    std::ifstream myFile;

    myFile.open(fileName);

    if(!myFile.is_open()){
        throw Exception("No se pudo abrir el archivo para lectura");
    }

    nullify();

    T myData;

    try{
        while(myFile >> myData){
            insertData(getLastPos(), myData);
        }
    }
    catch(Exception ex){
        myFile.close();
        throw Exception(ex.what());
    }
    myFile.close();
}

template <class T>
void DLList<T>::writeToDisk(const std::string& fileName)
{
    std::ofstream myFile;

    myFile.open(fileName, std::ios_base::trunc);

    if(!myFile.is_open()){
        throw Exception("No se pudo abrir el archivo para escritura");
    }

    Node* aux = header->getNext();
    T data;
    while(aux != header){
        data = aux->getData();
        myFile << data << std::endl;
        aux = aux->getNext();
    }

    myFile.close();
}

#endif // DLIST_H_INCLUDED
