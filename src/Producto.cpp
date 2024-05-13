#include "/include/Producto.h"

// Constructor
Producto::Producto(std::string nombre, 
                  std::string categoria, 
                  std::string subCategoria, 
                  float precio, 
                  int id): 
{
    this -> nombre = nombre;
    this -> categoria = categoria;
    this -> subCategoria = subCategoria;
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
    return subCategoria;
}

float Producto::getPrecio(){
    return precio;
}

int Producto::getID(){
    return id;
}
