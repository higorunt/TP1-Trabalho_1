#include "../../include/dominios/Duracao.hpp"

void Duracao::validar(int valor) {
    if (valor < 0 || valor > 360) {
        throw std::invalid_argument("Duracao invalida. Deve estar entre 0 e 360.");
    }
}

Duracao::Duracao(int valor) {
    validar(valor);
    this->valor = valor;
}

int Duracao::getValor() const {
    return valor;
}

void Duracao::setValor(int valor) {
    validar(valor);
    this->valor = valor;
}
