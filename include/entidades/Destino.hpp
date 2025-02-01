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
 * A classe contém informações sobre um destino, incluindo seu nome, código, avaliação e datas de início e fim.
 */
class Destino
{
private:
    Nome nome;           ///< Nome do destino.
    Codigo codigo;       ///< Código identificador único do destino.
    Avaliacao avaliacao; ///< Avaliação atribuída ao destino.
    Data dataInicio;     ///< Data de início do destino.
    Data dataFim;        ///< Data de término do destino.

    std::vector<Codigo> atividadesCodigos;
    std::vector<Codigo> hospedagensCodigos;

public:
    /**
     * @brief Construtor da classe Destino.
     *
     * Inicializa o destino com os valores fornecidos para nome, código, avaliação, data de início e data de término.
     *
     * @param nome Nome do destino.
     * @param codigo Código identificador único do destino.
     * @param avaliacao Avaliação atribuída ao destino.
     * @param dataInicio Data de início do destino.
     * @param dataFim Data de término do destino.
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
     * @brief Define o código do destino.
     *
     * @param codigo Novo código do destino.
     */
    void setCodigo(const Codigo &codigo) { this->codigo = codigo; }

    /**
     * @brief Retorna o código do destino.
     *
     * @return Código do destino.
     */
    Codigo getCodigo() const { return codigo; }

    /**
     * @brief Define a avaliação do destino.
     *
     * @param avaliacao Nova avaliação do destino.
     */
    void setAvaliacao(const Avaliacao &avaliacao) { this->avaliacao = avaliacao; }

    /**
     * @brief Retorna a avaliação do destino.
     *
     * @return Avaliação do destino.
     */
    Avaliacao getAvaliacao() const { return avaliacao; }

    /**
     * @brief Define a data de início do destino.
     *
     * @param dataInicio Nova data de início.
     */
    void setDataInicio(const Data &dataInicio) { this->dataInicio = dataInicio; }

    /**
     * @brief Retorna a data de início do destino.
     *
     * @return Data de início do destino.
     */
    Data getDataInicio() const { return dataInicio; }

    /**
     * @brief Define a data de término do destino.
     *
     * @param dataFim Nova data de término.
     */
    void setDataFim(const Data &dataFim) { this->dataFim = dataFim; }

    /**
     * @brief Retorna a data de término do destino.
     *
     * @return Data de término do destino.
     */
    Data getDataFim() const { return dataFim; }

    // Métodos para validação de datas de atividades
    bool validarDataAtividade(const Data& dataAtividade) const {
        // Verificar se a data está dentro do intervalo
        // Precisaríamos implementar operadores de comparação na classe Data
        return true; // Implementação temporária
    }

    // Métodos para gerenciamento de atividades e hospedagens
    void adicionarAtividade(const Codigo& codigoAtividade);
    void removerAtividade(const Codigo& codigoAtividade);
    bool possuiAtividadesOuHospedagens() const {
        return !atividadesCodigos.empty() || !hospedagensCodigos.empty();
    }
    Codigo codigoViagem{"000"};  // Referência à viagem inicializada com valor padrão

};

#endif // DESTINO_HPP
