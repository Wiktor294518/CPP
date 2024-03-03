#ifndef HASLO_H
#define HASLO_H

#include <string>

class Haslo {
public:
    std::string witryna;
    std::string haslo;
    std::string kategoria;
    std::string www;
    std::string login;

    Haslo(std::string witryna, std::string haslo, std::string kategoria,
          std::string www = "", std::string login = "");

};

#endif
