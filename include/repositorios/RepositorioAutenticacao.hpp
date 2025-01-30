// include/repositorios/RepositorioAutenticacao.hpp
#ifndef REPOSITORIO_AUTENTICACAO_HPP
#define REPOSITORIO_AUTENTICACAO_HPP

#include "RepositorioBase.hpp"
#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

/**
 * @brief Classe responsável pelo gerenciamento de autenticação de viajantes no repositório
 * 
 * Esta classe herda de RepositorioBase e implementa a interface IRepositorio
 * para fornecer operações CRUD (Create, Read, Update, Delete) específicas para Viajantes
 * 
 * @see RepositorioBase
 * @see IRepositorio
 * @see Viajante
 * @see Codigo
 */
class RepositorioAutenticacao : 
    public RepositorioBase, 
    public IRepositorio<Viajante, Codigo> {
        
public:
    RepositorioAutenticacao(const std::string& caminho);
    
    Viajante* buscar(const Codigo& codigo) override;
    bool salvar(const Viajante& viajante) override;
    bool atualizar(const Viajante& viajante) override;
    bool deletar(const Codigo& codigo) override;
};

#endif