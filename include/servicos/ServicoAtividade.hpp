#ifndef SERVICO_ATIVIDADE_HPP
#define SERVICO_ATIVIDADE_HPP

#include "../repositorios/RepositorioAtividade.hpp"
#include "../servicos/ServicoDestino.hpp"
#include <vector>
#include <ctime>

class ServicoAtividade {
public:
    ServicoAtividade(RepositorioAtividade* rep, ServicoDestino* srvDestino); // Removida a implementação inline
    bool criarAtividade(const Atividade& atividade);
    Atividade* buscarAtividade(const Codigo& codigo);
    bool atualizarAtividade(const Atividade& atividade);
    bool excluirAtividade(const Codigo& codigo);
    std::vector<Atividade> listarPorDestino(const Codigo& codigoDestino);

private:
    RepositorioAtividade* repositorioAtividade;
    ServicoDestino* servicoDestino;  // Adicionado para acessar dados do destino
    
    bool validarDataAtividade(const Data& dataAtividade, const Codigo& codigoDestino);
    time_t converterParaTime(const Data& data);
};

#endif
