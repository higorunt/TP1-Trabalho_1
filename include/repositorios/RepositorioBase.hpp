// include/repositorios/RepositorioBase.hpp
#ifndef REPOSITORIO_BASE_HPP
#define REPOSITORIO_BASE_HPP

#include <sqlite3.h>
#include <string>

/**
 * @brief Classe base para repositórios que interagem com banco de dados SQLite
 * 
 * Esta classe fornece funcionalidades básicas para manipulação de banco de dados SQLite,
 * incluindo conexão, desconexão e execução de comandos SQL.
 */
class RepositorioBase {
protected:
    /**
     * @brief Ponteiro para o banco de dados SQLite
     */
    sqlite3* bd;

    /**
     * @brief Caminho do arquivo do banco de dados
     */
    std::string caminhoBD;

    /**
     * @brief Executa uma instrução SQL
     * @param sql String contendo o comando SQL a ser executado
     * @return true se a execução for bem-sucedida, false caso contrário
     */
    bool executarSQL(const std::string& sql);

    /**
     * @brief Prepara uma instrução SQL para execução
     * @param sql String contendo o comando SQL a ser preparado
     * @return Ponteiro para a instrução SQL preparada
     */
    sqlite3_stmt* prepararSQL(const std::string& sql);

    /**
     * @brief Finaliza uma instrução SQL preparada
     * @param stmt Ponteiro para a instrução SQL a ser finalizada
     */
    void finalizar(sqlite3_stmt* stmt);

public:
    /**
     * @brief Construtor
     * @param caminho Caminho do arquivo do banco de dados
     */
    RepositorioBase(const std::string& caminho);

    /**
     * @brief Destrutor virtual
     */
    virtual ~RepositorioBase();
    
    /**
     * @brief Estabelece conexão com o banco de dados
     * @return true se a conexão for bem-sucedida, false caso contrário
     */
    bool conectar();

    /**
     * @brief Encerra a conexão com o banco de dados
     */
    void desconectar();
};

#endif