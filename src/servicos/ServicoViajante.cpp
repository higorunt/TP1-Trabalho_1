#include "ServicoViajante.hpp"

ServicoViajante::ServicoViajante(const std::string &caminhoBD)
    : repositorio(caminhoBD) {}

bool ServicoViajante::criarViajante(const Viajante &viajante)
{
    return repositorio.criarViajante(viajante);
}

Viajante *ServicoViajante::lerViajante(const Codigo &codigo)
{
    return repositorio.lerViajante(codigo);
}

bool ServicoViajante::atualizarViajante(const Viajante &viajante)
{
    return repositorio.atualizarViajante(viajante);
}

bool ServicoViajante::excluirViajante(const Codigo &codigo)
{
    return repositorio.excluirViajante(codigo);
}

std::vector<Viajante> ServicoViajante::listarViajantes()
{
    return repositorio.listarViajantes();
}