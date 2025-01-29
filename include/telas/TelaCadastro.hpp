// include/telas/TelaCadastro.hpp
#ifndef TELA_CADASTRO_HPP
#define TELA_CADASTRO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"

class TelaCadastro : public TelaBase {
private:
    ServicoAutenticacao* servico;

public:
    TelaCadastro(ServicoAutenticacao* srv);
    void mostrar() override;
    Viajante* executar();
};

#endif