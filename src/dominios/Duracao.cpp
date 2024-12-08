#include "../../include/dominios/Duracao.hpp"

/**
 * @brief Valida o valor da dura��o.
 *
 * @param valor Valor da dura��o a ser validado.
 * @throw std::invalid_argument Se o valor n�o estiver no intervalo permitido (0 a 360).
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
 * @param valor Valor inicial da dura��o.
 * @throw std::invalid_argument Se o valor fornecido n�o for v�lido.
 */
Duracao::Duracao(int valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor da dura��o.
 *
 * @return Valor da dura��o.
 */
int Duracao::getValor() const
{
    return valor;
}

/**
 * @brief Define um novo valor para a dura��o.
 *
 * @param valor Novo valor da dura��o.
 * @throw std::invalid_argument Se o valor fornecido n�o for v�lido.
 */
void Duracao::setValor(int valor)
{
    validar(valor);
    this->valor = valor;
}
