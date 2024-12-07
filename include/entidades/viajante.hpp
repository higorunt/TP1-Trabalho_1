#ifndef VIAJANTE_HPP
#define VIAJANTE_HPP

#include "../dominios/Nome.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

class Viajante
{
private:
    Nome nome;
    Codigo codigo;
    Senha senha;

public:
    Viajante(const Nome &nome, const Codigo &codigo, const Senha &senha)
        : nome(nome), codigo(codigo), senha(senha) {}

    void setNome(const Nome &nome) { this->nome = nome; }
    Nome getNome() const { return nome; }

    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }
    Codigo getCodigo() const { return codigo; }

    void setSenha(const Senha &senha) { this->senha = senha; }
    Senha getSenha() const { return senha; }
};

#endif // VIAJANTE_HPP