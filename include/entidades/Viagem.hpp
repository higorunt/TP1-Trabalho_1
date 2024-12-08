#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../entidades/Conta.hpp"

/**
 * @brief Classe que representa uma Viagem.
 *
 * A classe cont�m informa��es sobre uma viagem, incluindo seu nome, c�digo, avalia��o e conta associada.
 */
class Viagem
{
private:
    Nome nome;           ///< Nome da viagem.
    Codigo codigo;       ///< C�digo identificador �nico da viagem.
    Avaliacao avaliacao; ///< Avalia��o atribu�da � viagem.
    Conta conta;         ///< Conta associada � viagem.

public:
    /**
     * @brief Construtor da classe Viagem.
     *
     * Inicializa a viagem com os valores fornecidos para nome, c�digo, avalia��o e conta.
     *
     * @param nome Nome da viagem.
     * @param codigo C�digo identificador �nico da viagem.
     * @param avaliacao Avalia��o atribu�da � viagem.
     */
    Viagem(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao)
        : nome(nome), codigo(codigo), avaliacao(avaliacao) {}

    /**
     * @brief Define o nome da viagem.
     *
     * @param nome Novo nome da viagem.
     */
    void setNome(const Nome &nome) { this->nome = nome; }

    /**
     * @brief Retorna o nome da viagem.
     *
     * @return Nome da viagem.
     */
    Nome getNome() const { return nome; }

    /**
     * @brief Define o c�digo da viagem.
     *
     * @param codigo Novo c�digo da viagem.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o c�digo da viagem.
     *
     * @return C�digo da viagem.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avalia��o da viagem.
     *
     * @param avaliacao Nova avalia��o da viagem.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avalia��o da viagem.
     *
     * @return Avalia��o da viagem.
     */
    Avaliacao getAvaliacao() const { return avaliacao; }

    /**
     * @brief Define a conta associada � viagem.
     *
     * @param conta Nova conta associada � viagem.
     */
    void setConta(const Conta &conta) { this->conta = conta; }

    /**
     * @brief Retorna a conta associada � viagem.
     *
     * @return Conta associada � viagem.
     */
    Conta getConta() const { return conta; }
};

#endif // VIAGEM_HPP
