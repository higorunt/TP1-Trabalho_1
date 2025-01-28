// include/apresentacao/TelaLogin.hpp
#ifndef TELA_LOGIN_HPP
#define TELA_LOGIN_HPP

#include <curses.h>
#include "../interfaces/IAutenticacaoService.hpp"

class TelaLogin {
private:
    IAutenticacaoService* service;
    WINDOW* janela;
    
    void inicializarCurses();
    void finalizarCurses();
    void exibirMensagem(const char* mensagem);

public:
    explicit TelaLogin(IAutenticacaoService* service);
    ~TelaLogin();
    
    Viajante* executar();
};

#endif