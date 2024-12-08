#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../entidades/codigo.hpp"

class Viagem
{
private:
    Nome nome;
    Codigo codigo;
    Avaliacao avaliacao;
    Conta conta;

public:
    Viagem(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao)
        : nome(nome), codigo(codigo), avaliacao(avaliacao) {}

    void setNome(const Nome &nome) { this->nome = nome; }
    Nome getNome() const { return nome; }

    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }
    Codigo getCodigo() const { return codigo; }

    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }
    Avaliacao getAvaliacao() const { return avaliacao; }

    void setConta(const Conta &conta) { this->conta = conta; }
    Conta getConta() const { return conta; }
};

#endif