#ifndef DESTINO_HPP
#define DESTINO_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/data.hpp"
#include "../dominios/codigo.hpp"

class Destino
{
private:
    Nome nome;
    Codigo codigo;
    Avaliacao avaliacao;
    Data dataInicio;
    Data dataFim;

public:
    Destino(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao,
            const Data &dataInicio, const Data &dataFim)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), dataInicio(dataInicio), dataFim(dataFim) {}

    void setNome(const Nome &nome) { this->nome = nome; }
    Nome getNome() const { return nome; }

    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }
    Codigo getCodigo() const { return codigo; }

    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }
    Avaliacao getAvaliacao() const { return avaliacao; }

    void setDataInicio(const Data &dataInicio) { this->dataInicio = dataInicio; }
    Data getDataInicio() const { return dataInicio; }

    void setDataFim(const Data &dataFim) { this->dataFim = dataFim; }
    Data getDataFim() const { return dataFim; }
};

#endif