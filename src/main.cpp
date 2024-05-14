#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Cliente.h"
#include "../include/ClientePreferencial.h"
#include "../include/Producto.h"
#include "../include/Bodega.h"

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
*/

/**
 * Funcion para leer archio bodega y el archivo stock, para luego guardar los datos en la clase
 * bodega.
*/

int leerArchivoBodega(Bodega* &bodega){
    std::ifstream archivoBodega("data/Bodega.txt");
    std::ifstream archivoStock("data/StockBodega.txt");
    if (!archivoBodega.is_open()) {
        std::cerr << "El archivo de la bodega no existe." << std::endl;
    }else{
        if(!archivoStock.is_open()){
            std::cerr << "El archivo de la bodega no existe." << std::endl;
        }
    }
    

    std::string lineaBodega;
    std::string lineaStock;
    while (std::getline(archivoBodega, lineaBodega) && std::getline(archivoStock,lineaStock)) {
        std::stringstream ssBodega(lineaBodega);
        std::stringstream ssStock(lineaStock);
        std::string nombre, categoria, subcategoria;
        float precio;
        int idProducto,idStock,stock;
        char comma;
        if (std::getline(ssBodega,nombre, ',') &&
            std::getline(ssBodega, categoria , ',') &&
            std::getline(ssBodega,subcategoria, ',') &&
            (ssBodega >> precio >> comma) &&
            (ssBodega >> idProducto)){
                if((ssStock >> idStock >> comma) && (ssStock >> stock)){
                    // Crea un objeto Producto con los datos extraídos
                    Producto* producto = new Producto(nombre,categoria, subcategoria, precio, idProducto);
                    if(idProducto == idStock){
                        // Agrega el producto a la bodega con su respectivo stock
                        std::cout<<"producto "+nombre+" agregado con stock " << stock<<std::endl;
                        bodega -> agregarProductos(nombre, producto, stock);
                    }else{
                        // Agrega el producto a la bodega con stock 0
                        bodega -> agregarProductos(nombre, producto, 0);
                    }
                }
        } else {
            std::cerr << "Error al analizar las líneas: " +lineaBodega+ " "+lineaStock <<std::endl;
        }
    }
    // Cierra los archivos
    archivoBodega.close();
    archivoStock.close();
}



/*

void generarVenta(Bodega& bodega,std::vector<std::string>& productos){
    std::cout<< "**GESTIONAR VENTA**" << std::endl;
    std::cout << "Se generó la venta con los siguientes productos:\n";
    // Recorre la lista de productos vendidos
    for (const std::string& nombreProducto : productos) {
        // Busca el producto en la bodega
        Producto* producto = bodega.obtenerProducto(nombreProducto);
        if (producto != nullptr) {
            // Resta el stock vendido del producto
            int stockActual = bodega.obtenerStockProducto(nombreProducto);
            int cantidadVendida = 1; // Suponiendo que se vende una unidad a la vez
            bodega.actualizarStock(nombreProducto, stockActual - cantidadVendida);
            // Verifica si el stock es menor o igual a cero y elimina el producto si es el caso
            if (bodega.obtenerStockProducto(nombreProducto) <= 0) {
                // Aquí podrías implementar lógica adicional si un producto se queda sin stock
            }
        } else {
            std::cerr << "Error: Producto no encontrado en la bodega: " << nombreProducto << std::endl;
            // Aquí podrías manejar la situación de un producto no encontrado de otra manera si lo deseas
        }
    }

} 
*/ 
void ingresarPedido(Bodega* &bodega){
    std::vector<std::string> productosSolicitados;
    std::cout << "Ingrese los productos que el cliente solicita (Ingrese 'fin' para finalizar):\n";
    std::string producto;
    while (true) {
        std::cout << "Producto: ";
        std::getline(std::cin, producto);
        // si producto no esta 

        if (producto == "fin") {
            break;  // Salir del bucle si se ingresa 'fin'
        }

        productosSolicitados.push_back(producto);  // Agregar el producto a la lista
    }
    //llamar a una función para generar la venta con los productos ingresados
    //generarVenta(bodega,productosSolicitados);
}

void dar_numero(std::queue<Cliente*> &cola_comun, 
                std::queue<ClientePreferencial*> &cola_preferencial){
    int opcion;

    std::string nombre;
    int edad;
    std::string preferencia;

    std::cout<<"Ingrese nombre: "<<std::endl;
    std::cin>>nombre;
    std::cout<<"Ingrese edad: "<<std::endl;
    std::cin>>edad;
    if(edad >= 60){
        preferencia = "Tercera edad";
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

void agregarProductosCliente(Bodega* &bodega, Cliente* &cliente){
    //imprimir cliente
    std::cout<<"Cliente: "<<cliente ->getNombre()<<std::endl;
    //imprimir productos de la bodega
    std::cout<<bodega ->obtenerTodosLosProductos()<<std::endl;

}

void GestionarVenta(std::queue<Cliente*> &cola_comun,
                    std::queue<ClientePreferencial*> &cola_pref,
                    Bodega* &bodega){
    int opcion=0;
    std::cout<< "**GESTIONAR VENTA**" << std::endl;
    //mientras una de las colas tenga personas
    while(!cola_comun.empty() || !cola_pref.empty()){
        //primero atender a los clientes de la cola preferencial
        while(!cola_pref.empty()){
            Cliente* cliente = cola_pref.front();
            agregarProductosCliente(bodega,cliente);
        }
        //segundo, atender a los clientes de la cola comun
        while(!cola_comun.empty()){
            Cliente* cliente = cola_comun.front();
            agregarProductosCliente(bodega,cliente);
        }
    }

}


int interfazUsuario(){
    int opcion=0;
    std::cout<< "Bienvenido" << std::endl;
    std::cout << "(1) Gestionar Clientes" << std::endl;
    std::cout << "(2) Gestionar Venta" << std:: endl;
    std::cout << "(3) salir" << std::endl;

    std::cout << "Ingrese una opcion:" << std::endl;
    while (!(std::cin >> opcion) || opcion < 1 || opcion > 3){
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
        //GestionarVenta();
        break;
    case 3:
     std::cout << "Saliendo del programa..." << std::endl;
        break;
    }
}

int main(){
    Bodega* bodega = new Bodega();
    Menu(bodega);
    leerArchivoBodega(bodega);
    return 0;
};
