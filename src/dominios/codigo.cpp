#include "dominios/Codigo.hpp"

Codigo::Codigo(const std::string &valor) : valor(valor)
{
    // Adicione a validação do código aqui, se necessário
}

std::string Codigo::getValor() const
{
    return valor;
}