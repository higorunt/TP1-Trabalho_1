#include "servicos/ServicoAtividade.hpp"

ServicoAtividade::ServicoAtividade(const std::string &caminhoBD)
    : repositorio(caminhoBD) {}

bool ServicoAtividade::criarAtividade(const Atividade &atividade)
{
    return repositorio.criarAtividade(atividade);
}

Atividade *ServicoAtividade::lerAtividade(const Codigo &codigo)
{
    return repositorio.lerAtividade(codigo);
}

bool ServicoAtividade::atualizarAtividade(const Atividade &atividade)
{
    return repositorio.atualizarAtividade(atividade);
}

bool ServicoAtividade::excluirAtividade(const Codigo &codigo)
{
    return repositorio.excluirAtividade(codigo);
}

std::vector<Atividade> ServicoAtividade::listarAtividades(const Codigo &destinoCodigo)
{
    return repositorio.listarAtividades(destinoCodigo);
}