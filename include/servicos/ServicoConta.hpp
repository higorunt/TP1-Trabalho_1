#ifndef SERVICO_CONTA_HPP
#define SERVICO_CONTA_HPP

#include "../entidades/Conta.hpp"
#include "../repositorios/RepositorioConta.hpp"

class ServicoConta
{
private:
    RepositorioConta repositorio;

public:
    ServicoConta(const std::string &caminhoBD);

    bool criarConta(const Conta &conta);
    Conta *lerConta(const Codigo &codigo);
    bool atualizarConta(const Conta &conta);
    bool excluirConta(const Codigo &codigo);
    std::vector<Conta> listarContas();
};

#endif // SERVICO_CONTA_HPP