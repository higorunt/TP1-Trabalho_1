//221006404

#ifndef SERVICO_ATIVIDADE_HPP
#define SERVICO_ATIVIDADE_HPP

#include "../repositorios/RepositorioAtividade.hpp"
#include "../servicos/ServicoDestino.hpp"
#include <vector>
#include <ctime>

/**
 * @brief Classe que gerencia as regras de negócio relacionadas a Atividades.
 */
class ServicoAtividade {
public:
    /**
     * @brief Construtor do serviço de atividades.
     * @param rep Repositório de atividades.
     * @param srvDestino Serviço de destinos para validações.
     */
    ServicoAtividade(RepositorioAtividade* rep, ServicoDestino* srvDestino); // Removida a implementação inline

    /**
     * @brief Cria uma nova atividade após validações.
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
     * @brief Valida se a data da atividade está dentro do período do destino.
     */
    bool validarDataAtividade(const Data& dataAtividade, const Codigo& codigoDestino);

    time_t converterParaTime(const Data& data);
    bool validarHorarioAtividade(const Horario& horario, const Duracao& duracao, 
                                const Data& data, const Codigo& codigoDestino,
                                const Codigo& codigoAtividade = Codigo("000000"));
    time_t converterHorarioParaMinutos(const Horario& horario);
};

#endif
