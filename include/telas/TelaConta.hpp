#ifndef TELA_CONTA_HPP
#define TELA_CONTA_HPP

#include "../servicos/ServicoConta.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

class TelaConta
{
private:
    ServicoConta *servico;
    WINDOW *painelConta;

    void desenharModal();
    bool processarConta();

public:
    TelaConta(ServicoConta *srv);
    ~TelaConta();

    void mostrar();
    bool executar();
};

#endif // TELA_CONTA_HPP