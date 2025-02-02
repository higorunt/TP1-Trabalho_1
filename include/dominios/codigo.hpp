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
    std::string valor; ///< Armazena o c�digo validado.
public:
    explicit Codigo(const std::string &valor);
    std::string getValor() const;
};

#endif // CODIGO_HPP