#include "ServicoHospedagem.hpp"

ServicoHospedagem::ServicoHospedagem(const std::string &caminhoBD)
    : repositorio(caminhoBD) {}

bool ServicoHospedagem::criarHospedagem(const Hospedagem &hospedagem)
{
    return repositorio.criarHospedagem(hospedagem);
}

Hospedagem *ServicoHospedagem::lerHospedagem(const Codigo &codigo)
{
    return repositorio.lerHospedagem(codigo);
}

bool ServicoHospedagem::atualizarHospedagem(const Hospedagem &hospedagem)
{
    return repositorio.atualizarHospedagem(hospedagem);
}

bool ServicoHospedagem::excluirHospedagem(const Codigo &codigo)
{
    return repositorio.excluirHospedagem(codigo);
}

std::vector<Hospedagem> ServicoHospedagem::listarHospedagens(const Codigo &destinoCodigo)
{
    return repositorio.listarHospedagens(destinoCodigo);
}