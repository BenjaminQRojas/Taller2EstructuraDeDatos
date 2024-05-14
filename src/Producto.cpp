#include "../include/Producto.h"

// Constructor
Producto::Producto(std::string nombre, 
                  std::string categoria, 
                  std::string subcategoria, 
                  float precio, 
                  int id)
{
    this -> nombre = nombre;
    this -> categoria = categoria;
    this -> subcategoria = subcategoria;
    this -> precio = precio;
    this -> id = id;
  
};
//destructor
Producto::~Producto(){};

// Métodos Getters
std::string Producto::getNombre() {
    return nombre;
}

std::string Producto::getCategoria(){
    return categoria;
}

std::string Producto::getSubCategoria(){
    return subcategoria;
}

float Producto::getPrecio(){
    return precio;
}

int Producto::getID(){
    return id;
}
