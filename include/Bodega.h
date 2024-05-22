#include "Producto.h"
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>

class Bodega{
    private:
        std::map<std::string , Producto*> productos; //<nombre_producto(key), puntero_producto(value)>
    public:
        //constructor vacio
        Bodega();
        //destructor
        ~Bodega();
        //metodo agregar productos a su respectivo mapa
        void agregarProductos(std::string nombre_producto, Producto* producto);
        //metodo obtener un producto en especifico
        Producto* obtenerProducto(std::string nombre_producto);
        //metodo obtener todos los productos en un string
        std::string obtenerTodosLosProductos();
};