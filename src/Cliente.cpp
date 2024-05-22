#include "../include/Cliente.h"

Cliente::Cliente(){};

Cliente::Cliente(std::string nombre, int edad)
{
    this -> nombre = nombre;
    this -> edad = edad;
};

Cliente::~Cliente()
{
    std::cout<<"destruir objeto cliente: "+nombre<<std::endl;
};

std::string Cliente::getNombre()
{
    return this -> nombre;
};

int Cliente::getEdad()
{
    return this -> edad;
};

void Cliente::setNombre(std::string nombre)
{
    this -> nombre = nombre;
};

void Cliente::setEdad(int edad)
{
    this -> edad = edad;
};
