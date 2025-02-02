// 221006440

#ifndef ATIVIDADE_HPP
#define ATIVIDADE_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/data.hpp"
#include "../dominios/horario.hpp"
#include "../dominios/duracao.hpp"
#include "../dominios/dinheiro.hpp"
#include "../dominios/codigo.hpp"

/**
 * @brief Classe que representa uma Atividade.
 *
 * Cont�m informa��es como nome, c�digo, avalia��o, data, hor�rio, dura��o, pre�o e destino da atividade.
 */
class Atividade
{
private:
    Nome nome;            ///< Nome da atividade.
    Codigo codigo;        ///< C�digo identificador da atividade.
    Avaliacao avaliacao;  ///< Avalia��o da atividade.
    Data data;            ///< Data em que a atividade ocorre.
    Horario horario;      ///< Hor�rio da atividade.
    Duracao duracao;      ///< Dura��o da atividade em minutos.
    Dinheiro preco;       ///< Pre�o da atividade.
    Codigo destinoCodigo; ///< C�digo do destino associado � atividade.

public:
    /**
     * @brief Construtor da classe Atividade.
     *
     * Inicializa uma nova atividade com os valores fornecidos.
     *
     * @param nome Nome da atividade.
     * @param codigo C�digo identificador da atividade.
     * @param avaliacao Avalia��o da atividade.
     * @param data Data da atividade.
     * @param horario Hor�rio da atividade.
     * @param duracao Dura��o da atividade.
     * @param preco Pre�o da atividade.
     * @param destinoCodigo C�digo do destino associado � atividade.
     */
    Atividade(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao,
              const Data &data, const Horario &horario, const Duracao &duracao,
              const Dinheiro &preco, const Codigo &destinoCodigo)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), data(data), horario(horario),
          duracao(duracao), preco(preco), destinoCodigo(destinoCodigo) {}

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

    void setDestinoCodigo(const Codigo &destinoCodigo) { this->destinoCodigo = destinoCodigo; }
    Codigo getDestinoCodigo() const { return destinoCodigo; }
};

#endif
