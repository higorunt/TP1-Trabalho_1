// include/services/AutenticacaoService.hpp
#ifndef AUTENTICACAO_SERVICE_HPP
#define AUTENTICACAO_SERVICE_HPP

#include "../interfaces/IAutenticacaoService.hpp"
#include "../interfaces/IAutenticacaoRepository.hpp"

class AutenticacaoService : public IAutenticacaoService {
private:
    IAutenticacaoRepository* repository;

public:
    explicit AutenticacaoService(IAutenticacaoRepository* repository);
    ~AutenticacaoService() override;
    
    Viajante* autenticar(const Codigo& codigo, const Senha& senha) override;
    bool cadastrar(const Viajante& viajante) override;
};

#endif