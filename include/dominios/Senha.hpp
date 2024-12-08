#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>
#include <stdexcept>

/**
 * @class Senha
 * @brief Classe que representa o dom�nio Senha.
 *
 * Esta classe valida e armazena uma senha de cinco d�gitos.
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
     * @param valor Senha a ser atribu�da.
     * @throw std::invalid_argument Se a senha for inv�lida.
     */
    explicit Senha(const std::string &valor);

    /**
     * @brief Define o valor da senha ap�s valida��o.
     * @param valor Senha a ser atribu�da.
     * @throw std::invalid_argument Se a senha for inv�lida.
     */
    void setValor(const std::string &valor);

    /**
     * @brief Retorna o valor da senha.
     * @return Senha armazenada.
     */
    std::string getValor() const;
};

#endif // SENHA_H