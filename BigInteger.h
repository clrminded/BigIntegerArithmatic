/**
 * @file BigInteger.h
 * @author Christopher Liudahl-Rackley and Mohamed Elfergani
 * @brief BigInteger is a customer data type that has the ability to handle the addition and subtraction of numbers that are larger than any data type. It can read in data from external files and assign them to variables used in the program. The addition works, and we were only able to 
 * @version 4.0
 * @date 2021-11-07 
 */

#ifndef BIG_INTEGER
#define BIG_INTEGER

#include "DoublyLinkedList.h"
#include "Node.h"
#include "IllegalArgumentException.h"
#include "NoSuchElementException.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class BigInteger 
{
private:
    int sign; // will be 0 if positive and -1 is a negative number
    string str;
    DoublyLinkedList<int>* bigIntList; // this will be the on that we turn into the big in
    
public:
    BigInteger();
    BigInteger(const string); 
    BigInteger(const BigInteger&);
    ~BigInteger();

    BigInteger& operator+( const BigInteger&); 
    BigInteger& operator-(const BigInteger&);
    bool operator<=(const BigInteger&) const; 
    bool operator>=(const BigInteger&) const; 
    bool operator==(const BigInteger&) const;
    bool operator>(const BigInteger&) const; 
    bool operator<(const BigInteger&) const; 
    BigInteger& operator=( const BigInteger&);

    friend ostream& operator<<(ostream& os, const BigInteger& list) 
    {
        os << list.toString();

        return os;
    }

    friend std::ifstream& operator>>(std::ifstream& in, BigInteger& list) 
    {
        string filename = "test.txt";
        string line;
        // Read from file
        ifstream fin(filename.c_str());  // default mode ios::in

        if (!fin) 
        {
            cerr << "error: open file for input failed!" << endl;
            abort();
        }

        while (fin) 
        {  // till end-of-file
            // Read a Line from File
            if(getline(in, line, '\n'))
                list.str += line;
            else
                list.str += line;
            
            for(int i = 0; i < list.str.length(); i++) 
            {
                int num = list.convertToInt(list.str, i);
                list.bigIntList->insertLast(num);
            }

            return in;
        }

        fin.close();

        return in;
    }   

    bool isNegative();
    int getLength();
    string toString() const;
    string listToString(const DoublyLinkedList<int>&);
    DoublyLinkedList<int>* createList(const string);
    string convertToString(int);
    int convertToInt(string, int);
    int compareTwoBigIntegers(BigInteger*, BigInteger*);
    bool is_decimal_number(char const);
    void print_number(std::string const&);
};

// -----------------------------------------The Big Three ----------------------------------------------------------- //
// Default constructor
BigInteger::BigInteger():str("")
{
    bigIntList = new DoublyLinkedList<int>();
    sign = 0;
}

// Constructor with a string as a parameter
BigInteger::BigInteger(const string _str) 
{
    sign = 0;
    str = _str;
    bigIntList = createList(_str);
}

// Copy constructor
BigInteger::BigInteger(const BigInteger& other) 
{
    *this = other; // calls the copy assignment operator
}

// Copy assignment operator
BigInteger& BigInteger::operator=(const BigInteger& other) 
{
    DoublyLinkedList<int>* temp1 = bigIntList;

    if(&other != this)
    {
        DoublyLinkedList<int>* temp2 = other.bigIntList;
        
        temp1 = temp2;
        bigIntList = temp1;
        temp2 = nullptr;
    }

    sign = other.sign;
    str = other.str;

    temp1 = nullptr;
    delete temp1;

    return *this;
}


// Destructor
BigInteger::~BigInteger()
{
    bigIntList = nullptr;
    delete bigIntList;
}

/* ---------------------------------------- OPERATOR OVERLOADING ---------------------------------------------------- */
// Equality operator
bool BigInteger::operator==(const BigInteger& other) const 
{
    return (str == other.str);
}

// Addition operator
BigInteger& BigInteger::operator+(const BigInteger& other) 
{
    DoublyLinkedList<int>* sumsList = new DoublyLinkedList<int>(); // temp list to hold sum values
    DoublyLinkedList<int>* list2 = other.bigIntList; 
    
    bigIntList->setIteratorLast();
    list2->setIteratorLast();
    bool isThisIteratorNull = bigIntList->isIteratorNULL();
    bool isOtherIteratorNull = other.bigIntList->isIteratorNULL();
    string newStr = "";
    int carry = 0; // to carry the 1
    int sum = 0; // to hold sum of nodes in each list
    

    while(!isThisIteratorNull || !isOtherIteratorNull) 
    {
        int a = (!isThisIteratorNull) ? bigIntList->getData() : 0;
        int b = (!isOtherIteratorNull) ? list2->getData() : 0;
        
        // when the sum of two nodes is > 10, enter the remainder into sums list and carry the 1
        sum = carry + (a + b); 
        carry = (sum >= 10) ? 1 : 0;

        // we will want to enter this into the end of the list so it pushes the values towards the front of the list
        sumsList->insertLast(sum % 10);
        if (bigIntList->hasPrev())
            bigIntList->prev();
        else
            isThisIteratorNull = true;

        if(list2->hasPrev())
            list2->prev();
        else
            isOtherIteratorNull = true;
    }

    if(carry > 0)
       sumsList->insertLast(carry);

    bigIntList->clear();
    sumsList->setIteratorFirst();
    bool isSumsIteratorNull = sumsList->isIteratorNULL();
    // by the time we get here the sums list should be the value of the sums of each node.
    while(!isSumsIteratorNull)
    {
        bigIntList->insertFirst(sumsList->getData());

        bigIntList->setIteratorFirst();

        string number = convertToString(bigIntList->getData());
        newStr = number + newStr; // used this to in a way reverse the string value to match the linked list
        if(sumsList->hasNext())
            sumsList->next();
        else 
            isSumsIteratorNull = true;
    }

    str = newStr;
    
    sumsList = nullptr;
    list2 = nullptr;
    delete sumsList;
    delete sumsList;

    return *this;
} // end +operator

// // subtraction operator
BigInteger& BigInteger::operator-(const BigInteger& other)
{
    // steps to find subtraction:
    // [x] 1. Calculate sizes of given two linked lists.
    // [x] 2. If sizes are not the same, then append zeros in the smaller linked list.
    // [x] 3. If the size is the same, then follow the below steps:
    // [x] 1. Find the smaller valued linked list.
    // [x] 2. One by one subtract nodes of the smaller-sized linked list from the larger size. 
    // Keep track of borrow while subtracting.

    string newStr = "";

    int carry = 0, diff = 0, borrow = 0;
    bool isThisIteratorNull = false;

    DoublyLinkedList<int>* list1 = bigIntList;
    DoublyLinkedList<int>* list2 = other.bigIntList;
    DoublyLinkedList<int>* diffList = new DoublyLinkedList<int>();
    BigInteger largerNumber;
    BigInteger smallerNumber;
    if (*this > other) {
        largerNumber = *this;
        smallerNumber = other;
    }
    else {
        largerNumber = other;
        smallerNumber = *this;
    }

    int len1 = list1->getLength(); // length of (*this)
    int len2 = list2->getLength(); // length of (&other)

    if (len2 > len1) {
        while (len1 != len2)
        {
            list1->insertFirst(0);
            len1++;
        }
        // if we are doing list1 - list2 then the result will be negative
        // if the list is negative then we will add '-' to the start of the string
    }

    if (len1 > len2)
    {
        while (len2 != len1)
        {
            list2->insertFirst(0);
            len2++;
        }
        // if we are doing list2 - list1 then the result will be negative
        // if the list is negative then we will add '-' to the start of the string
    }
    if (*this == smallerNumber)
    {
        str = str + "-";
        sign = -1;
    }
    list1->setIteratorFirst();
    list2->setIteratorFirst();

    while (!isThisIteratorNull)
    {
        int result;
        int x = list1->getData();
        int y = list2->getData();

        if (largerNumber == other)
        {
            
            if (carry == -1) {
                borrow = 10;
            }
            else {
                borrow = 0;
            }
            for (int i = 0; i < 10; i++) {
                if (y - i == x) {
                    result = i;
                    break;
                }
            }

            if (x <= result) {
                carry = -1;
                diff = borrow - (result + carry);
            }
            else {
                carry = 0;
                diff = borrow - (y + carry);
            }
        }
        else 
        {
            for (int i = 0; i < 10; i++) {
                if (x - i == y) {
                    result = i;
                    break;
                }
            }
            diff = result;
        }

        if (list1->hasNext())
        {
            list1->next();
            list2->next();
        }
        else
            isThisIteratorNull = true;
       

        diffList->insertFirst(diff);

        // remove any padded zeros from the front
        if (diff == 0 && diffList->getLength() > 1)
            diffList->deleteFirst();
        else
            newStr += convertToString(diff);
    }

    bigIntList = diffList;
    str = newStr;

    list1 = nullptr;
    list2 = nullptr;
    diffList = nullptr;
    delete list1;
    delete list2;
    delete diffList;
    return *this;
} // end -operator
 
// less than operator
bool BigInteger::operator<(const BigInteger& other) const 
{
    BigInteger temp1 = *this;
    BigInteger temp2 = other;

    bool isThisIteratorNull = false;

    int len1 = temp1.bigIntList->getLength();
    int len2 = temp2.bigIntList->getLength();

    if (len2 > len1) 
    {
        while(len1 != len2) 
        {
            temp1.bigIntList->insertFirst(0);
            len1++;
        }
        // if we are doing list1 - list2 then the result will be negative
        // if the list is negative then we will add '-' to the start of the string
    }
    if (len1 > len2)
    {
        while(len2 != len1) 
        {
            temp2.bigIntList->insertFirst(0);
            len2++;
        }
        // if we are doing list2 - list1 then the result will be negative
        // if the list is negative then we will add '-' to the start of the string
    }

    temp1.bigIntList->setIteratorLast();
    temp2.bigIntList->setIteratorFirst();

    while(!isThisIteratorNull) 
    {
        if (temp1.bigIntList->getData() < temp2.bigIntList->getData())
            return false;
        if(temp1.bigIntList->hasNext()) 
        {
            temp1.bigIntList->next();
            temp2.bigIntList->next();
        } 
        else 
            isThisIteratorNull = true;
    }
    return true;
}  

// greater than operator
bool BigInteger::operator>(const BigInteger& other) const 
{
    BigInteger temp1 = *this;
    BigInteger temp2 = other;

    bool isThisIteratorNull = false;

    int len1 = temp1.bigIntList->getLength();
    int len2 = temp2.bigIntList->getLength();

    if (len2 > len1) 
    {
        while(len1 != len2) 
        {
            temp1.bigIntList->insertFirst(0);
            len1++;
        }
        // if we are doing list1 - list2 then the result will be negative
        // if the list is negative then we will add '-' to the start of the string
    }
    if (len1 > len2)
    {
        while(len2 != len1) 
        {
            temp2.bigIntList->insertFirst(0);
            len2++;
        }
        // if we are doing list2 - list1 then the result will be negative
        // if the list is negative then we will add '-' to the start of the string
    }

    temp1.bigIntList->setIteratorFirst();
    temp2.bigIntList->setIteratorFirst();

    while(!isThisIteratorNull) 
    {
        if (temp1.bigIntList->getData() < temp2.bigIntList->getData())
            return false;
        if(temp1.bigIntList->hasNext()) 
        {
            temp1.bigIntList->next();
            temp2.bigIntList->next();
        } 
        else 
            isThisIteratorNull = true;
    }
    return true;
} 

bool BigInteger::operator<=(const BigInteger& other) const 
{
    return (*this < other || *this == other);
}

bool BigInteger::operator>=(const BigInteger& other) const 
{
    return (*this > other || *this == other);
}

// --------------------------------------------- USER DEFINED METHODS ----------------------------------------------//

std::string BigInteger::toString() const 
{
    std::string result = str;

    for (int i = str.length() - 1; i >= 0; i--)
        result += str.at(i);

    return result;
}

int BigInteger::convertToInt(string str, int num) 
{
    return str.at(num) - '0';
}

string BigInteger::convertToString(int num) 
{
    return to_string(num);
}

DoublyLinkedList<int>* BigInteger::createList(const string str) 
{
    DoublyLinkedList<int>* temp = new DoublyLinkedList<int>();

    for(int i = 0; i < str.length(); i++) 
        temp->insertLast(convertToInt(str, i));
    
    return temp;
}

int BigInteger::getLength() 
{
    return str.length();
}

bool BigInteger::isNegative() 
{
    return sign == -1;
}

// new bool that only has acceptable numbers from 0-9
//includes char c as a parameter 
bool BigInteger::is_decimal_number(char const c) 
{
    return c >= '0' && c <= '9';
}

// new void that has a string parameter
//if its different than is_desimal number, throw an exception
void BigInteger::print_number(std::string const& s) 
{
    for (char const c : s)
        if (!is_decimal_number(c)) {
            throw IllegalArgumentException{ std::string{"IllegalArgumentException: string \""} + s + "\" is not a number!" };
        }
    std::cout << s;
}

#endif