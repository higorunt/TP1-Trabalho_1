// include/telas/TelaAutenticacao.hpp
#ifndef TELA_AUTENTICACAO_HPP
#define TELA_AUTENTICACAO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"

class TelaAutenticacao : public TelaBase {
private:
    ServicoAutenticacao* servico;
    void mostrarErro(const std::string& erro);

public:
    TelaAutenticacao(ServicoAutenticacao* servico);
    
    void mostrar() override;
    Viajante* fazerLogin();
};

#endif