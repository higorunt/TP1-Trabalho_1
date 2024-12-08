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
 * Contém informações como nome, código, avaliação, data, horário, duração e preço da atividade.
 */
class Atividade
{
private:
    Nome nome;           ///< Nome da atividade.
    Codigo codigo;       ///< Código identificador da atividade.
    Avaliacao avaliacao; ///< Avaliação da atividade.
    Data data;           ///< Data em que a atividade ocorre.
    Horario horario;     ///< Horário da atividade.
    Duracao duracao;     ///< Duração da atividade em minutos.
    Dinheiro preco;      ///< Preço da atividade.

public:
    /**
     * @brief Construtor da classe Atividade.
     *
     * Inicializa uma nova atividade com os valores fornecidos.
     *
     * @param nome Nome da atividade.
     * @param codigo Código identificador da atividade.
     * @param avaliacao Avaliação da atividade.
     * @param data Data da atividade.
     * @param horario Horário da atividade.
     * @param duracao Duração da atividade.
     * @param preco Preço da atividade.
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
     * @brief Define o código da atividade.
     *
     * @param codigo Código identificador da atividade.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o código da atividade.
     *
     * @return Código identificador da atividade.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avaliação da atividade.
     *
     * @param avaliacao Avaliação da atividade.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avaliação da atividade.
     *
     * @return Avaliação da atividade.
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
     * @brief Define o horário da atividade.
     *
     * @param horario Horário da atividade.
     */
    void setHorario(const Horario &horario) { this->horario = horario; }

    /**
     * @brief Retorna o horário da atividade.
     *
     * @return Horário da atividade.
     */
    Horario getHorario() const { return horario; }

    /**
     * @brief Define a duração da atividade.
     *
     * @param duracao Duração da atividade.
     */
    void setDuracao(const Duracao &duracao) { this->duracao = duracao; }

    /**
     * @brief Retorna a duração da atividade.
     *
     * @return Duração da atividade.
     */
    Duracao getDuracao() const { return duracao; }

    /**
     * @brief Define o preço da atividade.
     *
     * @param preco Preço da atividade.
     */
    void setPreco(const Dinheiro &preco) { this->preco = preco; }

    /**
     * @brief Retorna o preço da atividade.
     *
     * @return Preço da atividade.
     */
    Dinheiro getPreco() const { return preco; }
};

#endif
