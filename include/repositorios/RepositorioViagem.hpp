//221006440
#ifndef REPOSITORIO_VIAGEM_HPP
#define REPOSITORIO_VIAGEM_HPP

#include "RepositorioBase.hpp"
#include "../interfaces/IRepositorioViagem.hpp"
#include "../entidades/Viagem.hpp"
#include <vector>

/**
 * @brief Repositório para gerenciamento de Viagens no sistema.
 * 
 * Implementa as operações CRUD e outras operações específicas para a entidade Viagem.
 */
class RepositorioViagem : 
    public RepositorioBase,
    public IRepositorioViagem {
public:
    /**
     * @brief Construtor do repositório.
     * @param caminho Caminho do banco de dados.
     */
    RepositorioViagem(const std::string& caminho);
    
    bool salvar(const Viagem& viagem) override;
    Viagem* buscar(const Codigo& codigo) override;
    bool atualizar(const Viagem& viagem) override;
    bool deletar(const Codigo& codigo) override;
    std::vector<Viagem> listarPorViajante(const Codigo& codigoViajante) override;
    double calcularCustoTotal(const Codigo& codigoViagem);

private:
    /**
     * @brief Cria a tabela de viagens no banco de dados.
     */
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

    /**
     * @brief Calcula o número de dias entre duas datas.
     * @param dataInicio Data inicial.
     * @param dataFim Data final.
     * @return Número de dias entre as datas.
     */
    int calcularDiasEntreDatas(const std::string& dataInicio, const std::string& dataFim);
};

#endif // REPOSITORIO_VIAGEM_HPP
