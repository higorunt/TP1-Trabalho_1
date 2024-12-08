#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>
#include <stdexcept>

/**
 * @class Senha
 * @brief Classe que representa o domínio Senha.
 *
 * Esta classe valida e armazena uma senha de cinco dígitos.
 */
class Senha
{
private:
    std::string valor;
    static const int TAMANHO = 5;
    void validar(const std::string &valor);

public:
    /**
     * @brief Construtor que inicializa e valida a senha.
     * @param valor Senha a ser atribuída.
     * @throw std::invalid_argument Se a senha for inválida.
     */
    explicit Senha(const std::string &valor);

    /**
     * @brief Define o valor da senha após validação.
     * @param valor Senha a ser atribuída.
     * @throw std::invalid_argument Se a senha for inválida.
     */
    void setValor(const std::string &valor);

    /**
     * @brief Retorna o valor da senha.
     * @return Senha armazenada.
     */
    std::string getValor() const;
};

#endif // SENHA_H