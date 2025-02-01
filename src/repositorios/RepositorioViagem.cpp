#include "../../include/repositorios/RepositorioViagem.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>
#include <iostream>


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
    // Implemente a lógica de cálculo conforme a regra de negócio.
    // Neste exemplo, retornamos 0.0.
    return 0.0;
}
