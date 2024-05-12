#pragma once
#include <iostream>
#include "Cliente.h"

class ClientePreferencial : public Cliente{
    private:
        std::string preferencia;
    public:
        //constructor vacio
        ClientePreferencial();
        //constructor con parametros
        ClientePreferencial(std::string nombre, int edad, std::string preferencia);
        //destructor
        ~ClientePreferencial();
        //metodos
        //get parametro preferecia
        std::string getPreferencia();
        //set preferencia por un string
        void setPreferencia(std::string preferencia);
};