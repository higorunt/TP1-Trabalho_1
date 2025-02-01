#include "../../include/repositorios/RepositorioDestino.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>

RepositorioDestino::RepositorioDestino(const std::string& caminho) : RepositorioBase(caminho) {
    conectar();
    criarTabela();
}

bool RepositorioDestino::salvar(const Destino& destino) {
    const char* sql = "INSERT INTO destinos (codigo, nome, avaliacao, data_inicio, data_fim, codigo_viagem) "
                      "VALUES (?, ?, ?, ?, ?, ?)";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return false;

    try {
        sqlite3_bind_text(stmt, 1, destino.getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, destino.getNome().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, destino.getAvaliacao().getValor());
        sqlite3_bind_text(stmt, 4, destino.getDataInicio().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, destino.getDataFim().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, destino.codigoViagem.getValor().c_str(), -1, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        finalizar(stmt);
        return result == SQLITE_DONE;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao salvar destino: " + std::string(e.what()));
    }
}

Destino* RepositorioDestino::buscar(const Codigo& codigo) {
    const char* sql = "SELECT * FROM destinos WHERE codigo = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return nullptr;

    try {
        sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            Codigo cod((const char*)sqlite3_column_text(stmt, 0));
            Nome nome((const char*)sqlite3_column_text(stmt, 1));
            Avaliacao aval(sqlite3_column_int(stmt, 2));
            
            // Converter string da data para inteiros
            std::string dataInicioStr((const char*)sqlite3_column_text(stmt, 3));
            std::string dataFimStr((const char*)sqlite3_column_text(stmt, 4));
            
            // Assumindo formato dd/mm/aa
            int diaInicio = std::stoi(dataInicioStr.substr(0,2));
            int mesInicio = std::stoi(dataInicioStr.substr(3,2));
            int anoInicio = std::stoi(dataInicioStr.substr(6,2));
            
            int diaFim = std::stoi(dataFimStr.substr(0,2));
            int mesFim = std::stoi(dataFimStr.substr(3,2));
            int anoFim = std::stoi(dataFimStr.substr(6,2));
            
            Data dataInicio(diaInicio, mesInicio, anoInicio);
            Data dataFim(diaFim, mesFim, anoFim);
            
            finalizar(stmt);
            return new Destino(nome, cod, aval, dataInicio, dataFim);
        }
        
        finalizar(stmt);
        return nullptr;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao buscar destino: " + std::string(e.what()));
    }
}

bool RepositorioDestino::atualizar(const Destino& destino) {
    const char* sql = "UPDATE destinos SET nome = ?, avaliacao = ?, data_inicio = ?, data_fim = ? WHERE codigo = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return false;

    try {
        sqlite3_bind_text(stmt, 1, destino.getNome().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, destino.getAvaliacao().getValor());
        sqlite3_bind_text(stmt, 3, destino.getDataInicio().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, destino.getDataFim().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, destino.getCodigo().getValor().c_str(), -1, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        finalizar(stmt);
        return result == SQLITE_DONE;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao atualizar destino: " + std::string(e.what()));
    }
}

bool RepositorioDestino::deletar(const Codigo& codigo) {
    const char* sql = "DELETE FROM destinos WHERE codigo = ?";
    
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
        throw std::runtime_error("Erro ao deletar destino: " + std::string(e.what()));
    }
}

std::vector<Destino> RepositorioDestino::listarPorViagem(const Codigo& codigoViagem) {
    std::vector<Destino> destinos;
    const char* sql = "SELECT * FROM destinos WHERE codigo_viagem = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return destinos;

    try {
        sqlite3_bind_text(stmt, 1, codigoViagem.getValor().c_str(), -1, SQLITE_STATIC);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Codigo cod((const char*)sqlite3_column_text(stmt, 0));
            Nome nome((const char*)sqlite3_column_text(stmt, 1));
            Avaliacao aval(sqlite3_column_int(stmt, 2));
            
            // Converter string da data para inteiros
            std::string dataInicioStr((const char*)sqlite3_column_text(stmt, 3));
            std::string dataFimStr((const char*)sqlite3_column_text(stmt, 4));
            
            // Assumindo formato dd/mm/aa
            int diaInicio = std::stoi(dataInicioStr.substr(0,2));
            int mesInicio = std::stoi(dataInicioStr.substr(3,2));
            int anoInicio = std::stoi(dataInicioStr.substr(6,2));
            
            int diaFim = std::stoi(dataFimStr.substr(0,2));
            int mesFim = std::stoi(dataFimStr.substr(3,2));
            int anoFim = std::stoi(dataFimStr.substr(6,2));
            
            Data dataInicio(diaInicio, mesInicio, anoInicio);
            Data dataFim(diaFim, mesFim, anoFim);
            
            destinos.emplace_back(nome, cod, aval, dataInicio, dataFim);
        }
        
        finalizar(stmt);
        return destinos;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao listar destinos: " + std::string(e.what()));
    }
}