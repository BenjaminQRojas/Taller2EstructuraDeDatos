#pragma once
#include <iostream>

class Producto{  

  private:
    std::  string nombre;
    std:: string categoria;
    std:: string subcategoria;
    float precio;
    int id;

  public:
    Producto( std::string nombre, std:: string categoria, std:: string subcategoria, float precio, int id);
    //destructor
    ~Producto();
    //getters
    std::string getNombre();
    std::string getCategoria();
    std::string getSubcategoria();
    float getPrecio();
    int getID();
};
