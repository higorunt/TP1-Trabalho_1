#include "../../include/servicos/ServicoAtividade.hpp"
#include <stdexcept>

ServicoAtividade::ServicoAtividade(RepositorioAtividade* rep)
    : repositorioAtividade(rep) { }

bool ServicoAtividade::criarAtividade(const Atividade& atividade) {
    try {
        return repositorioAtividade->salvar(atividade);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao criar atividade: " + std::string(e.what()));
    }
}

Atividade* ServicoAtividade::buscarAtividade(const Codigo& codigo) {
    try {
        return repositorioAtividade->buscar(codigo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao buscar atividade: " + std::string(e.what()));
    }
}

bool ServicoAtividade::atualizarAtividade(const Atividade& atividade) {
    try {
        return repositorioAtividade->atualizar(atividade);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao atualizar atividade: " + std::string(e.what()));
    }
}

bool ServicoAtividade::excluirAtividade(const Codigo& codigo) {
    try {
        return repositorioAtividade->deletar(codigo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao excluir atividade: " + std::string(e.what()));
    }
}

std::vector<Atividade> ServicoAtividade::listarPorDestino(const Codigo& codigoDestino) {
    try {
        return repositorioAtividade->listarPorDestino(codigoDestino);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao listar atividades por destino: " + std::string(e.what()));
    }
}
