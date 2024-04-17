#pragma once
#include <iostream>
#include <string>
/*
Tipos de Producto:
        Los productos de la farmacia tienen categoría y sub-categoría, precio por
        producto e ID por producto. (Es necesario tener un archivo de “Bodega”
        donde se puedan cargar todos los productos Al iniciar el programa, con
        un mínimo de 5 categorías, 2 sub-categorías por categoría y al menos 3
        tipos de producto por sub-categoría)
*/

/*
categorias (?)
    farmacos
        antiinflamatorios
        antibioticos
    belleza
        maquillaje
        cremas
    limpieza dental
        pastas dentales
        enjuage bucal
    limpieza general
        shampoo
        jabones
    suministros medicos
        alcohol
        gaza
*/

class ProductoBase{
    private:
        int codigo_producto;
        std::string nombre_producto;
        std::string categoria_producto;
};