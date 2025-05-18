#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include "role.h"

class Person{
    public:
        Person(std::string nm){name = nm;}
        std::string get_name(){return name;}
        Role get_role(){return the_role;}
        void set_name(std::string nm){name = nm;}
        void set_role(Role rl){the_role = rl;}
    private:
        std::string name;
        Role the_role;
};

#endif
