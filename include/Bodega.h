#include "Producto.h"
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>

class Bodega{
    private:
        std::map<std::string , Producto*> productos; //<nombre_producto(key), puntero_producto(value)>
        std::unordered_map<std::string, int> stocks; // <nombre_producto(key), stock(value)>
    public:
        //constructor vacio
        Bodega();
        //destructor
        ~Bodega();
        //metodo agregar productos y stock a sus respectivos mapas
        void agregarProductos(std::string nombre_producto, Producto* producto, int stock);
        //metodo obtener un producto en especifico
        Producto* obtenerProducto(std::string nombre_producto);
        //metodo obtener stock de un producto en especifico
        int obtenerStockProducto(std::string nombre_producto);
        //metodo obtener todos los productos en un string
        std::string obtenerTodosLosProductos();
};