#ifndef TELA_CADASTRO_HPP
#define TELA_CADASTRO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"
#include "../entidades/Viajante.hpp"
#include "../entidades/Conta.hpp"
#include "../dominios/Nome.hpp"

/**
 * @brief Classe responsável pela interface gráfica de cadastro de usuários
 * 
 * Esta classe gerencia a tela de cadastro de novos usuários no sistema, incluindo
 * a apresentação do formulário e o processamento dos dados inseridos.
 * Herda funcionalidades básicas de TelaBase.
 * 
 * @see TelaBase
 * @see ServicoAutenticacao
 */
class TelaCadastro : public TelaBase {
private:
    /**
     * @brief Ponteiro para o serviço de autenticação
     */
    ServicoAutenticacao* servico;

    /**
     * @brief Ponteiro para janela modal de cadastro
     */
    WINDOW* modalCadastro;
    
    /**
     * @brief Tamanho máximo permitido para o nome do usuário
     */
    static const int TAM_MAX_NOME = 20;

    /**
     * @brief Tamanho máximo permitido para o código do usuário
     */
    static const int TAM_MAX_CODIGO = 6;

    /**
     * @brief Tamanho máximo permitido para a senha do usuário
     */
    static const int TAM_MAX_SENHA = 5;
    
    /**
     * @brief Desenha a interface do modal de cadastro
     */
    void desenharModal();

    /**
     * @brief Processa os dados inseridos no formulário de cadastro
     * @return true se o cadastro foi bem-sucedido, false caso contrário
     */
    bool processarCadastro();

public:
    /**
     * @brief Construtor da classe
     * @param srv Ponteiro para o serviço de autenticação
     */
    TelaCadastro(ServicoAutenticacao* srv);

    /**
     * @brief Destrutor da classe
     */
    ~TelaCadastro();
    
    /**
     * @brief Exibe a tela de cadastro
     * @override Sobrescreve método da classe base
     */
    void mostrar() override;

    /**
     * @brief Executa o fluxo de cadastro
     * @return true se a operação foi concluída com sucesso, false caso contrário
     */
    bool executar();
};

#endif