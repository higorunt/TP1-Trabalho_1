// include/repositorios/RepositorioBase.hpp
#ifndef REPOSITORIO_BASE_HPP
#define REPOSITORIO_BASE_HPP

#include <sqlite3.h>
#include <string>

class RepositorioBase {
protected:
    sqlite3* bd;
    std::string caminhoBD;

    // Métodos utilitários para SQLite
    bool executarSQL(const std::string& sql);
    sqlite3_stmt* prepararSQL(const std::string& sql);
    void finalizar(sqlite3_stmt* stmt);

public:
    RepositorioBase(const std::string& caminho);
    virtual ~RepositorioBase();
    
    bool conectar();
    void desconectar();
};

#endif