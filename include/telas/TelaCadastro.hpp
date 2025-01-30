#ifndef TELA_CADASTRO_HPP
#define TELA_CADASTRO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"
#include "../entidades/Viajante.hpp"
#include "../entidades/Conta.hpp"
#include "../dominios/Nome.hpp"

/**
 * @brief Classe respons�vel pela interface gr�fica de cadastro de usu�rios
 * 
 * Esta classe gerencia a tela de cadastro de novos usu�rios no sistema, incluindo
 * a apresenta��o do formul�rio e o processamento dos dados inseridos.
 * Herda funcionalidades b�sicas de TelaBase.
 * 
 * @see TelaBase
 * @see ServicoAutenticacao
 */
class TelaCadastro : public TelaBase {
private:
    /**
     * @brief Ponteiro para o servi�o de autentica��o
     */
    ServicoAutenticacao* servico;

    /**
     * @brief Ponteiro para janela modal de cadastro
     */
    WINDOW* modalCadastro;
    
    /**
     * @brief Tamanho m�ximo permitido para o nome do usu�rio
     */
    static const int TAM_MAX_NOME = 20;

    /**
     * @brief Tamanho m�ximo permitido para o c�digo do usu�rio
     */
    static const int TAM_MAX_CODIGO = 6;

    /**
     * @brief Tamanho m�ximo permitido para a senha do usu�rio
     */
    static const int TAM_MAX_SENHA = 5;
    
    /**
     * @brief Desenha a interface do modal de cadastro
     */
    void desenharModal();

    /**
     * @brief Processa os dados inseridos no formul�rio de cadastro
     * @return true se o cadastro foi bem-sucedido, false caso contr�rio
     */
    bool processarCadastro();

public:
    /**
     * @brief Construtor da classe
     * @param srv Ponteiro para o servi�o de autentica��o
     */
    TelaCadastro(ServicoAutenticacao* srv);

    /**
     * @brief Destrutor da classe
     */
    ~TelaCadastro();
    
    /**
     * @brief Exibe a tela de cadastro
     * @override Sobrescreve m�todo da classe base
     */
    void mostrar() override;

    /**
     * @brief Executa o fluxo de cadastro
     * @return true se a opera��o foi conclu�da com sucesso, false caso contr�rio
     */
    bool executar();
};

#endif