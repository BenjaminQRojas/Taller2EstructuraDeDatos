#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Cliente.h"
#include "../include/ClientePreferencial.h"
#include "../include/Producto.h"
#include "../include/Bodega.h"



int leerArchivoBodega(Bodega* &bodega){
    std::ifstream archivoBodega("data/Bodega.txt");
    
    if (!archivoBodega.is_open()) {
        std::cerr << "El archivo de la bodega no se puede abrir." << std::endl;
        return -1; // Retorna un código de error
    }
    
    
    std::string lineaBodega;
    while (std::getline(archivoBodega, lineaBodega)) {
        std::stringstream ssBodega(lineaBodega);
        std::string nombre, categoria, subcategoria;
        float precio;
        int idProducto;
        char comma;
        if (std::getline(ssBodega,nombre, ',') &&
            std::getline(ssBodega, categoria , ',') &&
            std::getline(ssBodega,subcategoria, ',') &&
            (ssBodega >> precio >> comma) &&
            (ssBodega >> idProducto)){
                Producto* producto = new Producto(nombre,categoria, subcategoria, precio, idProducto);
                bodega -> agregarProductos(nombre,producto);
        } else {
            std::cerr << "Error al analizar las líneas: " +lineaBodega<<std::endl;
        }
    }
    // Cierra los archivos
    archivoBodega.close();
    return 0;
}

int guardarVenta(std::vector<std::string> ventas){
    std::ofstream archivo("data/Ventas.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return -1;
    }
    for (const auto& venta : ventas) {
        archivo << venta << std::endl;
    }
    archivo.close();
    return 0;
}

std::string generarVenta(Bodega* &bodega,std::vector<Producto*> &productos){
    std::cout<< "**GESTIONAR VENTA**" << std::endl;
    std::cout << "Se generó la venta con los siguientes productos:\n";
    // Recorre la lista de productos vendidos
    int precioTotal = 0;
    for (Producto* producto : productos) {
        std::cout<<producto ->getNombre()<<std::endl;
        precioTotal += producto -> getPrecio();
        
    }
    std::cout<<"total: "<<precioTotal<<std::endl;
    std::string salida = "Venta total: "+precioTotal;
    return salida;
}

void ingresarPedido(Bodega* &bodega,std::vector<std::string> ventas){
    std::vector<Producto*> productosSolicitados;
    std::cout << "Ingrese los productos que el cliente solicita (Ingrese 'fin' para finalizar):\n";
    std::string producto;
    while (true) {
        std::cout << "Producto: ";
        std::getline(std::cin, producto);
        Producto* productoObtenido = bodega-> obtenerProducto(producto);
        // Agregar el producto a la lista
        if(bodega->obtenerProducto(producto) != nullptr){
            productosSolicitados.push_back(productoObtenido);
        }else {
            std::cerr << "Error: Producto no encontrado en la bodega: " << producto << std::endl;
            // Aquí podrías manejar la situación de un producto no encontrado de otra manera si lo deseas
        }
        if (producto == "fin") {
            break;  // Salir del bucle si se ingresa 'fin'
        } 
    }
    
    //llamar a una función para generar la venta con los productos ingresados
    ventas.push_back(generarVenta(bodega,productosSolicitados));
}

void dar_numero(std::queue<Cliente*> &cola_comun, 
                std::queue<ClientePreferencial*> &cola_preferencial) {
    int opcion;
    std::string nombre;
    int edad;
    std::string preferencia;

    std::cout << "Ingrese nombre: " << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    std::getline(std::cin, nombre);

    std::cout << "Ingrese edad: " << std::endl;
    while (!(std::cin >> edad)) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Por favor, ingrese una edad válida: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada

    if (edad >= 60) {
        preferencia = "Tercera edad";
    } else {
        std::cout << "discapacidad (1) / embarazada (2) / nada (3)" << std::endl;
        while (!(std::cin >> opcion) || opcion < 1 || opcion > 3) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Opción ingresada no válida. Por favor, ingrese una opción válida (1/2/3): ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        switch (opcion) {
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
    
    if (preferencia == "nada") {
        Cliente* cliente = new Cliente(nombre, edad);
        cola_comun.push(cliente);
    } else {
        ClientePreferencial* clientepref = new ClientePreferencial(nombre, edad, preferencia);
        cola_preferencial.push(clientepref);
    }
}

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

void fila(std::queue<Cliente*> &cola_comun, 
          std::queue<ClientePreferencial*> &cola_preferencial){
    int opcion;
    std::cout<<"MENU"<<std::endl;
    std::cout<<"(1) Agregar clientes a la cola"<<std::endl;
    std::cout<<"(2) Finalizar"<<std::endl;
    std::cin>>opcion;
    while(opcion != 2){
        dar_numero(cola_comun, cola_preferencial);
        std::cout<<"Cliente agregado a la cola"<<std::endl;
        std::cout<<"************"<<std::endl;
        std::cout<<"(1) Agregar clientes a la cola"<<std::endl;
        std::cout<<"(2) Finalizar"<<std::endl;
        std::cin>>opcion;
    }
}

void GestionarCliente(std::queue<Cliente*> &cola_comun,
                      std::queue<ClientePreferencial*> &cola_1,
                      std::queue<ClientePreferencial*> &cola_2,
                      std::queue<ClientePreferencial*> &cola_aux,
                      Bodega* &bodega){
    std::cout<< "**GESTIONAR CLIENTE**" << std::endl;
    fila(cola_comun, cola_1);
    ordenar_colas(cola_1,cola_2,cola_aux,"tercera edad");//pone los 1 en cola_2
    ordenar_colas(cola_1,cola_2,cola_aux,"embarazada");//pone los 2 en cola_2
    ordenar_colas(cola_1,cola_2,cola_aux,"dicapacidad");//pone los 3 en cola_2
}

void GestionarVenta(std::queue<Cliente*> &cola_comun,
                    std::queue<ClientePreferencial*> &cola_pref,
                    Bodega* &bodega){
    int opcion=0;
    std::vector<std::string> ventas;
    std::cout<< "**GESTIONAR VENTA**" << std::endl;
    //mientras una de las colas tenga personas
    while(!cola_comun.empty() || !cola_pref.empty()){
        //primero atender a los clientes de la cola preferencial
        while(!cola_pref.empty()){
            ClientePreferencial* cliente = cola_pref.front();
            //mostrar productos
            std::cout<<"Hola "<<cliente->getNombre()<<std::endl;
            std::cout<<bodega -> obtenerTodosLosProductos()<<std::endl;
            //pedir productos
            ingresarPedido(bodega,ventas);
            //eliminar cliente de la cola
            cola_pref.pop();
            delete cliente;
        }
        //segundo, atender a los clientes de la cola comun
        while(!cola_comun.empty()){
            Cliente* cliente = cola_comun.front();
            //mostrar productos
            std::cout<<"Hola "<<cliente->getNombre()<<std::endl;
            std::cout<<bodega -> obtenerTodosLosProductos()<<std::endl;
            //pedir productos
            ingresarPedido(bodega,ventas);
            //eliminar cliente de la cola
            cola_comun.pop();
            delete cliente;
        }
    }
    if(guardarVenta(ventas) == 0){
        std::cout<<"ventas guardadas"<<std::endl;
    }
}


int interfazUsuario(){
    int opcion=0;
    std::cout<< "Bienvenido" << std::endl;
    std::cout << "(1) Gestionar Clientes" << std::endl;
    std::cout << "(2) salir" << std::endl;

    std::cout << "Ingrese una opcion:" << std::endl;
    while (!(std::cin >> opcion) || opcion < 1 || opcion > 2){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer
        std::cout << "Opción ingresada no válida. Por favor, ingrese una opción válida: ";
    }
    return opcion;
}



void Menu(Bodega* &bodega){
    std::queue<Cliente*> cola_comun; 
    std::queue<ClientePreferencial*> colapref_inicial; //cola principal (llena al inicio, vacia al final)
    std::queue<ClientePreferencial*> colapref_aux; //cola auxiliar (vacia)
    std::queue<ClientePreferencial*> colapref_final; //cola final (vacia al inicio, llena al final)
    int opcion = interfazUsuario();
    switch (opcion) {
    case 1:
        GestionarCliente(cola_comun,colapref_inicial,colapref_final,colapref_aux,bodega);
        GestionarVenta(cola_comun,colapref_final,bodega);
        break;
    case 2:
        GestionarVenta(cola_comun,colapref_final,bodega);
        break;
    case 3:
     std::cout << "Saliendo del programa..." << std::endl;
        break;
    }
}

int main(){
    Bodega* bodega = new Bodega();
    if(leerArchivoBodega(bodega) == 0){
        Menu(bodega);
    }
    delete bodega;
    return 0;
};
