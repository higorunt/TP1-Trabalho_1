//221006404

#ifndef DESTINO_HPP
#define DESTINO_HPP

#include "../dominios/avaliacao.hpp"
#include "../dominios/nome.hpp"
#include "../dominios/data.hpp"
#include "../dominios/codigo.hpp"

/**
 * @brief Classe que representa um Destino.
 *
 * A classe cont�m informa��es sobre um destino, incluindo seu nome, c�digo, avalia��o e datas de in�cio e fim.
 */
class Destino
{
private:
    Nome nome;           ///< Nome do destino.
    Codigo codigo;       ///< C�digo identificador �nico do destino.
    Avaliacao avaliacao; ///< Avalia��o atribu�da ao destino.
    Data dataInicio;     ///< Data de in�cio do destino.
    Data dataFim;        ///< Data de t�rmino do destino.

    std::vector<Codigo> atividadesCodigos;
    std::vector<Codigo> hospedagensCodigos;

public:
    /**
     * @brief Construtor da classe Destino.
     *
     * Inicializa o destino com os valores fornecidos para nome, c�digo, avalia��o, data de in�cio e data de t�rmino.
     *
     * @param nome Nome do destino.
     * @param codigo C�digo identificador �nico do destino.
     * @param avaliacao Avalia��o atribu�da ao destino.
     * @param dataInicio Data de in�cio do destino.
     * @param dataFim Data de t�rmino do destino.
     */
    Destino(const Nome &nome, const Codigo &codigo, const Avaliacao &avaliacao,
            const Data &dataInicio, const Data &dataFim)
        : nome(nome), codigo(codigo), avaliacao(avaliacao), dataInicio(dataInicio), dataFim(dataFim) {}

    /**
     * @brief Define o nome do destino.
     *
     * @param nome Novo nome do destino.
     */
    void setNome(const Nome &nome) { this->nome = nome; }

    /**
     * @brief Retorna o nome do destino.
     *
     * @return Nome do destino.
     */
    Nome getNome() const { return nome; }

    /**
     * @brief Define o c�digo do destino.
     *
     * @param codigo Novo c�digo do destino.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o c�digo do destino.
     *
     * @return C�digo do destino.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avalia��o do destino.
     *
     * @param avaliacao Nova avalia��o do destino.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avalia��o do destino.
     *
     * @return Avalia��o do destino.
     */
    Avaliacao getAvaliacao() const { return avaliacao; }

    /**
     * @brief Define a data de in�cio do destino.
     *
     * @param dataInicio Nova data de in�cio.
     */
    void setDataInicio(const Data &dataInicio) { this->dataInicio = dataInicio; }

    /**
     * @brief Retorna a data de in�cio do destino.
     *
     * @return Data de in�cio do destino.
     */
    Data getDataInicio() const { return dataInicio; }

    /**
     * @brief Define a data de t�rmino do destino.
     *
     * @param dataFim Nova data de t�rmino.
     */
    void setDataFim(const Data &dataFim) { this->dataFim = dataFim; }

    /**
     * @brief Retorna a data de t�rmino do destino.
     *
     * @return Data de t�rmino do destino.
     */
    Data getDataFim() const { return dataFim; }

    // M�todos para valida��o de datas de atividades
    bool validarDataAtividade(const Data& dataAtividade) const {
        // Verificar se a data est� dentro do intervalo
        // Precisar�amos implementar operadores de compara��o na classe Data
        return true; // Implementa��o tempor�ria
    }

    // M�todos para gerenciamento de atividades e hospedagens
    void adicionarAtividade(const Codigo& codigoAtividade);
    void removerAtividade(const Codigo& codigoAtividade);
    bool possuiAtividadesOuHospedagens() const {
        return !atividadesCodigos.empty() || !hospedagensCodigos.empty();
    }
    Codigo codigoViagem{"000"};  // Refer�ncia � viagem inicializada com valor padr�o

};

#endif // DESTINO_HPP
