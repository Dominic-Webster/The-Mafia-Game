#ifndef ROLE_H
#define ROLE_H

#include <iostream>
#include "role.h"

class Role{
    public:
        Role(){name = ""; team = ""; lvl = 1;}
        Role(std::string nm){name = nm;}
        std::string get_name(){return name;}
        std::string get_team(){return team;}
        int get_lvl(){return lvl;}
        void set_name(std::string nm){name = nm;}
        void set_team(std::string tm){team = tm;}
        void set_lvl(int lv){lvl = lv;}
    private:
        std::string name, team;
        int lvl;
};

#endif