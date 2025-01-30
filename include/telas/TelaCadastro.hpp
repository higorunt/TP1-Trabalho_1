#ifndef TELA_CADASTRO_HPP
#define TELA_CADASTRO_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAutenticacao.hpp"
#include "../entidades/Viajante.hpp"
#include "../entidades/Conta.hpp"
#include "../dominios/Nome.hpp"

class TelaCadastro : public TelaBase {
private:
    ServicoAutenticacao* servico;
    WINDOW* modalCadastro;
    
    static const int TAM_MAX_NOME = 20;
    static const int TAM_MAX_CODIGO = 6;
    static const int TAM_MAX_SENHA = 5;
    
    void desenharModal();
    bool processarCadastro();

public:
    TelaCadastro(ServicoAutenticacao* srv);
    ~TelaCadastro();
    
    void mostrar() override;
    bool executar();
};

#endif