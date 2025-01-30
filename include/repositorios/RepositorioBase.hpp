// include/repositorios/RepositorioBase.hpp
#ifndef REPOSITORIO_BASE_HPP
#define REPOSITORIO_BASE_HPP

#include <sqlite3.h>
#include <string>

/**
 * @brief Classe base para reposit�rios que interagem com banco de dados SQLite
 * 
 * Esta classe fornece funcionalidades b�sicas para manipula��o de banco de dados SQLite,
 * incluindo conex�o, desconex�o e execu��o de comandos SQL.
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
     * @brief Executa uma instru��o SQL
     * @param sql String contendo o comando SQL a ser executado
     * @return true se a execu��o for bem-sucedida, false caso contr�rio
     */
    bool executarSQL(const std::string& sql);

    /**
     * @brief Prepara uma instru��o SQL para execu��o
     * @param sql String contendo o comando SQL a ser preparado
     * @return Ponteiro para a instru��o SQL preparada
     */
    sqlite3_stmt* prepararSQL(const std::string& sql);

    /**
     * @brief Finaliza uma instru��o SQL preparada
     * @param stmt Ponteiro para a instru��o SQL a ser finalizada
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
     * @brief Estabelece conex�o com o banco de dados
     * @return true se a conex�o for bem-sucedida, false caso contr�rio
     */
    bool conectar();

    /**
     * @brief Encerra a conex�o com o banco de dados
     */
    void desconectar();
};

#endif