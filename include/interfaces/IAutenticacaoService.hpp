// include/interfaces/IAutenticacaoService.hpp
#ifndef IAUTENTICACAO_SERVICE_HPP
#define IAUTENTICACAO_SERVICE_HPP

#include "../entidades/Viajante.hpp"

class IAutenticacaoService {
public:
    virtual ~IAutenticacaoService() = default;
    virtual Viajante* autenticar(const Codigo& codigo, const Senha& senha) = 0;
    virtual bool cadastrar(const Viajante& viajante) = 0;
};

#endif