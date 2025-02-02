#ifndef REPOSITORIO_HOSPEDAGEM_HPP
#define REPOSITORIO_HOSPEDAGEM_HPP

#include "RepositorioBase.hpp"
#include "../entidades/Hospedagem.hpp"
#include <vector>
#include <string>

class RepositorioHospedagem : public RepositorioBase {
public:
    explicit RepositorioHospedagem(const std::string& caminhoBD);
    bool salvar(const Hospedagem& hospedagem);
    Hospedagem* buscar(const Codigo& codigo);
    bool atualizar(const Hospedagem& hospedagem);
    bool deletar(const Codigo& codigo);
    Hospedagem* buscarPorDestino(const Codigo& codigoDestino);

protected:
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
    Hospedagem mapearParaEntidade(sqlite3_stmt* stmt);
};

#endif
