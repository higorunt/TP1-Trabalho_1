//221006440

#ifndef AVALIACAO_H
#define AVALIACAO_H

#include <stdexcept>

/**
 * @class Avaliacao
 * @brief Classe que representa o dom�nio Avalia��o.
 *
 * Esta classe valida e armazena uma avalia��o em uma escala de 1 a 5.
 */
class Avaliacao
{
private:
    int valor;               ///< Valor da avalia��o (entre 1 e 5).
    void validar(int valor); ///< M�todo para validar o valor da avalia��o.

public:
    /**
     * @brief Construtor que inicializa e valida a avalia��o.
     * @param valor Avalia��o a ser atribu�da.
     * @throw std::invalid_argument Se a avalia��o for inv�lida.
     */
    explicit Avaliacao(int valor);

    /**
     * @brief Define o valor da avalia��o ap�s valida��o.
     * @param valor Avalia��o a ser atribu�da.
     * @throw std::invalid_argument Se a avalia��o for inv�lida.
     */
    void setValor(int valor);

    /**
     * @brief Retorna o valor da avalia��o.
     * @return Avalia��o armazenada.
     */
    int getValor() const;
};

#endif // AVALIACAO_H
