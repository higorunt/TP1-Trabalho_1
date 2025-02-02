#include "../../include/servicos/ServicoDestino.hpp"
#include <stdexcept>
#include <string>

ServicoDestino::ServicoDestino(RepositorioDestino* repDestino)
    : repositorioDestino(repDestino) { }

bool ServicoDestino::criarDestino(const Destino& destino) {
    try {
        return repositorioDestino->salvar(destino);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao criar destino: " + std::string(e.what()));
    }
}

Destino* ServicoDestino::buscarDestino(const Codigo& codigo) {
    try {
        return repositorioDestino->buscar(codigo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao buscar destino: " + std::string(e.what()));
    }
}

bool ServicoDestino::atualizarDestino(const Destino& destino) {
    try {
        return repositorioDestino->atualizar(destino);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao atualizar destino: " + std::string(e.what()));
    }
}

bool ServicoDestino::excluirDestino(const Codigo& codigo) {
    try {
        return repositorioDestino->deletar(codigo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao excluir destino: " + std::string(e.what()));
    }
}

std::vector<Destino> ServicoDestino::listarPorViagem(const Codigo& codigoViagem) {
    try {
        return repositorioDestino->listarPorViagem(codigoViagem);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao listar destinos por viagem: " + std::string(e.what()));
    }
}

// Novo método: lista todos os destinos cadastrados
std::vector<Destino> ServicoDestino::listarTodos() {
    try {
        return repositorioDestino->listarTodos();  // Certifique-se de que RepositorioDestino tenha esse método
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao listar todos os destinos: " + std::string(e.what()));
    }
}
