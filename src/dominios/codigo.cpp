#include "dominios/Codigo.hpp"

Codigo::Codigo(const std::string &valor) : valor(valor)
{
    // Adicione a valida��o do c�digo aqui, se necess�rio
}

std::string Codigo::getValor() const
{
    return valor;
}