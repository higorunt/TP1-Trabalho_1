#include "../../include/repositorios/RepositorioViagem.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>


// Construtor: conecta ao banco e cria a tabela, se necessário
RepositorioViagem::RepositorioViagem(const std::string& caminho) : RepositorioBase(caminho) {
    if (!conectar()) {
        throw std::runtime_error("Não foi possível conectar ao banco de dados");
    }
    criarTabela();
}

bool RepositorioViagem::salvar(const Viagem& viagem) {
    const char* sql = "INSERT INTO viagens (codigo, nome, avaliacao, codigo_viajante, custo_total) VALUES (?, ?, ?, ?, ?)";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return false;

    try {
        sqlite3_bind_text(stmt, 1, viagem.getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, viagem.getNome().getValor().c_str(), -1, SQLITE_STATIC);
        // Use o valor inteiro diretamente, pois Avaliacao::getValor() retorna um int
        sqlite3_bind_int(stmt, 3, viagem.getAvaliacao().getValor());
        sqlite3_bind_text(stmt, 4, viagem.getConta().getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 5, 0.0); // Custo total inicial é 0

        int result = sqlite3_step(stmt);
        finalizar(stmt);
        return result == SQLITE_DONE;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao salvar viagem: " + std::string(e.what()));
    }
}

Viagem* RepositorioViagem::buscar(const Codigo& codigo) {
    try {
        // Primeiro buscar os dados básicos da viagem
        std::string sql = 
            "SELECT v.codigo, v.nome, v.avaliacao, v.codigo_viajante "
            "FROM viagens v "
            "WHERE v.codigo = ?";
            
        sqlite3_stmt* stmt = prepararSQL(sql);
        
        if (!stmt) {
            throw std::runtime_error("Erro ao preparar consulta SQL");
        }
        
        sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string codViagem = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int avaliacao = sqlite3_column_int(stmt, 2);
            std::string codViajante = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            
            finalizar(stmt);

            // Agora buscar a senha do viajante
            stmt = prepararSQL("SELECT senha FROM viajantes WHERE codigo = ?");
            if (!stmt) {
                throw std::runtime_error("Erro ao preparar consulta SQL para buscar senha");
            }
            
            sqlite3_bind_text(stmt, 1, codViajante.c_str(), -1, SQLITE_STATIC);
            
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string senha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                
                try {
                    Nome nomeViagem(nome);
                    Codigo codViagemObj(codViagem);
                    Avaliacao avaliacaoViagem(avaliacao);
                    Codigo codViajanteObj(codViajante);
                    Senha senhaObj(senha);
                    
                    Conta conta(codViajanteObj, senhaObj);
                    
                    finalizar(stmt);
                    return new Viagem(nomeViagem, codViagemObj, avaliacaoViagem, conta);
                    
                } catch (const std::exception& e) {
                    finalizar(stmt);
                    throw std::runtime_error(std::string("Erro ao criar objeto Viagem: ") + e.what());
                }
            }
            
            finalizar(stmt);
        } else {
            finalizar(stmt);
        }
        
        return nullptr;
        
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao buscar viagem: " + std::string(e.what()));
    }
}

bool RepositorioViagem::atualizar(const Viagem& viagem) {
    try {
        // Primeiro, buscar a senha do viajante
        sqlite3_stmt* stmtViajante = prepararSQL("SELECT senha FROM viajantes WHERE codigo = ?");
        if (!stmtViajante) {
            throw std::runtime_error("Erro ao preparar consulta SQL para buscar senha");
        }
        
        sqlite3_bind_text(stmtViajante, 1, viagem.getConta().getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        
        std::string senhaViajante;
        if (sqlite3_step(stmtViajante) == SQLITE_ROW) {
            senhaViajante = reinterpret_cast<const char*>(sqlite3_column_text(stmtViajante, 0));
        }
        finalizar(stmtViajante);

        // Atualizar a viagem
        std::string sql = 
            "UPDATE viagens "
            "SET nome = ?, avaliacao = ? "
            "WHERE codigo = ? AND codigo_viajante = ?";
            
        sqlite3_stmt* stmt = prepararSQL(sql);
        
        if (!stmt) {
            throw std::runtime_error("Erro ao preparar consulta SQL");
        }
        
        sqlite3_bind_text(stmt, 1, viagem.getNome().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, viagem.getAvaliacao().getValor());
        sqlite3_bind_text(stmt, 3, viagem.getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, viagem.getConta().getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            finalizar(stmt);
            return false;
        }
        
        finalizar(stmt);
        return true;
        
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao atualizar viagem: " + std::string(e.what()));
    }
}

bool RepositorioViagem::deletar(const Codigo& codigo) {
    const char* sql = "DELETE FROM viagens WHERE codigo = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return false;

    try {
        sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        finalizar(stmt);
        return result == SQLITE_DONE;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao deletar viagem: " + std::string(e.what()));
    }
}

// src/repositorios/RepositorioViagem.cpp
std::vector<Viagem> RepositorioViagem::listarPorViajante(const Codigo& codigoViajante) {
    std::vector<Viagem> viagens;
    
    try {
        // Primeiro, buscar a senha do viajante na tabela correta
        sqlite3_stmt* stmtViajante = prepararSQL("SELECT senha FROM viajantes WHERE codigo = ?");
        if (!stmtViajante) {
            throw std::runtime_error("Erro ao preparar consulta SQL para buscar senha");
        }
        
        sqlite3_bind_text(stmtViajante, 1, codigoViajante.getValor().c_str(), -1, SQLITE_STATIC);
        
        std::string senhaViajante;
        if (sqlite3_step(stmtViajante) == SQLITE_ROW) {
            senhaViajante = reinterpret_cast<const char*>(sqlite3_column_text(stmtViajante, 0));
        }
        finalizar(stmtViajante);

        // Agora buscar as viagens
        std::string sql = 
            "SELECT v.codigo, v.nome, v.avaliacao, v.codigo_viajante "
            "FROM viagens v "
            "WHERE v.codigo_viajante = ?";
            
        sqlite3_stmt* stmt = prepararSQL(sql);
        
        if (!stmt) {
            throw std::runtime_error("Erro ao preparar consulta SQL");
        }
        
        sqlite3_bind_text(stmt, 1, codigoViajante.getValor().c_str(), -1, SQLITE_STATIC);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string codigo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int avaliacao = sqlite3_column_int(stmt, 2);
            std::string codViajanteBD = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            
            try {
                Nome nomeViagem(nome);
                Codigo codViagem(codigo);
                Avaliacao avaliacaoViagem(avaliacao);
                Codigo codViajanteObj(codViajanteBD);
                Senha senhaObj(senhaViajante);
                
                // Criar conta com a senha real do viajante
                Conta conta(codViajanteObj, senhaObj);
                
                Viagem viagem(nomeViagem, codViagem, avaliacaoViagem, conta);
                viagens.push_back(viagem);
                
            } catch (const std::exception& e) {
                std::cerr << "Erro ao processar viagem: " << e.what() << std::endl;
                continue;
            }
        }
        
        finalizar(stmt);
        return viagens;
        
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro ao listar viagens: " + std::string(e.what()));
    }
}

double RepositorioViagem::calcularCustoTotal(const Codigo& codigoViagem) {
    double custoTotal = 0.0;
    
    // 1. Buscar todos os destinos da viagem
    std::string sqlDestinos = 
        "SELECT codigo FROM destinos WHERE codigo_viagem = ?";
    
    sqlite3_stmt* stmtDestinos = prepararSQL(sqlDestinos);
    sqlite3_bind_text(stmtDestinos, 1, codigoViagem.getValor().c_str(), -1, SQLITE_STATIC);
    
    std::vector<std::string> codigosDestinos;
    while (sqlite3_step(stmtDestinos) == SQLITE_ROW) {
        codigosDestinos.push_back(
            reinterpret_cast<const char*>(sqlite3_column_text(stmtDestinos, 0))
        );
    }
    finalizar(stmtDestinos);
    
    // 2. Para cada destino, somar custos das atividades e hospedagem
    for (const auto& codigoDestino : codigosDestinos) {
        // Somar custos das atividades
        std::string sqlAtividades = 
            "SELECT SUM(CAST(preco AS FLOAT)) FROM atividades WHERE codigo_destino = ?";
        
        sqlite3_stmt* stmtAtividades = prepararSQL(sqlAtividades);
        sqlite3_bind_text(stmtAtividades, 1, codigoDestino.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmtAtividades) == SQLITE_ROW) {
            custoTotal += sqlite3_column_double(stmtAtividades, 0);
        }
        finalizar(stmtAtividades);
        
        // Somar custos da hospedagem
        std::string sqlHospedagem = 
            "SELECT CAST(diaria AS FLOAT) FROM hospedagens WHERE codigo_destino = ?";
        
        sqlite3_stmt* stmtHospedagem = prepararSQL(sqlHospedagem);
        sqlite3_bind_text(stmtHospedagem, 1, codigoDestino.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmtHospedagem) == SQLITE_ROW) {
            // Calcular custo total da hospedagem (diária * número de dias)
            double diaria = sqlite3_column_double(stmtHospedagem, 0);
            // Buscar período do destino para calcular número de dias
            std::string sqlPeriodo = 
                "SELECT data_inicio, data_fim FROM destinos WHERE codigo = ?";
            
            sqlite3_stmt* stmtPeriodo = prepararSQL(sqlPeriodo);
            sqlite3_bind_text(stmtPeriodo, 1, codigoDestino.c_str(), -1, SQLITE_STATIC);
            
            if (sqlite3_step(stmtPeriodo) == SQLITE_ROW) {
                std::string dataInicio = reinterpret_cast<const char*>(sqlite3_column_text(stmtPeriodo, 0));
                std::string dataFim = reinterpret_cast<const char*>(sqlite3_column_text(stmtPeriodo, 1));
                
                // Converter datas para calcular diferença
                int dias = calcularDiasEntreDatas(dataInicio, dataFim);
                custoTotal += (diaria * dias);
            }
            finalizar(stmtPeriodo);
        }
        finalizar(stmtHospedagem);
    }
    
    // 3. Atualizar o custo total na tabela de viagens
    std::string sqlUpdate = 
        "UPDATE viagens SET custo_total = ? WHERE codigo = ?";
    
    sqlite3_stmt* stmtUpdate = prepararSQL(sqlUpdate);
    sqlite3_bind_double(stmtUpdate, 1, custoTotal);
    sqlite3_bind_text(stmtUpdate, 2, codigoViagem.getValor().c_str(), -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmtUpdate) != SQLITE_DONE) {
        finalizar(stmtUpdate);
        throw std::runtime_error("Erro ao atualizar custo total da viagem");
    }
    finalizar(stmtUpdate);
    
    return custoTotal;
}

int RepositorioViagem::calcularDiasEntreDatas(const std::string& dataInicio, const std::string& dataFim) {
    // Converter datas do formato "DD-MM-AA" para estrutura tm
    tm tmInicio = {}, tmFim = {};
    
    // Extrair dia, mês e ano da data de início
    tmInicio.tm_mday = std::stoi(dataInicio.substr(0, 2));
    tmInicio.tm_mon = std::stoi(dataInicio.substr(3, 2)) - 1;
    tmInicio.tm_year = std::stoi(dataInicio.substr(6, 2)) + 2000 - 1900;
    
    // Extrair dia, mês e ano da data de fim
    tmFim.tm_mday = std::stoi(dataFim.substr(0, 2));
    tmFim.tm_mon = std::stoi(dataFim.substr(3, 2)) - 1;
    tmFim.tm_year = std::stoi(dataFim.substr(6, 2)) + 2000 - 1900;
    
    // Converter para time_t e calcular diferença em segundos
    time_t timeInicio = mktime(&tmInicio);
    time_t timeFim = mktime(&tmFim);
    
    // Converter diferença de segundos para dias
    return static_cast<int>(difftime(timeFim, timeInicio) / (60 * 60 * 24)) + 1; // +1 para incluir o último dia
}
