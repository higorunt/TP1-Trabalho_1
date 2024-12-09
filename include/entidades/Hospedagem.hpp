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
 * A classe cont�m informa��es sobre uma hospedagem, incluindo seu nome, c�digo, avalia��o e valor da di�ria.
 */
class Hospedagem
{
private:
    Nome nome;           ///< Nome da hospedagem.
    Codigo codigo;       ///< C�digo identificador �nico da hospedagem.
    Avaliacao avaliacao; ///< Avalia��o atribu�da � hospedagem.
    Dinheiro diaria;     ///< Valor da di�ria da hospedagem.

public:
    /**
     * @brief Construtor da classe Hospedagem.
     *
     * Inicializa a hospedagem com os valores fornecidos para nome, c�digo, avalia��o e valor da di�ria.
     *
     * @param nome Nome da hospedagem.
     * @param codigo C�digo identificador �nico da hospedagem.
     * @param avaliacao Avalia��o atribu�da � hospedagem.
     * @param diaria Valor da di�ria da hospedagem.
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
     * @brief Define o c�digo da hospedagem.
     *
     * @param codigo Novo c�digo da hospedagem.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o c�digo da hospedagem.
     *
     * @return C�digo da hospedagem.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avalia��o da hospedagem.
     *
     * @param avaliacao Nova avalia��o da hospedagem.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avalia��o da hospedagem.
     *
     * @return Avalia��o da hospedagem.
     */
    Avaliacao getAvaliacao() const { return avaliacao; }

    /**
     * @brief Define o valor da di�ria da hospedagem.
     *
     * @param diaria Novo valor da di�ria.
     */
    void setDiaria(const Dinheiro &diaria) { this->diaria = diaria; }

    /**
     * @brief Retorna o valor da di�ria da hospedagem.
     *
     * @return Valor da di�ria da hospedagem.
     */
    Dinheiro getDiaria() const { return diaria; }
};

#endif // HOSPEDAGEM_HPP
