//221006404
#ifndef REPOSITORIO_DESTINO_HPP
#define REPOSITORIO_DESTINO_HPP

#include "../../include/entidades/Destino.hpp"
#include "../../include/repositorios/RepositorioBase.hpp"
#include <vector>
#include <string>

/**
 * @brief Repositório para gerenciamento de Destinos no sistema.
 * 
 * Implementa operações CRUD e consultas específicas para a entidade Destino.
 */
class RepositorioDestino : public RepositorioBase {
public:
    /**
     * @brief Construtor do repositório.
     * @param caminhoBD Caminho do banco de dados.
     */
    RepositorioDestino(const std::string& caminhoBD);

    /**
     * @brief Salva um novo destino.
     * @param destino Destino a ser salvo.
     * @return true se salvou com sucesso, false caso contrário.
     */
    bool salvar(const Destino& destino);

    /**
     * @brief Busca um destino pelo código.
     * @param codigo Código do destino.
     * @return Ponteiro para o destino encontrado ou nullptr.
     */
    Destino* buscar(const Codigo& codigo);

    /**
     * @brief Atualiza um destino existente.
     * @param destino Destino com dados atualizados.
     * @return true se atualizou com sucesso, false caso contrário.
     */
    bool atualizar(const Destino& destino);

    /**
     * @brief Remove um destino.
     * @param codigo Código do destino a ser removido.
     * @return true se removeu com sucesso, false caso contrário.
     */
    bool deletar(const Codigo& codigo);

    /**
     * @brief Lista destinos de uma viagem específica.
     * @param codigoViagem Código da viagem.
     * @return Vector com os destinos da viagem.
     */
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

#endif
