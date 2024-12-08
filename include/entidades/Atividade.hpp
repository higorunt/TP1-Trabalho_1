#ifndef ATIVIDADE_HPP
#define ATIVIDADE_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/data.hpp"
#include "../dominios/horario.hpp"
#include "../dominios/duracao.hpp"
#include "../dominios/dinheiro.hpp"
#include "../dominios/codigo.hpp"

class Atividade
{
private:
    Nome nome;
    Codigo codigo;
    Avaliacao avaliacao;
    Data data;
    Horario horario;
    Duracao duracao;
    Dinheiro preco;

public:
    Atividade(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao,
              const Data &data, const Horario &horario, const Duracao &duracao, const Dinheiro &preco)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), data(data), horario(horario), duracao(duracao), preco(preco) {}

    void setNome(const Nome &nome) { this->nome = nome; }
    Nome getNome() const { return nome; }

    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }
    Codigo getCodigo() const { return codigo; }

    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }
    Avaliacao getAvaliacao() const { return avaliacao; }

    void setData(const Data &data) { this->data = data; }
    Data getData() const { return data; }

    void setHorario(const Horario &horario) { this->horario = horario; }
    Horario getHorario() const { return horario; }

    void setDuracao(const Duracao &duracao) { this->duracao = duracao; }
    Duracao getDuracao() const { return duracao; }

    void setPreco(const Dinheiro &preco) { this->preco = preco; }
    Dinheiro getPreco() const { return preco; }
};

#endif