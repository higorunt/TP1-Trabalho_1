#ifndef TELA_AUTENTICACAO_HPP
#define TELA_AUTENTICACAO_HPP
//221006440
/**
 * @brief Classe que gerencia a interface de autentica��o.
 * 
 * Respons�vel pela tela de login e registro de usu�rios.
 */

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

class TelaAutenticacao : public TelaBase {
private:
    static const int TAM_MAX_CODIGO = 6;  // Tamanho m�ximo do c�digo
    static const int TAM_MAX_SENHA = 5;   // Tamanho m�ximo da senha

    ServicoAutenticacao* servico;
    WINDOW* painelLogin;
    
    struct {
        int logoY = 1;
        int altura = 5;
        int largura = 40;
        int camposCentralX;
        int camposY;
    } layout;

    void desenharLogo();
    void desenharCamposLogin();
    void mostrarModalCadastro();

public:
    TelaAutenticacao(ServicoAutenticacao* srv);
    ~TelaAutenticacao();

    void mostrar() override;
    Viajante* fazerLogin();
};

#endif // TELA_AUTENTICACAO_HPP