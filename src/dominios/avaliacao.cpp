#include "../../include/dominios/avaliacao.h"

/**
 * @brief Método para validar o valor da avaliação.
 * @param valor Valor a ser validado.
 * @throw std::invalid_argument Se o valor não estiver entre 1 e 5.
 */
void Avaliacao::validar(int valor) {
    if (valor < 1 || valor > 5) {
        throw std::invalid_argument("Avaliacao invalida. Deve estar entre 1 e 5.");
    }
}

/**
 * @brief Construtor da classe Avaliacao.
 * @param valor Avaliação inicial.
 */
Avaliacao::Avaliacao(int valor) {
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Define o valor da avaliação.
 * @param valor Nova avaliação.
 */
void Avaliacao::setValor(int valor) {
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Obtém o valor da avaliação.
 * @return Valor da avaliação.
 */
int Avaliacao::getValor() const {
    return valor;
}