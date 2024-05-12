#pragma once
#include <iostream>

class Cliente{
    private:
        std::string nombre;
        int edad;
    public:
        //constructor vacio cliente
        Cliente();
        //constructor con parametros cliente
        Cliente(std::string nombre, int edad);
        //destructor
        ~Cliente();

        //metodos
        //get parametro nombre
        std::string getNombre();
        //get parametro edad
        int getEdad();
        //set nombre por un string
        void setNombre(std::string nombre);
        //set edad por un int
        void setEdad(int edad);
};