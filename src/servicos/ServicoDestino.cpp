#include "ServicoDestino.hpp"

ServicoDestino::ServicoDestino(const std::string &caminhoBD)
    : repositorio(caminhoBD) {}

bool ServicoDestino::criarDestino(const Destino &destino)
{
    // Valida��es de neg�cio (se necess�rio)
    return repositorio.criarDestino(destino);
}

Destino *ServicoDestino::lerDestino(const Codigo &codigo)
{
    return repositorio.lerDestino(codigo);
}

bool ServicoDestino::atualizarDestino(const Destino &destino)
{
    // Valida��es de neg�cio (se necess�rio)
    return repositorio.atualizarDestino(destino);
}

bool ServicoDestino::excluirDestino(const Codigo &codigo)
{
    return repositorio.excluirDestino(codigo);
}

std::vector<Destino> ServicoDestino::listarDestinos(const Codigo &viagemCodigo)
{
    return repositorio.listarDestinos(viagemCodigo);
}