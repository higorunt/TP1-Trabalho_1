//221006440


#ifndef DINHEIRO_HPP
#define DINHEIRO_HPP

#include <stdexcept>
#include <string>
#include <iomanip>
#include <sstream>

/**
 * @class Dinheiro
 * @brief Classe que representa o dom�nio Dinheiro.
 *
 * Esta classe valida e armazena valores monet�rios entre 0,00 e 200.000,00.
 */
class Dinheiro
{
private:
    double valor;                     ///< Valor monet�rio armazenado.
    static const double VALOR_MINIMO; ///< Valor m�nimo permitido (0.00).
    static const double VALOR_MAXIMO; ///< Valor m�ximo permitido (200,000.00).
    void validar(double valor);       ///< M�todo para validar o valor monet�rio.

public:
    /**
     * @brief Construtor que inicializa e valida o valor monet�rio.
     * @param valor Valor a ser atribu�do.
     * @throw std::invalid_argument Se o valor for inv�lido.
     */
    explicit Dinheiro(double valor);

    /**
     * @brief Define o valor monet�rio ap�s valida��o.
     * @param valor Valor a ser atribu�do.
     * @throw std::invalid_argument Se o valor for inv�lido.
     */
    void setValor(double valor);

    /**
     * @brief Retorna o valor monet�rio formatado.
     * @return Valor monet�rio armazenado como string no formato 0,00.
     */
    std::string getValor() const;
};

#endif // DINHEIRO_HPP
