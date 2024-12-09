//221006404


#ifndef HOSPEDAGEM_HPP
#define HOSPEDAGEM_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../dominios/dinheiro.hpp"

/**
 * @brief Classe que representa uma Hospedagem.
 *
 * A classe contém informações sobre uma hospedagem, incluindo seu nome, código, avaliação e valor da diária.
 */
class Hospedagem
{
private:
    Nome nome;           ///< Nome da hospedagem.
    Codigo codigo;       ///< Código identificador único da hospedagem.
    Avaliacao avaliacao; ///< Avaliação atribuída à hospedagem.
    Dinheiro diaria;     ///< Valor da diária da hospedagem.

public:
    /**
     * @brief Construtor da classe Hospedagem.
     *
     * Inicializa a hospedagem com os valores fornecidos para nome, código, avaliação e valor da diária.
     *
     * @param nome Nome da hospedagem.
     * @param codigo Código identificador único da hospedagem.
     * @param avaliacao Avaliação atribuída à hospedagem.
     * @param diaria Valor da diária da hospedagem.
     */
    Hospedagem(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao, const Dinheiro &diaria)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), diaria(diaria) {}

    /**
     * @brief Define o nome da hospedagem.
     *
     * @param nome Novo nome da hospedagem.
     */
    void setNome(const Nome &nome) { this->nome = nome; }

    /**
     * @brief Retorna o nome da hospedagem.
     *
     * @return Nome da hospedagem.
     */
    Nome getNome() const { return nome; }

    /**
     * @brief Define o código da hospedagem.
     *
     * @param codigo Novo código da hospedagem.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o código da hospedagem.
     *
     * @return Código da hospedagem.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avaliação da hospedagem.
     *
     * @param avaliacao Nova avaliação da hospedagem.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avaliação da hospedagem.
     *
     * @return Avaliação da hospedagem.
     */
    Avaliacao getAvaliacao() const { return avaliacao; }

    /**
     * @brief Define o valor da diária da hospedagem.
     *
     * @param diaria Novo valor da diária.
     */
    void setDiaria(const Dinheiro &diaria) { this->diaria = diaria; }

    /**
     * @brief Retorna o valor da diária da hospedagem.
     *
     * @return Valor da diária da hospedagem.
     */
    Dinheiro getDiaria() const { return diaria; }
};

#endif // HOSPEDAGEM_HPP
