#ifndef REPOSITORIO_ATIVIDADE_HPP
#define REPOSITORIO_ATIVIDADE_HPP

#include "RepositorioBase.hpp"
#include "../entidades/Atividade.hpp"
#include <vector>
#include <string>

class RepositorioAtividade : public RepositorioBase {
public:
    explicit RepositorioAtividade(const std::string& caminhoBD);
    bool salvar(const Atividade& atividade);
    Atividade* buscar(const Codigo& codigo);
    bool atualizar(const Atividade& atividade);
    bool deletar(const Codigo& codigo);
    std::vector<Atividade> listarPorDestino(const Codigo& codigoDestino);
    std::vector<Atividade> listarTodos();

protected:
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
    Atividade mapearParaEntidade(sqlite3_stmt* stmt);
};

#endif
