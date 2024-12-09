//221006440

#ifndef CONTA_HPP
#define CONTA_HPP

#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

/**
 * @brief Classe que representa uma Conta.
 *
 * A classe cont�m informa��es b�sicas de uma conta, como o c�digo identificador �nico e a senha associada.
 */
class Conta
{
private:
    Codigo codigo; ///< C�digo identificador �nico da conta.
    Senha senha;   ///< Senha para autentica��o.

public:
    /**
     * @brief Construtor da classe Conta.
     *
     * Inicializa a conta com os valores fornecidos para o c�digo e a senha.
     *
     * @param codigo C�digo �nico da conta.
     * @param senha Senha associada � conta.
     */
    Conta(const Codigo &codigo, const Senha &senha) : codigo(codigo), senha(senha) {}

    /**
     * @brief Define o c�digo da conta.
     *
     * @param codigo Novo c�digo da conta.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o c�digo da conta.
     *
     * @return C�digo da conta.
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
