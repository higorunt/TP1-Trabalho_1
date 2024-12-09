//221006404


#ifndef DURACAO_HPP
#define DURACAO_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa a dura��o em dias.
 *
 * A dura��o deve estar entre 0 e 360 dias.
 */
class Duracao
{
private:
    int valor; ///< Valor da dura��o em dias.

    /**
     * @brief Valida o valor da dura��o.
     *
     * @param valor Valor a ser validado.
     * @throw std::invalid_argument Se o valor n�o estiver entre 0 e 360.
     */
    void validar(int valor);

public:
    /**
     * @brief Construtor da classe Duracao.
     *
     * @param valor Valor inicial da dura��o.
     */
    Duracao(int valor);

    /**
     * @brief Obt�m o valor da dura��o.
     *
     * @return int Valor da dura��o em dias.
     */
    int getValor() const;

    /**
     * @brief Define o valor da dura��o.
     *
     * @param valor Novo valor da dura��o.
     */
    void setValor(int valor);
};

#endif // DURACAO_HPP
