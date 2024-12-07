#include "../../include/dominios/dinheiro.hpp"

const double Dinheiro::VALOR_MINIMO = 0.00;      ///< Valor mínimo permitido.
const double Dinheiro::VALOR_MAXIMO = 200000.00; ///< Valor máximo permitido.

/**
 * @brief Método para validar o valor monetário.
 * @param valor Valor a ser validado.
 * @throw std::invalid_argument Se o valor estiver fora do intervalo permitido.
 */
void Dinheiro::validar(double valor)
{
    if (valor < VALOR_MINIMO || valor > VALOR_MAXIMO)
    {
        throw std::invalid_argument("Valor invalido. Deve estar entre 0,00 e 200.000,00.");
    }
}

/**
 * @brief Construtor que inicializa e valida o valor monetário.
 * @param valor Valor inicial a ser atribuído.
 */
Dinheiro::Dinheiro(double valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Define o valor monetário após validação.
 * @param valor Valor a ser atribuído.
 */
void Dinheiro::setValor(double valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor monetário formatado.
 * @return Valor armazenado como string no formato 0,00.
 */
std::string Dinheiro::getValor() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << valor;
    return oss.str();
}
