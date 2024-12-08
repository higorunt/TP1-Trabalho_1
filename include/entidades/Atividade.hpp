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
 * Cont�m informa��es como nome, c�digo, avalia��o, data, hor�rio, dura��o e pre�o da atividade.
 */
class Atividade
{
private:
    Nome nome;           ///< Nome da atividade.
    Codigo codigo;       ///< C�digo identificador da atividade.
    Avaliacao avaliacao; ///< Avalia��o da atividade.
    Data data;           ///< Data em que a atividade ocorre.
    Horario horario;     ///< Hor�rio da atividade.
    Duracao duracao;     ///< Dura��o da atividade em minutos.
    Dinheiro preco;      ///< Pre�o da atividade.

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
     */
    Atividade(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao,
              const Data &data, const Horario &horario, const Duracao &duracao, const Dinheiro &preco)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), data(data), horario(horario), duracao(duracao), preco(preco) {}

    /**
     * @brief Define o nome da atividade.
     *
     * @param nome Nome da atividade.
     */
    void setNome(const Nome &nome) { this->nome = nome; }

    /**
     * @brief Retorna o nome da atividade.
     *
     * @return Nome da atividade.
     */
    Nome getNome() const { return nome; }

    /**
     * @brief Define o c�digo da atividade.
     *
     * @param codigo C�digo identificador da atividade.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o c�digo da atividade.
     *
     * @return C�digo identificador da atividade.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avalia��o da atividade.
     *
     * @param avaliacao Avalia��o da atividade.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avalia��o da atividade.
     *
     * @return Avalia��o da atividade.
     */
    Avaliacao getAvaliacao() const { return avaliacao; }

    /**
     * @brief Define a data da atividade.
     *
     * @param data Data da atividade.
     */
    void setData(const Data &data) { this->data = data; }

    /**
     * @brief Retorna a data da atividade.
     *
     * @return Data da atividade.
     */
    Data getData() const { return data; }

    /**
     * @brief Define o hor�rio da atividade.
     *
     * @param horario Hor�rio da atividade.
     */
    void setHorario(const Horario &horario) { this->horario = horario; }

    /**
     * @brief Retorna o hor�rio da atividade.
     *
     * @return Hor�rio da atividade.
     */
    Horario getHorario() const { return horario; }

    /**
     * @brief Define a dura��o da atividade.
     *
     * @param duracao Dura��o da atividade.
     */
    void setDuracao(const Duracao &duracao) { this->duracao = duracao; }

    /**
     * @brief Retorna a dura��o da atividade.
     *
     * @return Dura��o da atividade.
     */
    Duracao getDuracao() const { return duracao; }

    /**
     * @brief Define o pre�o da atividade.
     *
     * @param preco Pre�o da atividade.
     */
    void setPreco(const Dinheiro &preco) { this->preco = preco; }

    /**
     * @brief Retorna o pre�o da atividade.
     *
     * @return Pre�o da atividade.
     */
    Dinheiro getPreco() const { return preco; }
};

#endif
