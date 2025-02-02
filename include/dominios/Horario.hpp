// 221006404

#ifndef HORARIO_HPP
#define HORARIO_HPP

#include <string>
#include <stdexcept>
#include <regex>

/**
 * @class Horario
 * @brief Classe que representa o dom�nio Horario.
 *
 * Esta classe valida e armazena um hor�rio no formato HH:MM.
 */
class Horario
{
private:
    std::string horario;
    void validar(std::string horario);

public:
    /**
     * @brief Define o valor do hor�rio ap�s valida��o.
     * @param horario Hor�rio a ser atribu�do.
     * @throw std::invalid_argument Se o hor�rio for inv�lido.
     */
    void setValor(std::string horario);

    /**
     * @brief Retorna o valor do hor�rio.
     * @return Hor�rio armazenado.
     */
    std::string getValor() const;
    explicit Horario(const std::string &horario);
};

#endif // HORARIO_HPP
