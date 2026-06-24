#include "main.h"

Cat vet(std::string name, int age) {
    return {name, age};
}

int main() {
    vet("fred", 10);
}

