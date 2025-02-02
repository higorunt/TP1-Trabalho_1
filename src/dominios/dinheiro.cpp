#include "dominios/Dinheiro.hpp"

Dinheiro::Dinheiro(double valor) : valor(valor) {}

double Dinheiro::getValor() const
{
    return valor;
}