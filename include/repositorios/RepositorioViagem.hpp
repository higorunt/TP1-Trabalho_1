#ifndef REPOSITORIO_VIAGEM_HPP
#define REPOSITORIO_VIAGEM_HPP

#include "RepositorioBase.hpp"
#include "../interfaces/IRepositorioViagem.hpp"
#include "../entidades/Viagem.hpp"
#include <vector>

class RepositorioViagem : 
    public RepositorioBase,
    public IRepositorioViagem {
public:
    RepositorioViagem(const std::string& caminho);
    
    bool salvar(const Viagem& viagem) override;
    Viagem* buscar(const Codigo& codigo) override;
    bool atualizar(const Viagem& viagem) override;
    bool deletar(const Codigo& codigo) override;
    std::vector<Viagem> listarPorViajante(const Codigo& codigoViajante) override;
    double calcularCustoTotal(const Codigo& codigoViagem);

private:
    void criarTabela() {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS viagens (
                codigo TEXT PRIMARY KEY,
                nome TEXT NOT NULL,
                avaliacao INTEGER,
                codigo_viajante TEXT NOT NULL,
                custo_total REAL DEFAULT 0.0,
                FOREIGN KEY (codigo_viajante) REFERENCES viajantes(codigo)
            );
        )";
        executarSQL(sql);
    }
};

#endif // REPOSITORIO_VIAGEM_HPP
