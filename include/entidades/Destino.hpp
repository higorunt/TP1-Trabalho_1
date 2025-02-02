#ifndef DESTINO_HPP
#define DESTINO_HPP

#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"
#include "../dominios/Data.hpp"
#include "../dominios/Avaliacao.hpp"

/**
 * @brief Classe que representa um Destino.
 *
 * Um Destino possui um código próprio, nome, data de início, data de fim, avaliação e
 * o código da viagem à qual está associado (foreign key).
 */
class Destino {
private:
    Codigo codigo;            ///< Código único do destino.
    Nome nome;                ///< Nome do destino.
    Data dataInicio;          ///< Data de início.
    Data dataFim;             ///< Data de fim.
    Avaliacao avaliacao;      ///< Avaliação do destino.
    Codigo codigoViagem;      ///< Código da viagem associada.

public:
    /**
     * @brief Construtor da classe Destino.
     * @param codigo Código do destino.
     * @param nome Nome do destino.
     * @param dataInicio Data de início.
     * @param dataFim Data de fim.
     * @param avaliacao Avaliação.
     * @param codigoViagem Código da viagem associada.
     */
    Destino(const Codigo& codigo, const Nome& nome, const Data& dataInicio, const Data& dataFim, const Avaliacao& avaliacao, const Codigo& codigoViagem)
        : codigo(codigo), nome(nome), dataInicio(dataInicio), dataFim(dataFim), avaliacao(avaliacao), codigoViagem(codigoViagem) { }

    // Getters
    Codigo getCodigo() const { return codigo; }
    Nome getNome() const { return nome; }
    Data getDataInicio() const { return dataInicio; }
    Data getDataFim() const { return dataFim; }
    Avaliacao getAvaliacao() const { return avaliacao; }
    Codigo getCodigoViagem() const { return codigoViagem; }

    // Setters (opcional, se necessário)
    void setCodigo(const Codigo& cod) { codigo = cod; }
    void setNome(const Nome& nm) { nome = nm; }
    void setDataInicio(const Data& dtIni) { dataInicio = dtIni; }
    void setDataFim(const Data& dtFim) { dataFim = dtFim; }
    void setAvaliacao(const Avaliacao& av) { avaliacao = av; }
    void setCodigoViagem(const Codigo& codViag) { codigoViagem = codViag; }
};

#endif // DESTINO_HPP
