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

std::vector<Producto*> Cliente::getCarrito()
{
    return this->carrito;
};

void Cliente::agregarProducto(Producto* producto)
{
    carrito.push_back(producto);
};

Producto* Cliente::obtenerProductoI(int i)
{
    return carrito[i];
};

void Cliente::vaciarCarrito()
{
    carrito.clear();
};

void Cliente::setNombre(std::string nombre)
{
    this -> nombre = nombre;
};

void Cliente::setEdad(int edad)
{
    this -> edad = edad;
};
