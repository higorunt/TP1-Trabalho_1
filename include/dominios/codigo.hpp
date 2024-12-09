//221006440

#ifndef CODIGO_HPP
#define CODIGO_HPP

#include <string>
#include <stdexcept>
#include <regex>

/**
 * @class Codigo
 * @brief Classe que representa o domínio Código.
 *
 * Esta classe valida e armazena um identificador único de 6 caracteres alfanuméricos.
 */
class Codigo
{
private:
    std::string valor;                      ///< Armazena o código validado.
    static const int TAMANHO = 6;           ///< Comprimento fixo do código.
    void validar(const std::string &valor); ///< Método para validar o código.

public:
    /**
     * @brief Construtor que inicializa e valida o código.
     * @param valor Código a ser atribuído.
     * @throw std::invalid_argument Se o código for inválido.
     */
    explicit Codigo(const std::string &valor);

    /**
     * @brief Define o valor do código após validação.
     * @param valor Código a ser atribuído.
     * @throw std::invalid_argument Se o código for inválido.
     */
    void setValor(const std::string &valor);

    /**
     * @brief Retorna o valor do código.
     * @return Código armazenado.
     */
    std::string getValor() const;
};

#endif // CODIGO_HPP
