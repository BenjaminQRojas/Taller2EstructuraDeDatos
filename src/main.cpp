#include <queue>
#include <iostream>
#include </workspaces/Taller2EstructuraDeDatos/include/Cliente.h>
#include </workspaces/Taller2EstructuraDeDatos/include/ClientePreferencial.h>


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

void dar_numero(std::queue<Cliente*> &cola_comun, 
                std::queue<ClientePreferencial*> &cola_preferencial){
    int opcion;
    
    std::string nombre;
    int edad;
    std::string preferencia;

    std::cout<<"ingrese nombre: "<<std::endl;
    std::cin>>nombre;
    std::cout<<"ingrese edad: "<<std::endl;
    std::cin>>edad;
    if(edad >= 60){
        preferencia = "tercera edad";
    }else{
        std::cout<<"discapacidad (1) / embarazada (2) / nada (3)"<<std::endl;
        std::cin>>opcion;
        switch (opcion)
        {
        case 1:
            preferencia = "discapacidad";
            break;
        case 2:
            preferencia = "embarazada";
            break;
        default:
            preferencia = "nada";
            break;
        }
    }
    
    if(preferencia == "nada"){
        Cliente* cliente = new Cliente(nombre, edad);
        cola_comun.push(cliente);
    }else{
        ClientePreferencial* clientepref = new ClientePreferencial(nombre, edad, preferencia);
        cola_preferencial.push(clientepref);
    }
}

void fila(std::queue<Cliente*> &cola_comun, 
          std::queue<ClientePreferencial*> &cola_preferencial){
    int opcion;
    std::cout<<"MENU"<<std::endl;
    std::cout<<"(1) agregar clientes a la cola"<<std::endl;
    std::cout<<"(2) finalizar"<<std::endl;
    std::cin>>opcion;
    while(opcion != 2){
        dar_numero(cola_comun, cola_preferencial);
        std::cout<<"cliente agregado a la cola"<<std::endl;
        std::cout<<"(1) agregar clientes a la cola"<<std::endl;
        std::cout<<"(2) finalizar"<<std::endl;
        std::cin>>opcion;
    }
}

/**
 * ordenar cola preferencial
*/
void ordenar_colas(std::queue<ClientePreferencial*>  &cola_1,
                   std::queue<ClientePreferencial*>  &cola_2, 
                   std::queue<ClientePreferencial*>  &cola_aux, 
                   std::string pref)
{
    while(!cola_1.empty())//mientras no sea vacio
    {
        if(cola_1.front() -> getPreferencia() == pref){//si el elemento es igual a pref(tercera edad, discapacidad, embarazada)
            ClientePreferencial* elemento = cola_1.front();
            
            cola_1.pop();
            cola_2.push(elemento);
            
        }else{//todo lo demas a cola aux
            ClientePreferencial* elemento = cola_1.front();
            cola_1.pop();
            cola_aux.push(elemento);
        }
    }
    cola_1.swap(cola_aux);//cambia la cola_1 con cola_aux
}

void mostrar_cola(std::queue<ClientePreferencial*> cola){
    while(!cola.empty()){
        std::cout<<cola.front() -> getNombre() + " " +cola.front() -> getPreferencia()<<std::endl;
        cola.pop();
    }
}

int main(){
    std::queue<Cliente*> cola_comun; 
    std::queue<ClientePreferencial*> cola_1; //cola principal (llena al inicio, vacia al final)
    std::queue<ClientePreferencial*> cola_aux; //cola auxiliar (vacia)
    std::queue<ClientePreferencial*> cola_2; //cola 2 o final(?) (vacia al inicio, llena al final)
    fila(cola_comun, cola_1);
    ordenar_colas(cola_1,cola_2,cola_aux,"tercera edad");//pone los 1 en cola_2
    ordenar_colas(cola_1,cola_2,cola_aux,"embarazada");//pone los 2 en cola_2
    ordenar_colas(cola_1,cola_2,cola_aux,"discapacidad");//pone los 3 en cola_2
    mostrar_cola(cola_2);
    return 0;
}