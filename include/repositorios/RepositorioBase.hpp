//221006404

#ifndef REPOSITORIO_BASE_HPP
#define REPOSITORIO_BASE_HPP

#include <sqlite3.h>
#include <string>

/**
 * @brief Classe base para todos os repositórios do sistema.
 * 
 * Fornece funcionalidades básicas para interação com o banco de dados SQLite.
 */
class RepositorioBase {
protected:
    sqlite3* bd;           ///< Ponteiro para o banco de dados SQLite
    std::string caminhoBD; ///< Caminho do arquivo do banco de dados

    /**
     * @brief Executa uma query SQL.
     * @param sql Query SQL a ser executada.
     * @return true se a execução foi bem sucedida, false caso contrário.
     */
    bool executarSQL(const std::string& sql);

    /**
     * @brief Prepara uma query SQL parametrizada.
     * @param sql Query SQL a ser preparada.
     * @return Ponteiro para a query preparada.
     */
    sqlite3_stmt* prepararSQL(const std::string& sql);

    /**
     * @brief Finaliza uma query preparada.
     * @param stmt Ponteiro para a query preparada.
     */
    void finalizar(sqlite3_stmt* stmt);

public:
    /**
     * @brief Construtor da classe.
     * @param caminho Caminho do arquivo do banco de dados.
     */
    RepositorioBase(const std::string& caminho);
    
    /**
     * @brief Destrutor virtual da classe.
     */
    virtual ~RepositorioBase();
    
    /**
     * @brief Estabelece conexão com o banco de dados.
     * @return true se conectou com sucesso, false caso contrário.
     */
    bool conectar();

    /**
     * @brief Encerra a conexão com o banco de dados.
     */
    void desconectar();
};

#endif