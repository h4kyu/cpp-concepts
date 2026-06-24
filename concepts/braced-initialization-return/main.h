#ifndef CPP_CONCEPTS_MAIN_H
#define CPP_CONCEPTS_MAIN_H

#include <string>

class Cat {
public:
    Cat(std::string name, int age)
    : name_(name), age_(age) {

    }
private:
    std::string name_;
    int age_;
};

Cat vet(std::string name, int age);

#endif //CPP_CONCEPTS_MAIN_H