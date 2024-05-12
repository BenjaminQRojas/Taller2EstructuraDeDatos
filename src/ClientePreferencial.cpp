#include </workspaces/Taller2EstructuraDeDatos/include/ClientePreferencial.h>

ClientePreferencial::ClientePreferencial(){};

ClientePreferencial::ClientePreferencial(std::string nombre, int edad, std::string preferencia):Cliente(nombre, edad)
{
    this -> preferencia = preferencia;
};

ClientePreferencial::~ClientePreferencial()
{
    std::cout<<"detruyendo objeto cliente preferencial: "+getNombre()<<std::endl;
};

std::string ClientePreferencial::getPreferencia()
{
    return this -> preferencia;
};

void ClientePreferencial::setPreferencia(std::string preferencia)
{
    this -> preferencia = preferencia;
};