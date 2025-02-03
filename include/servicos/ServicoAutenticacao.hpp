//221006440
// include/servicos/ServicoAutenticacao.hpp
#ifndef SERVICO_AUTENTICACAO_HPP
#define SERVICO_AUTENTICACAO_HPP

#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

/**
 * @brief Classe que gerencia a autenticação de viajantes no sistema.
 */
class ServicoAutenticacao {
private:
    IRepositorio<Viajante, Codigo>* repositorio;

public:
    /**
     * @brief Construtor do serviço de autenticação.
     * @param repo Repositório de viajantes.
     */
    ServicoAutenticacao(IRepositorio<Viajante, Codigo>* repo);
    ~ServicoAutenticacao();

    /**
     * @brief Autentica um viajante no sistema.
     * @param codigo Código do viajante.
     * @param senha Senha do viajante.
     * @return Ponteiro para o viajante se autenticado, nullptr caso contrário.
     */
    Viajante* autenticar(const Codigo& codigo, const Senha& senha);

    /**
     * @brief Cadastra um novo viajante.
     * @param viajante Viajante a ser cadastrado.
     * @return true se cadastrado com sucesso.
     */
    bool cadastrar(const Viajante& viajante);
};

#endif