#ifndef REPOSITORIO_CONTA_HPP
#define REPOSITORIO_CONTA_HPP

#include "../entidades/Conta.hpp"
#include "RepositorioBase.hpp"
#include <vector>

class RepositorioConta : public RepositorioBase
{
public:
    RepositorioConta(const std::string &caminhoBD);

    bool criarConta(const Conta &conta);
    Conta *lerConta(const Codigo &codigo);
    bool atualizarConta(const Conta &conta);
    bool excluirConta(const Codigo &codigo);
    std::vector<Conta> listarContas();

private:
    Conta mapearParaEntidade(sqlite3_stmt *stmt);
};

#endif // REPOSITORIO_CONTA_HPP