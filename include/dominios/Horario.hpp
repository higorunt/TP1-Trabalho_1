// 221006404

#ifndef HORARIO_HPP
#define HORARIO_HPP

#include <string>
#include <stdexcept>
#include <regex>

/**
 * @class Horario
 * @brief Classe que representa o domínio Horario.
 *
 * Esta classe valida e armazena um horário no formato HH:MM.
 */
class Horario
{
private:
    std::string horario;
    void validar(std::string horario);

public:
    /**
     * @brief Define o valor do horário após validação.
     * @param horario Horário a ser atribuído.
     * @throw std::invalid_argument Se o horário for inválido.
     */
    void setValor(std::string horario);

    /**
     * @brief Retorna o valor do horário.
     * @return Horário armazenado.
     */
    std::string getValor() const;
    explicit Horario(const std::string &horario);
};

#endif // HORARIO_HPP
