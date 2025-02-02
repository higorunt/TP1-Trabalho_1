#ifndef SERVICO_ATIVIDADE_HPP
#define SERVICO_ATIVIDADE_HPP

#include "../entidades/Atividade.hpp"
#include "../repositorios/RepositorioAtividade.hpp"

class ServicoAtividade
{
private:
    RepositorioAtividade repositorio;

public:
    ServicoAtividade(const std::string &caminhoBD);

    bool criarAtividade(const Atividade &atividade);
    Atividade *lerAtividade(const Codigo &codigo);
    bool atualizarAtividade(const Atividade &atividade);
    bool excluirAtividade(const Codigo &codigo);
    std::vector<Atividade> listarAtividades(const Codigo &destinoCodigo);
};

#endif // SERVICO_ATIVIDADE_HPP