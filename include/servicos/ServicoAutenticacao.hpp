// include/servicos/ServicoAutenticacao.hpp
#ifndef SERVICO_AUTENTICACAO_HPP
#define SERVICO_AUTENTICACAO_HPP

#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

class ServicoAutenticacao {
private:
    IRepositorio<Viajante, Codigo>* repositorio;

public:
    ServicoAutenticacao(IRepositorio<Viajante, Codigo>* repo);
    ~ServicoAutenticacao();

    Viajante* autenticar(const Codigo& codigo, const Senha& senha);
    bool cadastrar(const Viajante& viajante);
};

#endif