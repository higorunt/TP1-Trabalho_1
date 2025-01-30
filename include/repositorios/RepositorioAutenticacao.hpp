// include/repositorios/RepositorioAutenticacao.hpp
#ifndef REPOSITORIO_AUTENTICACAO_HPP
#define REPOSITORIO_AUTENTICACAO_HPP

#include "RepositorioBase.hpp"
#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

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