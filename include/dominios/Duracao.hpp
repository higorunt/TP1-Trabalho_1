//221006404


#ifndef DURACAO_HPP
#define DURACAO_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa a duração em dias.
 *
 * A duração deve estar entre 0 e 360 dias.
 */
class Duracao
{
private:
    int valor; ///< Valor da duração em dias.

    /**
     * @brief Valida o valor da duração.
     *
     * @param valor Valor a ser validado.
     * @throw std::invalid_argument Se o valor não estiver entre 0 e 360.
     */
    void validar(int valor);

public:
    /**
     * @brief Construtor da classe Duracao.
     *
     * @param valor Valor inicial da duração.
     */
    Duracao(int valor);

    /**
     * @brief Obtém o valor da duração.
     *
     * @return int Valor da duração em dias.
     */
    int getValor() const;

    /**
     * @brief Define o valor da duração.
     *
     * @param valor Novo valor da duração.
     */
    void setValor(int valor);
};

#endif // DURACAO_HPP
