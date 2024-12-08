#ifndef HOSPEDAGEM_HPP
#define HOSPEDAGEM_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../dominios/dinheiro.hpp"

class Hospedagem
{
private:
    Nome nome;
    Codigo codigo;
    Avaliacao avaliacao;
    Dinheiro diaria;

public:
    Hospedagem(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao, const Dinheiro &diaria)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), diaria(diaria) {}

    void setNome(const Nome &nome) { this->nome = nome; }
    Nome getNome() const { return nome; }

    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }
    Codigo getCodigo() const { return codigo; }

    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }
    Avaliacao getAvaliacao() const { return avaliacao; }

    void setDiaria(const Dinheiro &diaria) { this->diaria = diaria; }
    Dinheiro getDiaria() const { return diaria; }
};

#endif