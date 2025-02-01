//221006404


#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../entidades/Conta.hpp"
#include "../dominios/dinheiro.hpp"

/**
 * @brief Classe que representa uma Viagem.
 *
 * A classe contém informações sobre uma viagem, incluindo seu nome, código, avaliação e conta associada.
 */
class Viagem
{
private:
    Nome nome;           ///< Nome da viagem.
    Codigo codigo;       ///< Código identificador único da viagem.
    Avaliacao avaliacao; ///< Avaliação atribuída à viagem.
    Conta conta;         ///< Conta associada à viagem.
    Dinheiro custoTotal;  // Para facilitar o cálculo do custo total
    std::vector<Codigo> destinosCodigos; // Para rastrear destinos associados

public:
    /**
     * @brief Construtor da classe Viagem.
     *
     * Inicializa a viagem com os valores fornecidos para nome, código, avaliação e conta.
     *
     * @param nome Nome da viagem.
     * @param codigo Código identificador único da viagem.
     * @param avaliacao Avaliação atribuída à viagem.
     */
    Viagem(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao, const Conta &conta)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), conta(conta), custoTotal(0) {}

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
     * @brief Define o código da viagem.
     *
     * @param codigo Novo código da viagem.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o código da viagem.
     *
     * @return Código da viagem.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avaliação da viagem.
     *
     * @param avaliacao Nova avaliação da viagem.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avaliação da viagem.
     *
     * @return Avaliação da viagem.
     */
    Avaliacao getAvaliacao() const { return avaliacao; }

    /**
     * @brief Define a conta associada à viagem.
     *
     * @param conta Nova conta associada à viagem.
     */
    void setConta(const Conta &conta) { this->conta = conta; }

    /**
     * @brief Retorna a conta associada à viagem.
     *
     * @return Conta associada à viagem.
     */
    Conta getConta() const { return conta; }

    /**
     * @brief Adiciona um destino à viagem.
     *
     * @param codigoDestino Código do destino a ser adicionado.
     */
    void adicionarDestino(const Codigo& codigoDestino);

    /**
     * @brief Remove um destino da viagem.
     *
     * @param codigoDestino Código do destino a ser removido.
     */
    void removerDestino(const Codigo& codigoDestino);

    /**
     * @brief Verifica se a viagem possui destinos.
     *
     * @return true se a viagem tem destinos associados, false caso contrário.
     */
    bool possuiDestinos() const { return !destinosCodigos.empty(); }
};

#endif // VIAGEM_HPP
