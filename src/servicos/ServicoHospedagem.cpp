#include "../../include/servicos/ServicoHospedagem.hpp"
#include <stdexcept>

ServicoHospedagem::ServicoHospedagem(RepositorioHospedagem* rep)
    : repositorioHospedagem(rep) { }

bool ServicoHospedagem::criarHospedagem(const Hospedagem& hospedagem) {
    try {
        // Verifica se já existe hospedagem para este destino
        if (buscarPorDestino(hospedagem.getCodigoDestino()) != nullptr) {
            throw std::runtime_error("Já existe uma hospedagem cadastrada para este destino");
        }
        return repositorioHospedagem->salvar(hospedagem);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao criar hospedagem: " + std::string(e.what()));
    }
}

Hospedagem* ServicoHospedagem::buscarHospedagem(const Codigo& codigo) {
    try {
        return repositorioHospedagem->buscar(codigo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao buscar hospedagem: " + std::string(e.what()));
    }
}

bool ServicoHospedagem::atualizarHospedagem(const Hospedagem& hospedagem) {
    try {
        return repositorioHospedagem->atualizar(hospedagem);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao atualizar hospedagem: " + std::string(e.what()));
    }
}

bool ServicoHospedagem::excluirHospedagem(const Codigo& codigo) {
    try {
        return repositorioHospedagem->deletar(codigo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao excluir hospedagem: " + std::string(e.what()));
    }
}

Hospedagem* ServicoHospedagem::buscarPorDestino(const Codigo& codigoDestino) {
    try {
        return repositorioHospedagem->buscarPorDestino(codigoDestino);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao buscar hospedagem por destino: " + std::string(e.what()));
    }
}
