#include <iostream>

/*
problema: 
    Una farmacia necesita un programa para organizar las ventas del local, dentro
    de los requerimientos del software, se espera poder conocer la cantidad de
    productos en bodega por categoría y sub-categoría, generar boletas de venta y
    manejo de clientes utilizando un sistema de colas con preferencia.
requerimientos:
    tecnicos:
        - usar POO
        - usar punteros, pilas y colas
        - interfaz de usuario
        - persistencia de datos (cargar y guardar datos)
detalles:
    Tipos de Producto:
        Los productos de la farmacia tienen categoría y sub-categoría, precio por
        producto e ID por producto. (Es necesario tener un archivo de “Bodega”
        donde se puedan cargar todos los productos Al iniciar el programa, con
        un mínimo de 5 categorías, 2 sub-categorías por categoría y al menos 3
        tipos de producto por sub-categoría)
    Tipos de Clientes:
        Los clientes tienen que ser identificados por tipo (cliente normal, cliente
        preferencial) para poder entregar un número de atención.
        Los clientes preferenciales pueden dividirse en “Tercera edad”,
        “Embarazadas”, “Discapacidad” y estos deben atenderse primero si es
        que se encuentran en la fila (el orden de atención siempre es tercera
        edad>Discapacidad>Embarazada).
    Flujo básico de caja:
        Se atiende nuevo cliente si es que hay alguno en la fila → se ingresan
        productos que cliente solicito → se genera venta → se llama a nuevo
        cliente si es que hay alguno en fila
    Uso de listas y otras estructuras:
        Uso de listas (específicamente uso de hashmap o similar) para manejo
        de productos
        Uso de queue/stack para manejo de fila de clientes.
        No se pueden utilizar librerías para la creación de las listas/hashmap
*/

int main(){
    std::cout<<"inicio programa"<<std::endl;
    return 0;
}