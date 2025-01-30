// include/servicos/ServicoAutenticacao.hpp
#ifndef SERVICO_AUTENTICACAO_HPP
#define SERVICO_AUTENTICACAO_HPP

#include "../interfaces/IRepositorio.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

/**
 * @brief Servi�o respons�vel pela autentica��o e cadastro de viajantes
 * 
 * Esta classe fornece funcionalidades para autenticar viajantes existentes
 * e cadastrar novos viajantes no sistema.
 */
class ServicoAutenticacao {
private:
    /**
     * @brief Reposit�rio de viajantes
     */
    IRepositorio<Viajante, Codigo>* repositorio;

public:
    /**
     * @brief Construtor da classe ServicoAutenticacao
     * @param repo Ponteiro para o reposit�rio de viajantes
     */
    ServicoAutenticacao(IRepositorio<Viajante, Codigo>* repo);

    /**
     * @brief Destrutor da classe ServicoAutenticacao
     */
    ~ServicoAutenticacao();

    /**
     * @brief Autentica um viajante no sistema
     * @param codigo C�digo do viajante
     * @param senha Senha do viajante
     * @return Ponteiro para o viajante autenticado ou nullptr se a autentica��o falhar
     */
    Viajante* autenticar(const Codigo& codigo, const Senha& senha);

    /**
     * @brief Cadastra um novo viajante no sistema
     * @param viajante Objeto Viajante a ser cadastrado
     * @return true se o cadastro for bem-sucedido, false caso contr�rio
     */
    bool cadastrar(const Viajante& viajante);
};

#endif