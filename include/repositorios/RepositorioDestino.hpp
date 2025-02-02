#ifndef REPOSITORIO_DESTINO_HPP
#define REPOSITORIO_DESTINO_HPP

#include "../../include/entidades/Destino.hpp"
#include "../../include/repositorios/RepositorioBase.hpp"
#include <vector>
#include <string>

/**
 * @brief Repositório para operações CRUD com Destino.
 */
class RepositorioDestino : public RepositorioBase {
public:
    RepositorioDestino(const std::string& caminhoBD);

    bool salvar(const Destino& destino);
    Destino* buscar(const Codigo& codigo);
    bool atualizar(const Destino& destino);
    bool deletar(const Codigo& codigo);
    std::vector<Destino> listarPorViagem(const Codigo& codigoViagem);
    
    /**
     * @brief Lista todos os destinos cadastrados.
     * @return Vetor com todos os destinos.
     */
    std::vector<Destino> listarTodos();
    
private:
    void criarTabela() {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS destinos (
                codigo TEXT PRIMARY KEY,
                nome TEXT NOT NULL,
                data_inicio TEXT NOT NULL,
                data_fim TEXT NOT NULL,
                avaliacao INTEGER NOT NULL,
                codigo_viagem TEXT NOT NULL,
                FOREIGN KEY (codigo_viagem) REFERENCES viagens(codigo)
            );
        )";
        executarSQL(sql);
    }
    
    Destino mapearParaEntidade(sqlite3_stmt* stmt);
};

#endif // REPOSITORIO_DESTINO_HPP
