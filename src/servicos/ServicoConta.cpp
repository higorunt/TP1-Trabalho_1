#include "ServicoConta.hpp"

ServicoConta::ServicoConta(const std::string &caminhoBD)
    : repositorio(caminhoBD) {}

bool ServicoConta::criarConta(const Conta &conta)
{
    return repositorio.criarConta(conta);
}

Conta *ServicoConta::lerConta(const Codigo &codigo)
{
    return repositorio.lerConta(codigo);
}

bool ServicoConta::atualizarConta(const Conta &conta)
{
    return repositorio.atualizarConta(conta);
}

bool ServicoConta::excluirConta(const Codigo &codigo)
{
    return repositorio.excluirConta(codigo);
}

std::vector<Conta> ServicoConta::listarContas()
{
    return repositorio.listarContas();
}