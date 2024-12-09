//221006440

#ifndef CODIGO_HPP
#define CODIGO_HPP

#include <string>
#include <stdexcept>
#include <regex>

/**
 * @class Codigo
 * @brief Classe que representa o dom�nio C�digo.
 *
 * Esta classe valida e armazena um identificador �nico de 6 caracteres alfanum�ricos.
 */
class Codigo
{
private:
    std::string valor;                      ///< Armazena o c�digo validado.
    static const int TAMANHO = 6;           ///< Comprimento fixo do c�digo.
    void validar(const std::string &valor); ///< M�todo para validar o c�digo.

public:
    /**
     * @brief Construtor que inicializa e valida o c�digo.
     * @param valor C�digo a ser atribu�do.
     * @throw std::invalid_argument Se o c�digo for inv�lido.
     */
    explicit Codigo(const std::string &valor);

    /**
     * @brief Define o valor do c�digo ap�s valida��o.
     * @param valor C�digo a ser atribu�do.
     * @throw std::invalid_argument Se o c�digo for inv�lido.
     */
    void setValor(const std::string &valor);

    /**
     * @brief Retorna o valor do c�digo.
     * @return C�digo armazenado.
     */
    std::string getValor() const;
};

#endif // CODIGO_HPP
