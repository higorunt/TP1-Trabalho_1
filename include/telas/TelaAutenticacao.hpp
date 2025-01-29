// include/telas/TelaAutenticacao.hpp
#ifndef TELA_AUTENTICACAO_HPP
#define TELA_AUTENTICACAO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"

class TelaAutenticacao : public TelaBase {
private:
    ServicoAutenticacao* servico;

public:
    TelaAutenticacao(ServicoAutenticacao* servico);
    
    void mostrar() override;
    Viajante* fazerLogin();
};

#endif