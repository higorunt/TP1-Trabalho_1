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
    std::string valor; ///< Armazena o código validado.
public:
    explicit Codigo(const std::string &valor);
    std::string getValor() const;
};

#endif // CODIGO_HPP