// src/repositories/SQLiteAutenticacaoRepository.cpp
#include "../../include/repositories/SQLiteAutenticacaoRepository.hpp"

SQLiteAutenticacaoRepository::SQLiteAutenticacaoRepository(const std::string& dbPath) 
    : dbPath(dbPath), db(nullptr) {
    std::cout << "Inicializando banco de dados em: " << dbPath << std::endl;
    inicializarBancoDeDados();
    verificarBancoDeDados();
}

SQLiteAutenticacaoRepository::~SQLiteAutenticacaoRepository() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Conexão com banco de dados fechada." << std::endl;
    }
}

void SQLiteAutenticacaoRepository::inicializarBancoDeDados() {
    std::cout << "Tentando abrir banco de dados..." << std::endl;
    int rc = sqlite3_open(dbPath.c_str(), &db);
    
    if (rc) {
        std::string erro = "Erro ao abrir banco de dados: ";
        erro += sqlite3_errmsg(db);
        std::cerr << erro << std::endl;
        throw std::runtime_error(erro);
    }
    std::cout << "Banco de dados aberto com sucesso!" << std::endl;
}

void SQLiteAutenticacaoRepository::criarTabelas() {
    std::cout << "Criando tabela de viajantes..." << std::endl;
    const char* sql = 
        "CREATE TABLE IF NOT EXISTS viajantes ("
        "codigo TEXT PRIMARY KEY,"
        "nome TEXT NOT NULL,"
        "senha TEXT NOT NULL"
        ");";
        
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::string erro = "Erro SQL ao criar tabelas: ";
        erro += errMsg;
        sqlite3_free(errMsg);
        std::cerr << erro << std::endl;
        throw std::runtime_error(erro);
    }
    std::cout << "Tabela criada com sucesso!" << std::endl;
}

bool SQLiteAutenticacaoRepository::verificarBancoDeDados() {
    std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='viajantes';";
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao verificar tabelas: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    bool tabelaExiste = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        tabelaExiste = true;
        std::cout << "Tabela 'viajantes' encontrada." << std::endl;
    }
    
    sqlite3_finalize(stmt);
    
    if (!tabelaExiste) {
        std::cout << "Tabela 'viajantes' não existe. Criando..." << std::endl;
        criarTabelas();
    }
    
    return true;
}

Viajante* SQLiteAutenticacaoRepository::buscarPorCodigo(const Codigo& codigo) {
    std::cout << "Buscando viajante com código: " << codigo.getValor() << std::endl;
    
    std::string sql = "SELECT codigo, nome, senha FROM viajantes WHERE codigo = ?;";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar busca: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    
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
            std::cout << "Viajante encontrado: " << nome << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Erro ao criar objeto viajante: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Viajante não encontrado." << std::endl;
    }
    
    sqlite3_finalize(stmt);
    return viajante;
}

bool SQLiteAutenticacaoRepository::salvar(const Viajante& viajante) {
    std::cout << "Tentando salvar viajante..." << std::endl;
    
    std::string sql = 
        "INSERT OR REPLACE INTO viajantes (codigo, nome, senha) "
        "VALUES (?, ?, ?);";
        
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    const Codigo& codigo = viajante.getConta().getCodigo();
    const Nome& nome = viajante.getNome();
    const Senha& senha = viajante.getConta().getSenha();
    
    sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nome.getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, senha.getValor().c_str(), -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir viajante: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::cout << "Viajante salvo com sucesso!" << std::endl;
    return true;
}

bool SQLiteAutenticacaoRepository::listarViajantes() {
    std::cout << "\nListando todos os viajantes:" << std::endl;
    
    const char* sql = "SELECT codigo, nome FROM viajantes;";
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* codigo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::cout << "Código: " << codigo << ", Nome: " << nome << std::endl;
    }
    
    sqlite3_finalize(stmt);
    return true;
}

bool SQLiteAutenticacaoRepository::limparBancoDeDados() {
    std::cout << "Limpando banco de dados..." << std::endl;
    
    const char* sql = "DELETE FROM viajantes;";
    char* errMsg = nullptr;
    
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao limpar banco de dados: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    std::cout << "Banco de dados limpo com sucesso!" << std::endl;
    return true;
}