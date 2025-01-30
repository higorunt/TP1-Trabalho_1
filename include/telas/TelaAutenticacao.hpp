#ifndef TELA_AUTENTICACAO_HPP
#define TELA_AUTENTICACAO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"
#include "../entidades/Viajante.hpp"
#include "../entidades/Conta.hpp"
#include "../dominios/Nome.hpp"
#include <string>

class TelaAutenticacao : public TelaBase {
private:
    ServicoAutenticacao* servico;
    WINDOW* painelLogin;
    
    void desenharLogo();
    void desenharCamposLogin();
    void mostrarModalCadastro();
    
    // Dimensões e posições dos elementos
    struct {
        int altura = 6;
        int largura = 40;
        int logoY = 2;
        int camposCentralX;
        int camposY;
    } layout;
    
public:
    TelaAutenticacao(ServicoAutenticacao* srv);
    ~TelaAutenticacao();
    
    void mostrar() override;
    Viajante* fazerLogin();
    
    static const int TAM_MAX_CODIGO = 6;
    static const int TAM_MAX_SENHA = 5;
};

#endif