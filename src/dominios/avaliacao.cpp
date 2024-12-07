#include "../../include/dominios/avaliacao.h"

/**
 * @brief M�todo para validar o valor da avalia��o.
 * @param valor Valor a ser validado.
 * @throw std::invalid_argument Se o valor n�o estiver entre 1 e 5.
 */
void Avaliacao::validar(int valor) {
    if (valor < 1 || valor > 5) {
        throw std::invalid_argument("Avaliacao invalida. Deve estar entre 1 e 5.");
    }
}

/**
 * @brief Construtor da classe Avaliacao.
 * @param valor Avalia��o inicial.
 */
Avaliacao::Avaliacao(int valor) {
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Define o valor da avalia��o.
 * @param valor Nova avalia��o.
 */
void Avaliacao::setValor(int valor) {
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Obt�m o valor da avalia��o.
 * @return Valor da avalia��o.
 */
int Avaliacao::getValor() const {
    return valor;
}