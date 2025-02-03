//221006404
#ifndef REPOSITORIO_ATIVIDADE_HPP
#define REPOSITORIO_ATIVIDADE_HPP

#include "RepositorioBase.hpp"
#include "../entidades/Atividade.hpp"
#include <vector>
#include <string>

/**
 * @brief Repositório para gerenciamento de Atividades no sistema.
 * 
 * Implementa operações CRUD e consultas específicas para a entidade Atividade.
 */
class RepositorioAtividade : public RepositorioBase {
public:
    /**
     * @brief Construtor do repositório.
     * @param caminhoBD Caminho do banco de dados.
     */
    explicit RepositorioAtividade(const std::string& caminhoBD);

    /**
     * @brief Salva uma nova atividade.
     * @param atividade Atividade a ser salva.
     * @return true se salvou com sucesso, false caso contrário.
     */
    bool salvar(const Atividade& atividade);

    Atividade* buscar(const Codigo& codigo);
    bool atualizar(const Atividade& atividade);
    bool deletar(const Codigo& codigo);
    std::vector<Atividade> listarPorDestino(const Codigo& codigoDestino);
    std::vector<Atividade> listarTodos();

protected:
    /**
     * @brief Cria a tabela de atividades no banco de dados.
     */
    void criarTabela() {  
        executarSQL(
            "CREATE TABLE IF NOT EXISTS atividades ("
            "codigo TEXT PRIMARY KEY,"
            "nome TEXT NOT NULL,"
            "data TEXT NOT NULL,"
            "horario TEXT NOT NULL,"
            "duracao TEXT NOT NULL,"
            "preco REAL NOT NULL,"
            "avaliacao INTEGER NOT NULL,"
            "codigo_destino TEXT NOT NULL,"
            "FOREIGN KEY(codigo_destino) REFERENCES destinos(codigo) ON DELETE CASCADE"
            ");"
        );
    }

private:
    /**
     * @brief Converte um registro do banco em objeto Atividade.
     * @param stmt Statement SQL preparado.
     * @return Objeto Atividade populado.
     */
    Atividade mapearParaEntidade(sqlite3_stmt* stmt);
};

#endif
