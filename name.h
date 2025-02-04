#ifndef NAME_H_INCLUDED
#define NAME_H_INCLUDED
#include <string>
#include <iostream>

class Name{
private:
    std::string first;
    std::string last;

public:
    Name();
    Name(const Name&);

    std::string getFirst() const;
    std::string getLast() const;

    void setFirst(const std::string&);
    void setLast(const std::string&);

    std::string toString() const;

    Name& operator = (const Name&);
    bool operator ==(const Name&) const;
    bool operator !=(const Name&) const;
    bool operator <(const Name&) const;
    bool operator >(const Name&) const;
    bool operator <=(const Name&) const;
    bool operator >=(const Name&) const;

    static int compareByFirst(const Name&, const Name&);
    static int compareByLast(const Name&, const Name&);

    friend std::ostream& operator << (std::ostream&, Name&);
    friend std::istream& operator >> (std::istream&, Name&);
};


#endif // NAME_H_INCLUDED
