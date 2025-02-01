#include "../../include/servicos/ServicoViagem.hpp"

ServicoViagem::ServicoViagem(const std::string &caminhoBD)
    : repositorio(caminhoBD) {}

bool ServicoViagem::criarViagem(const Viagem &viagem)
{
    // Validações de negócio (se necessario)
    return repositorio.criarViagem(viagem);
}

Viagem *ServicoViagem::lerViagem(const Codigo &codigo)
{
    return repositorio.lerViagem(codigo);
}

bool ServicoViagem::atualizarViagem(const Viagem &viagem)
{
    // Validações de negócio (se necessario)
    return repositorio.atualizarViagem(viagem);
}

bool ServicoViagem::excluirViagem(const Codigo &codigo)
{
    return repositorio.excluirViagem(codigo);
}

std::vector<Viagem> ServicoViagem::listarViagens(const Codigo &viajanteCodigo)
{
    return repositorio.listarViagens(viajanteCodigo);
}