//221006404
// include/repositorios/RepositorioAutenticacao.hpp
#ifndef REPOSITORIO_AUTENTICACAO_HPP
#define REPOSITORIO_AUTENTICACAO_HPP

#include "RepositorioBase.hpp"
#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

/**
 * @brief Reposit�rio para autentica��o de viajantes no sistema.
 * 
 * Implementa opera��es CRUD espec�ficas para autentica��o de viajantes.
 */
class RepositorioAutenticacao : 
    public RepositorioBase, 
    public IRepositorio<Viajante, Codigo> {
        
public:
    /**
     * @brief Construtor do reposit�rio.
     * @param caminho Caminho do banco de dados.
     */
    RepositorioAutenticacao(const std::string& caminho);
    
    /**
     * @brief Busca um viajante pelo c�digo.
     * @param codigo C�digo do viajante.
     * @return Ponteiro para o viajante encontrado ou nullptr.
     */
    Viajante* buscar(const Codigo& codigo) override;

    /**
     * @brief Salva um novo viajante.
     * @param viajante Viajante a ser salvo.
     * @return true se salvou com sucesso, false caso contr�rio.
     */
    bool salvar(const Viajante& viajante) override;

    /**
     * @brief Atualiza um viajante existente.
     * @param viajante Viajante com dados atualizados.
     * @return true se atualizou com sucesso, false caso contr�rio.
     */
    bool atualizar(const Viajante& viajante) override;

    /**
     * @brief Remove um viajante.
     * @param codigo C�digo do viajante a ser removido.
     * @return true se removeu com sucesso, false caso contr�rio.
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