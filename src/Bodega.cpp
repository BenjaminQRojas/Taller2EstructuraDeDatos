#include "../include/Bodega.h"

Bodega::Bodega(){};

Bodega::~Bodega()
{
    std::cout<<"destruyendo objeto bodega"<<std::endl;
};

void Bodega::agregarProductos(std::string nombre_producto, Producto* producto)
{
    this -> productos[nombre_producto] = producto;
};

Producto* Bodega::obtenerProducto(std::string nombre_producto)
{
    // Verificar si el producto está presente en el mapa
    auto iter = productos.find(nombre_producto);
    if (iter != productos.end()) {
        // Devolver un puntero al producto encontrado
        return iter->second;
    } else {
        // El producto no está presente, devolver nullptr
        return nullptr;
    }
};


std::string Bodega::obtenerTodosLosProductos() {
    std::stringstream ss;

    ss << "Productos en la bodega:\n";
    for (const auto& par : productos) {
        std::string nombre = par.first;
        Producto* producto = par.second;
        ss << "Nombre: " << nombre << std::endl;
    }

    return ss.str();
};