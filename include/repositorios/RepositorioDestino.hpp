// include/repositorios/RepositorioDestino.hpp
#ifndef REPOSITORIO_DESTINO_HPP
#define REPOSITORIO_DESTINO_HPP

#include "RepositorioBase.hpp"
#include "../entidades/Destino.hpp"
#include <vector>

class RepositorioDestino : public RepositorioBase {
public:
    RepositorioDestino(const std::string& caminho);
    
    bool salvar(const Destino& destino);
    Destino* buscar(const Codigo& codigo);
    bool atualizar(const Destino& destino);
    bool deletar(const Codigo& codigo);
    std::vector<Destino> listarPorViagem(const Codigo& codigoViagem);

private:
    void criarTabela() {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS destinos (
                codigo TEXT PRIMARY KEY,
                nome TEXT NOT NULL,
                avaliacao INTEGER,
                data_inicio TEXT NOT NULL,
                data_fim TEXT NOT NULL,
                codigo_viagem TEXT NOT NULL,
                FOREIGN KEY (codigo_viagem) REFERENCES viagens(codigo)
            );
        )";
        executarSQL(sql);
    }
};

#endif