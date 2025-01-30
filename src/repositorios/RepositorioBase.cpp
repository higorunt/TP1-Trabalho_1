// src/repositorios/RepositorioBase.cpp
#include "../../include/repositorios/RepositorioBase.hpp"
#include <stdexcept>

RepositorioBase::RepositorioBase(const std::string& caminho) 
    : caminhoBD(caminho), bd(nullptr) {}

RepositorioBase::~RepositorioBase() {
    desconectar();
}

bool RepositorioBase::conectar() {
    if (bd) return true; // J� est� conectado

    int rc = sqlite3_open(caminhoBD.c_str(), &bd);
    if (rc) {
        throw std::runtime_error("Erro ao conectar ao banco: " + 
            std::string(sqlite3_errmsg(bd)));
    }
    return true;
}

void RepositorioBase::desconectar() {
    if (bd) {
        sqlite3_close(bd);
        bd = nullptr;
    }
}

/**
 * @brief Executa uma instru��o SQL no banco de dados SQLite
 * 
 * @param sql String contendo a instru��o SQL a ser executada
 * @return true Se a execu��o for bem sucedida
 * @throw std::runtime_error Se houver erro na execu��o da instru��o SQL
 * 
 * Esta fun��o executa uma instru��o SQL no banco de dados SQLite.
 * Em caso de erro na execu��o, uma exce��o � lan�ada com a mensagem de erro.
 */
bool RepositorioBase::executarSQL(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::string erro = errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error("Erro SQL: " + erro);
    }
    return true;
}

sqlite3_stmt* RepositorioBase::prepararSQL(const std::string& sql) {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar SQL: " + 
            std::string(sqlite3_errmsg(bd)));
    }
    return stmt;
}

void RepositorioBase::finalizar(sqlite3_stmt* stmt) {
    sqlite3_finalize(stmt);
}