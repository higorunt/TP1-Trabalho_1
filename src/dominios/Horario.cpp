#include "../../include/dominios/Horario.hpp"

/**
 * @brief Valida o formato e o valor do hor�rio.
 *
 * O hor�rio deve estar no formato HH:MM, onde:
 * - HH � um valor entre 00 e 23 (horas).
 * - MM � um valor entre 00 e 59 (minutos).
 *
 * @param horario String que representa o hor�rio a ser validado.
 * @throw std::invalid_argument Se o formato ou o valor do hor�rio for inv�lido.
 */
void Horario::validar(std::string horario)
{
    if (horario.size() != 5 || horario[2] != ':')
    {
        throw std::invalid_argument("Horario invalido");
    }
    int horas = std::stoi(horario.substr(0, 2));
    int minutos = std::stoi(horario.substr(3, 2));
    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59)
    {
        throw std::invalid_argument("Horario invalido");
    }
}

/**
 * @brief Define o valor do hor�rio.
 *
 * Valida o hor�rio antes de atribu�-lo ao atributo interno.
 *
 * @param horario String que representa o hor�rio no formato HH:MM.
 * @throw std::invalid_argument Se o formato ou o valor do hor�rio for inv�lido.
 */
void Horario::setValor(std::string horario)
{
    validar(horario);
    this->horario = horario;
}

/**
 * @brief Retorna o valor do hor�rio armazenado.
 *
 * @return String que representa o hor�rio no formato HH:MM.
 */
std::string Horario::getValor() const
{
    return horario;
}

Horario::Horario(const std::string &horario)
{
    setValor(horario);
}