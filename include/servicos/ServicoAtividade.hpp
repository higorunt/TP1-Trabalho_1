#ifndef SERVICO_ATIVIDADE_HPP
#define SERVICO_ATIVIDADE_HPP

#include "../repositorios/RepositorioAtividade.hpp"
#include <vector>

class ServicoAtividade {
public:
    ServicoAtividade(RepositorioAtividade* rep);
    bool criarAtividade(const Atividade& atividade);
    Atividade* buscarAtividade(const Codigo& codigo);
    bool atualizarAtividade(const Atividade& atividade);
    bool excluirAtividade(const Codigo& codigo);
    std::vector<Atividade> listarPorDestino(const Codigo& codigoDestino);

private:
    RepositorioAtividade* repositorioAtividade;
};

#endif
