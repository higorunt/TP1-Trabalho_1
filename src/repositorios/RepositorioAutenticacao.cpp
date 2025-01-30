// src/repositorios/RepositorioAutenticacao.cpp
#include "../../include/repositorios/RepositorioAutenticacao.hpp"
#include <stdexcept>

RepositorioAutenticacao::RepositorioAutenticacao(const std::string& caminho) 
    : RepositorioBase(caminho) {
    
    conectar();
    
    // Criar tabela se n�o existir
    const char* sql = 
        "CREATE TABLE IF NOT EXISTS viajantes ("
        "codigo TEXT PRIMARY KEY,"
        "nome TEXT NOT NULL,"
        "senha TEXT NOT NULL"
        ");";
    
    executarSQL(sql);
}

/**
 * @brief Busca um Viajante no banco de dados pelo c�digo fornecido
 * 
 * @details Este m�todo realiza uma consulta SQL para buscar informa��es de um viajante
 * espec�fico na tabela 'viajantes' utilizando o c�digo como crit�rio de busca.
 * As informa��es recuperadas s�o utilizadas para construir e retornar um objeto Viajante.
 * 
 * @param codigo Objeto Codigo contendo o c�digo do viajante a ser buscado
 * 
 * @return Ponteiro para um objeto Viajante se encontrado, nullptr caso contr�rio
 * 
 * @throws Pode propagar exce��es da constru��o dos objetos Codigo, Nome, Senha,
 * Conta e Viajante, por�m estas s�o capturadas internamente
 * 
 * @note As exce��es s�o capturadas e logadas internamente, n�o propagando para o chamador
 * 
 * @see Viajante
 * @see Codigo
 * @see Nome 
 * @see Senha
 * @see Conta
 */
Viajante* RepositorioAutenticacao::buscar(const Codigo& codigo) {
    const std::string sql = 
        "SELECT codigo, nome, senha FROM viajantes WHERE codigo = ?;";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);
    
    Viajante* viajante = nullptr;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* cod = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* senha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        
        try {
            Codigo codObj(cod);
            Nome nomeObj(nome);
            Senha senhaObj(senha);
            
            Conta conta(codObj, senhaObj);
            viajante = new Viajante(nomeObj, conta);
        }
        catch (const std::exception& e) {
            // Log do erro
        }
    }
    
    finalizar(stmt);
    return viajante;
}

bool RepositorioAutenticacao::salvar(const Viajante& viajante) {
    const std::string sql = 
        "INSERT OR REPLACE INTO viajantes (codigo, nome, senha) VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    const Codigo& codigo = viajante.getConta().getCodigo();
    const Nome& nome = viajante.getNome();
    const Senha& senha = viajante.getConta().getSenha();
    
    sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nome.getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, senha.getValor().c_str(), -1, SQLITE_STATIC);
    
    int rc = sqlite3_step(stmt);
    finalizar(stmt);
    
    return rc == SQLITE_DONE;
}

bool RepositorioAutenticacao::atualizar(const Viajante& viajante) {
    return salvar(viajante); // INSERT OR REPLACE j� lida com isso
}

bool RepositorioAutenticacao::deletar(const Codigo& codigo) {
    const std::string sql = "DELETE FROM viajantes WHERE codigo = ?;";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);
    
    int rc = sqlite3_step(stmt);
    finalizar(stmt);
    
    return rc == SQLITE_DONE;
}