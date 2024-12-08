#ifndef CONTA_HPP
#define CONTA_HPP

#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

class Conta {
private:
    Codigo codigo;   ///< C�digo identificador �nico da conta.
    Senha senha;     ///< Senha para autentica��o.

public:
    /**
     * @param codigo C�digo �nico da conta.
     * @param senha Senha da conta.
     */
    Conta(const Codigo &codigo, const Senha &senha) : codigo(codigo), senha(senha) {}

    // M�todos para obter e modificar os atributos.
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }
    Codigo getCodigo() const { return codigo; }

    void setSenha(const Senha &senha) { this->senha = senha; }
    Senha getSenha() const { return senha; }
};

#endif // CONTA_HPP
