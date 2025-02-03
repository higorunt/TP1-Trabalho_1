//221006404

#ifndef REPOSITORIO_HOSPEDAGEM_HPP
#define REPOSITORIO_HOSPEDAGEM_HPP

#include "RepositorioBase.hpp"
#include "../entidades/Hospedagem.hpp"
#include <vector>
#include <string>

/**
 * @brief Reposit�rio para gerenciamento de Hospedagens no sistema.
 * 
 * Implementa opera��es CRUD e consultas espec�ficas para a entidade Hospedagem.
 */
class RepositorioHospedagem : public RepositorioBase {
public:
    /**
     * @brief Construtor do reposit�rio.
     * @param caminhoBD Caminho do banco de dados.
     */
    explicit RepositorioHospedagem(const std::string& caminhoBD);

    /**
     * @brief Salva uma nova hospedagem.
     * @param hospedagem Hospedagem a ser salva.
     * @return true se salvou com sucesso, false caso contr�rio.
     */
    bool salvar(const Hospedagem& hospedagem);

    /**
     * @brief Busca uma hospedagem pelo c�digo.
     * @param codigo C�digo da hospedagem.
     * @return Ponteiro para a hospedagem encontrada ou nullptr.
     */
    Hospedagem* buscar(const Codigo& codigo);

    /**
     * @brief Atualiza uma hospedagem existente.
     * @param hospedagem Hospedagem com dados atualizados.
     * @return true se atualizou com sucesso, false caso contr�rio.
     */
    bool atualizar(const Hospedagem& hospedagem);

    /**
     * @brief Remove uma hospedagem.
     * @param codigo C�digo da hospedagem a ser removida.
     * @return true se removeu com sucesso, false caso contr�rio.
     */
    bool deletar(const Codigo& codigo);

    /**
     * @brief Busca uma hospedagem pelo c�digo do destino.
     * @param codigoDestino C�digo do destino.
     * @return Ponteiro para a hospedagem encontrada ou nullptr.
     */
    Hospedagem* buscarPorDestino(const Codigo& codigoDestino);

protected:
    /**
     * @brief Cria a tabela de hospedagens no banco de dados.
     */
    void criarTabela() {
        executarSQL(
            "CREATE TABLE IF NOT EXISTS hospedagens ("
            "codigo TEXT PRIMARY KEY,"
            "nome TEXT NOT NULL,"
            "diaria REAL NOT NULL,"
            "avaliacao INTEGER NOT NULL,"
            "codigo_destino TEXT NOT NULL UNIQUE," // UNIQUE garante apenas uma hospedagem por destino
            "FOREIGN KEY(codigo_destino) REFERENCES destinos(codigo) ON DELETE CASCADE"
            ");"
        );
    }

private:
    /**
     * @brief Converte um registro do banco em objeto Hospedagem.
     * @param stmt Statement SQL preparado.
     * @return Objeto Hospedagem populado.
     */
    Hospedagem mapearParaEntidade(sqlite3_stmt* stmt);
};

#endif
