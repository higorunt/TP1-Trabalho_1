//221006440

#ifndef AVALIACAO_H
#define AVALIACAO_H

#include <stdexcept>

/**
 * @class Avaliacao
 * @brief Classe que representa o domínio Avaliação.
 *
 * Esta classe valida e armazena uma avaliação em uma escala de 1 a 5.
 */
class Avaliacao
{
private:
    int valor;               ///< Valor da avaliação (entre 1 e 5).
    void validar(int valor); ///< Método para validar o valor da avaliação.

public:
    /**
     * @brief Construtor que inicializa e valida a avaliação.
     * @param valor Avaliação a ser atribuída.
     * @throw std::invalid_argument Se a avaliação for inválida.
     */
    explicit Avaliacao(int valor);

    /**
     * @brief Define o valor da avaliação após validação.
     * @param valor Avaliação a ser atribuída.
     * @throw std::invalid_argument Se a avaliação for inválida.
     */
    void setValor(int valor);

    /**
     * @brief Retorna o valor da avaliação.
     * @return Avaliação armazenada.
     */
    int getValor() const;
};

#endif // AVALIACAO_H
