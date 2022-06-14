/**
 * @file NoSuchElementException.h
 * @author Christopher Liudahl-Rackley and Mohamed Elfergani
 * @brief NoSuchElementException class
 * @version 0.1
 * @date 2021-11-07
 */

#ifndef NO_SUCH_ELEMENT_EXCEPTION
#define NO_SUCH_ELEMENT_EXCEPTION

#include <stdexcept>
#include <string>

class NoSuchElementException : public std::runtime_error {
public: 
    NoSuchElementException(const std::string& message = ""):std::runtime_error("No such element: " + message) {}


};

#endif //NO_SUCH_ELEMENT_EXCEPTION