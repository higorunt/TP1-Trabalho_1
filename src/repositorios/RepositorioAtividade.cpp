#include "repositorios/RepositorioAtividade.hpp"

RepositorioAtividade::RepositorioAtividade(const std::string &caminhoBD)
{
    // Implementa��o do construtor
}

bool RepositorioAtividade::criarAtividade(const Atividade &atividade)
{
    // Implementa��o
    return true;
}

Atividade *RepositorioAtividade::lerAtividade(const Codigo &codigo)
{
    // Implementa��o
    return nullptr;
}

bool RepositorioAtividade::atualizarAtividade(const Atividade &atividade)
{
    // Implementa��o
    return true;
}

bool RepositorioAtividade::excluirAtividade(const Codigo &codigo)
{
    // Implementa��o
    return true;
}

std::vector<Atividade> RepositorioAtividade::listarAtividades(const Codigo &destinoCodigo)
{
    // Implementa��o
    return std::vector<Atividade>();
}