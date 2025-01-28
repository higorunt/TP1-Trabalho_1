// include/repositories/SQLiteAutenticacaoRepository.hpp
#ifndef SQLITE_AUTENTICACAO_REPOSITORY_HPP
#define SQLITE_AUTENTICACAO_REPOSITORY_HPP

#include <sqlite3.h>
#include "../interfaces/IAutenticacaoRepository.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

class SQLiteAutenticacaoRepository : public IAutenticacaoRepository {
private:
    sqlite3* db;
    std::string dbPath;
    
    void inicializarBancoDeDados();
    void criarTabelas();
    static int callbackBusca(void* data, int argc, char** argv, char** azColName);

public:
    SQLiteAutenticacaoRepository(const std::string& dbPath = "viagens.db");
    ~SQLiteAutenticacaoRepository() override;
    
    Viajante* buscarPorCodigo(const Codigo& codigo) override;
    bool salvar(const Viajante& viajante) override;
    bool verificarBancoDeDados();
    
    // Métodos utilitários
    bool limparBancoDeDados();
    bool listarViajantes();
};

#endif