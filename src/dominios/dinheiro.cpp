#include "../../include/dominios/dinheiro.hpp"

const double Dinheiro::VALOR_MINIMO = 0.00;      ///< Valor m�nimo permitido.
const double Dinheiro::VALOR_MAXIMO = 200000.00; ///< Valor m�ximo permitido.

/**
 * @brief M�todo para validar o valor monet�rio.
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
 * @brief Construtor que inicializa e valida o valor monet�rio.
 * @param valor Valor inicial a ser atribu�do.
 */
Dinheiro::Dinheiro(double valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Define o valor monet�rio ap�s valida��o.
 * @param valor Valor a ser atribu�do.
 */
void Dinheiro::setValor(double valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor monet�rio formatado.
 * @return Valor armazenado como string no formato 0,00.
 */
std::string Dinheiro::getValor() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << valor;
    return oss.str();
}
