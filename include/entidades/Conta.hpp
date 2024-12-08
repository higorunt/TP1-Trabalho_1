#ifndef CONTA_HPP
#define CONTA_HPP

#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

class Conta {
private:
    Codigo codigo;   ///< Código identificador único da conta.
    Senha senha;     ///< Senha para autenticação.

public:
    /**
     * @param codigo Código único da conta.
     * @param senha Senha da conta.
     */
    Conta(const Codigo &codigo, const Senha &senha) : codigo(codigo), senha(senha) {}

    // Métodos para obter e modificar os atributos.
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }
    Codigo getCodigo() const { return codigo; }

    void setSenha(const Senha &senha) { this->senha = senha; }
    Senha getSenha() const { return senha; }
};

#endif // CONTA_HPP
