#include "../../include/servicos/ServicoAtividade.hpp"
#include <stdexcept>

ServicoAtividade::ServicoAtividade(RepositorioAtividade* rep, ServicoDestino* srvDestino)
    : repositorioAtividade(rep), servicoDestino(srvDestino) {}

bool ServicoAtividade::criarAtividade(const Atividade& atividade) {
    try {
        // Validar se a data da atividade está dentro do período do destino
        if (!validarDataAtividade(atividade.getData(), atividade.getCodigoDestino())) {
            throw std::runtime_error("Data da atividade fora do período do destino");
        }
        
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
        // Validar se a nova data está dentro do período do destino
        if (!validarDataAtividade(atividade.getData(), atividade.getCodigoDestino())) {
            throw std::runtime_error("Data da atividade fora do período do destino");
        }
        
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

bool ServicoAtividade::validarDataAtividade(const Data& dataAtividade, const Codigo& codigoDestino) {
    try {
        Destino* destino = servicoDestino->buscarDestino(codigoDestino);
        if (!destino) {
            throw std::runtime_error("Destino não encontrado");
        }

        // Converter as datas para time_t para comparação
        time_t dataAtividadeTime = converterParaTime(dataAtividade);
        time_t dataInicioTime = converterParaTime(destino->getDataInicio());
        time_t dataFimTime = converterParaTime(destino->getDataFim());

        delete destino;

        return (dataAtividadeTime >= dataInicioTime && dataAtividadeTime <= dataFimTime);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao validar data: " + std::string(e.what()));
    }
}

time_t ServicoAtividade::converterParaTime(const Data& data) {
    std::string dataStr = data.getValor(); // Formato: "DD-MM-AA"
    tm timeinfo = {};
    
    timeinfo.tm_mday = std::stoi(dataStr.substr(0, 2));
    timeinfo.tm_mon = std::stoi(dataStr.substr(3, 2)) - 1;
    timeinfo.tm_year = std::stoi(dataStr.substr(6, 2)) + 2000 - 1900;
    
    return mktime(&timeinfo);
}
