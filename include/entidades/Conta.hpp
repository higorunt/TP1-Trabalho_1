//221006440

#ifndef CONTA_HPP
#define CONTA_HPP

#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

/**
 * @brief Classe que representa uma Conta.
 *
 * A classe contém informações básicas de uma conta, como o código identificador único e a senha associada.
 */
class Conta
{
private:
    Codigo codigo; ///< Código identificador único da conta.
    Senha senha;   ///< Senha para autenticação.

public:
    /**
     * @brief Construtor da classe Conta.
     *
     * Inicializa a conta com os valores fornecidos para o código e a senha.
     *
     * @param codigo Código único da conta.
     * @param senha Senha associada à conta.
     */
    Conta(const Codigo &codigo, const Senha &senha) : codigo(codigo), senha(senha) {}

    /**
     * @brief Define o código da conta.
     *
     * @param codigo Novo código da conta.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o código da conta.
     *
     * @return Código da conta.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a senha da conta.
     *
     * @param senha Nova senha da conta.
     */
    void setSenha(const Senha &senha) { this->senha = senha; }

    /**
     * @brief Retorna a senha da conta.
     *
     * @return Senha da conta.
     */
    Senha getSenha() const { return senha; }
};

#endif // CONTA_HPP
