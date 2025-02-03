//221006404
// include/repositorios/RepositorioAutenticacao.hpp
#ifndef REPOSITORIO_AUTENTICACAO_HPP
#define REPOSITORIO_AUTENTICACAO_HPP

#include "RepositorioBase.hpp"
#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

/**
 * @brief Repositório para autenticação de viajantes no sistema.
 * 
 * Implementa operações CRUD específicas para autenticação de viajantes.
 */
class RepositorioAutenticacao : 
    public RepositorioBase, 
    public IRepositorio<Viajante, Codigo> {
        
public:
    /**
     * @brief Construtor do repositório.
     * @param caminho Caminho do banco de dados.
     */
    RepositorioAutenticacao(const std::string& caminho);
    
    /**
     * @brief Busca um viajante pelo código.
     * @param codigo Código do viajante.
     * @return Ponteiro para o viajante encontrado ou nullptr.
     */
    Viajante* buscar(const Codigo& codigo) override;

    /**
     * @brief Salva um novo viajante.
     * @param viajante Viajante a ser salvo.
     * @return true se salvou com sucesso, false caso contrário.
     */
    bool salvar(const Viajante& viajante) override;

    /**
     * @brief Atualiza um viajante existente.
     * @param viajante Viajante com dados atualizados.
     * @return true se atualizou com sucesso, false caso contrário.
     */
    bool atualizar(const Viajante& viajante) override;

    /**
     * @brief Remove um viajante.
     * @param codigo Código do viajante a ser removido.
     * @return true se removeu com sucesso, false caso contrário.
     */
    bool deletar(const Codigo& codigo) override;

protected:
    /**
     * @brief Cria a tabela de viajantes no banco de dados.
     */
    void criarTabela() {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS viajantes (
                codigo TEXT PRIMARY KEY,
                nome TEXT NOT NULL,
                senha TEXT NOT NULL
            );
        )";
        executarSQL(sql);
    }
};

#endif