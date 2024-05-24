#include "../include/Bodega.h"

Bodega::Bodega() {}

Bodega::~Bodega() {
    std::cout << "Destruyendo objeto bodega" << std::endl;
}

void Bodega::agregarProductos(std::string nombre_producto, Producto* producto) {
    productos.insert(nombre_producto, producto);
}

Producto* Bodega::obtenerProducto(std::string nombre_producto) {
    try {
        return productos.get(nombre_producto);
    } catch (const std::runtime_error& e) {
        return nullptr;
    }
}

std::string Bodega::obtenerTodosLosProductos() {
    std::stringstream ss;
    ss << "Productos en la bodega:\n";
    for (int i = 0; i < productos.getCapacity(); ++i) {
        HashNode<std::string, Producto*>* node = productos.getTable()[i];
        while (node != nullptr) {
            ss << "Nombre: " << node->key << std::endl;
            node = node->next;
        }
    }
    return ss.str();
}