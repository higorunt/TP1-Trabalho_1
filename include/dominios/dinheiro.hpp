//221006440


#ifndef DINHEIRO_HPP
#define DINHEIRO_HPP

#include <stdexcept>
#include <string>
#include <iomanip>
#include <sstream>

/**
 * @class Dinheiro
 * @brief Classe que representa o domínio Dinheiro.
 *
 * Esta classe valida e armazena valores monetários entre 0,00 e 200.000,00.
 */
class Dinheiro
{
private:
    double valor;                     ///< Valor monetário armazenado.
    static const double VALOR_MINIMO; ///< Valor mínimo permitido (0.00).
    static const double VALOR_MAXIMO; ///< Valor máximo permitido (200,000.00).
    void validar(double valor);       ///< Método para validar o valor monetário.

public:
    /**
     * @brief Construtor que inicializa e valida o valor monetário.
     * @param valor Valor a ser atribuído.
     * @throw std::invalid_argument Se o valor for inválido.
     */
    explicit Dinheiro(double valor);

    /**
     * @brief Define o valor monetário após validação.
     * @param valor Valor a ser atribuído.
     * @throw std::invalid_argument Se o valor for inválido.
     */
    void setValor(double valor);

    /**
     * @brief Retorna o valor monetário formatado.
     * @return Valor monetário armazenado como string no formato 0,00.
     */
    std::string getValor() const;
};

#endif // DINHEIRO_HPP
