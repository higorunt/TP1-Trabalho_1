#ifndef TELA_AUTENTICACAO_HPP
#define TELA_AUTENTICACAO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

class TelaAutenticacao : public TelaBase {
private:
    static const int TAM_MAX_CODIGO = 6;  // Tamanho máximo do código
    static const int TAM_MAX_SENHA = 5;   // Tamanho máximo da senha

    ServicoAutenticacao* servico;
    WINDOW* painelLogin;
    
    struct {
        int logoY = 5;
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