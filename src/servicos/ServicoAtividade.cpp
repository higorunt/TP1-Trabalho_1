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
        
        // Validar se não há sobreposição de horários
        if (!validarHorarioAtividade(atividade.getHorario(), 
                                   atividade.getDuracao(),
                                   atividade.getData(),
                                   atividade.getCodigoDestino())) {
            throw std::runtime_error("Existe conflito de horário com outra atividade");
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
        
        // Validar se não há sobreposição de horários (excluindo a própria atividade)
        if (!validarHorarioAtividade(atividade.getHorario(), 
                                   atividade.getDuracao(),
                                   atividade.getData(),
                                   atividade.getCodigoDestino(),
                                   atividade.getCodigo())) {
            throw std::runtime_error("Existe conflito de horário com outra atividade");
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

bool ServicoAtividade::validarHorarioAtividade(const Horario& horario, const Duracao& duracao,
                                              const Data& data, const Codigo& codigoDestino,
                                              const Codigo& codigoAtividade) {
    // Buscar todas as atividades do destino na mesma data
    std::vector<Atividade> atividades = listarPorDestino(codigoDestino);
    
    // Converter horário da nova atividade para minutos desde meia-noite
    time_t inicioNovo = converterHorarioParaMinutos(horario);
    time_t fimNovo = inicioNovo + duracao.getValor() * 60; // Converter duração para segundos
    
    for (const auto& ativ : atividades) {
        // Ignorar a própria atividade no caso de edição
        if (ativ.getCodigo().getValor() == codigoAtividade.getValor()) 
            continue;
            
        // Verificar apenas atividades do mesmo dia
        if (ativ.getData().getValor() != data.getValor())
            continue;
            
        time_t inicioExistente = converterHorarioParaMinutos(ativ.getHorario());
        time_t fimExistente = inicioExistente + ativ.getDuracao().getValor() * 60;
        
        // Verificar sobreposição
        if ((inicioNovo >= inicioExistente && inicioNovo < fimExistente) || // Início durante outra atividade
            (fimNovo > inicioExistente && fimNovo <= fimExistente) ||      // Fim durante outra atividade
            (inicioNovo <= inicioExistente && fimNovo >= fimExistente)) {  // Engloba outra atividade
            return false;
        }
    }
    
    return true;
}

time_t ServicoAtividade::converterHorarioParaMinutos(const Horario& horario) {
    std::string horarioStr = horario.getValor(); // Formato "HH:MM"
    int horas = std::stoi(horarioStr.substr(0, 2));
    int minutos = std::stoi(horarioStr.substr(3, 2));
    return horas * 3600 + minutos * 60; // Converter para segundos desde meia-noite
}

time_t ServicoAtividade::converterParaTime(const Data& data) {
    std::string dataStr = data.getValor(); // Formato: "DD-MM-AA"
    tm timeinfo = {};
    
    timeinfo.tm_mday = std::stoi(dataStr.substr(0, 2));
    timeinfo.tm_mon = std::stoi(dataStr.substr(3, 2)) - 1;
    timeinfo.tm_year = std::stoi(dataStr.substr(6, 2)) + 2000 - 1900;
    
    return mktime(&timeinfo);
}
