#pragma once
#include <iostream>
#include <string>
/*
Tipos de Clientes:
        Los clientes tienen que ser identificados por tipo (cliente normal, cliente
        preferencial) para poder entregar un número de atención.
        Los clientes preferenciales pueden dividirse en “Tercera edad”,
        “Embarazadas”, “Discapacidad” y estos deben atenderse primero si es
        que se encuentran en la fila (el orden de atención siempre es tercera
        edad>Discapacidad>Embarazada).
*/

class ClienteBase{
    private:
        std::string rut;
        std::string nombre;
        std::string apellido;
        std::string tipo_cliente;
}
;