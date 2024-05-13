#include "../include/Bodega.h"

Bodega::Bodega(){};

Bodega::~Bodega()
{
    std::cout<<"destruyendo objeto bodega"<<std::endl;
};

void Bodega::agregarProductos(std::string nombre_producto, Producto* producto, int stock)
{
    this -> productos[nombre_producto] = producto;
    this -> stocks[nombre_producto] = stock;
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

int Bodega::obtenerStockProducto(std::string nombre_producto)
{
    // Verificar si el producto está presente en el unordered_map
    auto iter = stocks.find(nombre_producto);
    if (iter != stocks.end()) {
        // Devolver el stock del producto encontrado
        return iter->second;
    } else {
        return -1; 
    }
};