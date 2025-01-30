// include/servicos/ServicoAutenticacao.hpp
#ifndef SERVICO_AUTENTICACAO_HPP
#define SERVICO_AUTENTICACAO_HPP

#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

/**
 * @brief Serviço responsável pela autenticação e cadastro de viajantes
 * 
 * Esta classe fornece funcionalidades para autenticar viajantes existentes
 * e cadastrar novos viajantes no sistema.
 */
class ServicoAutenticacao {
private:
    /**
     * @brief Repositório de viajantes
     */
    IRepositorio<Viajante, Codigo>* repositorio;

public:
    /**
     * @brief Construtor da classe ServicoAutenticacao
     * @param repo Ponteiro para o repositório de viajantes
     */
    ServicoAutenticacao(IRepositorio<Viajante, Codigo>* repo);

    /**
     * @brief Destrutor da classe ServicoAutenticacao
     */
    ~ServicoAutenticacao();

    /**
     * @brief Autentica um viajante no sistema
     * @param codigo Código do viajante
     * @param senha Senha do viajante
     * @return Ponteiro para o viajante autenticado ou nullptr se a autenticação falhar
     */
    Viajante* autenticar(const Codigo& codigo, const Senha& senha);

    /**
     * @brief Cadastra um novo viajante no sistema
     * @param viajante Objeto Viajante a ser cadastrado
     * @return true se o cadastro for bem-sucedido, false caso contrário
     */
    bool cadastrar(const Viajante& viajante);
};

#endif