//221006404

#ifndef SERVICO_ATIVIDADE_HPP
#define SERVICO_ATIVIDADE_HPP

#include "../repositorios/RepositorioAtividade.hpp"
#include "../servicos/ServicoDestino.hpp"
#include <vector>
#include <ctime>

/**
 * @brief Classe que gerencia as regras de neg�cio relacionadas a Atividades.
 */
class ServicoAtividade {
public:
    /**
     * @brief Construtor do servi�o de atividades.
     * @param rep Reposit�rio de atividades.
     * @param srvDestino Servi�o de destinos para valida��es.
     */
    ServicoAtividade(RepositorioAtividade* rep, ServicoDestino* srvDestino); // Removida a implementa��o inline

    /**
     * @brief Cria uma nova atividade ap�s valida��es.
     * @param atividade Atividade a ser criada.
     * @return true se criada com sucesso.
     */
    bool criarAtividade(const Atividade& atividade);

    Atividade* buscarAtividade(const Codigo& codigo);
    bool atualizarAtividade(const Atividade& atividade);
    bool excluirAtividade(const Codigo& codigo);
    std::vector<Atividade> listarPorDestino(const Codigo& codigoDestino);

private:
    RepositorioAtividade* repositorioAtividade;
    ServicoDestino* servicoDestino;  // Adicionado para acessar dados do destino

    /**
     * @brief Valida se a data da atividade est� dentro do per�odo do destino.
     */
    bool validarDataAtividade(const Data& dataAtividade, const Codigo& codigoDestino);

    time_t converterParaTime(const Data& data);
    bool validarHorarioAtividade(const Horario& horario, const Duracao& duracao, 
                                const Data& data, const Codigo& codigoDestino,
                                const Codigo& codigoAtividade = Codigo("000000"));
    time_t converterHorarioParaMinutos(const Horario& horario);
};

#endif
