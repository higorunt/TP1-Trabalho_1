#include "../../include/dominios/Duracao.hpp"

/**
 * @brief Valida o valor da duração.
 *
 * @param valor Valor da duração a ser validado.
 * @throw std::invalid_argument Se o valor não estiver no intervalo permitido (0 a 360).
 */
void Duracao::validar(int valor)
{
    if (valor < 0 || valor > 360)
    {
        throw std::invalid_argument("Duracao invalida. Deve estar entre 0 e 360.");
    }
}

/**
 * @brief Construtor da classe Duracao.
 *
 * @param valor Valor inicial da duração.
 * @throw std::invalid_argument Se o valor fornecido não for válido.
 */
Duracao::Duracao(int valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor da duração.
 *
 * @return Valor da duração.
 */
int Duracao::getValor() const
{
    return valor;
}

/**
 * @brief Define um novo valor para a duração.
 *
 * @param valor Novo valor da duração.
 * @throw std::invalid_argument Se o valor fornecido não for válido.
 */
void Duracao::setValor(int valor)
{
    validar(valor);
    this->valor = valor;
}
