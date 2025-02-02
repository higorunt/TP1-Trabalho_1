// src/servicos/ServicoViagem.cpp
#include "../../include/servicos/ServicoViagem.hpp"
#include <stdexcept>

bool ServicoViagem::criarViagem(const Viagem &viagem)
{
    try
    {
        return repositorioViagem->salvar(viagem);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao criar viagem: " + std::string(e.what()));
    }
}

Viagem *ServicoViagem::buscarViagem(const Codigo &codigo)
{
    try
    {
        return repositorioViagem->buscar(codigo);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao buscar viagem: " + std::string(e.what()));
    }
}

bool ServicoViagem::atualizarViagem(const Viagem &viagem)
{
    try
    {
        return repositorioViagem->atualizar(viagem);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao atualizar viagem: " + std::string(e.what()));
    }
}

bool ServicoViagem::excluirViagem(const Codigo &codigo)
{
    try
    {
        // Verificar se existem destinos associados
        if (possuiDestinos(codigo))
        {
            throw std::runtime_error("Não é possível excluir uma viagem com destinos associados");
        }

        return repositorioViagem->deletar(codigo);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao excluir viagem: " + std::string(e.what()));
    }
}

double ServicoViagem::calcularCustoViagem(const Codigo &codigoViagem)
{
    try
    {
        // Implementar lógica para calcular o custo total da viagem
        // Isso pode envolver somar os custos de todos os destinos, atividades e hospedagens
        return repositorioViagem->calcularCustoTotal(codigoViagem);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao calcular custo da viagem: " + std::string(e.what()));
    }
}

std::vector<Viagem> ServicoViagem::listarViagensPorViajante(const Codigo &codigoViajante)
{
    try
    {
        return repositorioViagem->listarPorViajante(codigoViajante);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao listar Viagens: " + std::string(e.what()));
    }
}

std::vector<Destino> ServicoViagem::listarDestinosPorViagem(const Codigo &codigoViagem)
{
    try
    {
        return repositorioDestino->listarPorViagem(codigoViagem);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao listar destinos: " + std::string(e.what()));
    }
}

bool ServicoViagem::possuiDestinos(const Codigo &codigoViagem)
{
    try
    {
        std::vector<Destino> destinos = listarDestinosPorViagem(codigoViagem);
        return !destinos.empty();
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Erro ao verificar destinos: " + std::string(e.what()));
    }
}