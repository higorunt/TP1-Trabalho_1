#include "repositorios/RepositorioAtividade.hpp"

RepositorioAtividade::RepositorioAtividade(const std::string &caminhoBD)
{
    // Implementação do construtor
}

bool RepositorioAtividade::criarAtividade(const Atividade &atividade)
{
    // Implementação
    return true;
}

Atividade *RepositorioAtividade::lerAtividade(const Codigo &codigo)
{
    // Implementação
    return nullptr;
}

bool RepositorioAtividade::atualizarAtividade(const Atividade &atividade)
{
    // Implementação
    return true;
}

bool RepositorioAtividade::excluirAtividade(const Codigo &codigo)
{
    // Implementação
    return true;
}

std::vector<Atividade> RepositorioAtividade::listarAtividades(const Codigo &destinoCodigo)
{
    // Implementação
    return std::vector<Atividade>();
}