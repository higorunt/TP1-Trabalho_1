#ifndef REPOSITORIO_VIAGEM_HPP
#define REPOSITORIO_VIAGEM_HPP

#include "../entidades/Viagem.hpp"
#include "RepositorioBase.hpp"
#include <vector>

class RepositorioViagem : public RepositorioBase
{
public:
    RepositorioViagem(const std::string &caminhoBD);

    bool criarViagem(const Viagem &viagem);
    Viagem *lerViagem(const Codigo &codigo);
    bool atualizarViagem(const Viagem &viagem);
    bool excluirViagem(const Codigo &codigo);
    std::vector<Viagem> listarViagens(const Codigo &viajanteCodigo);

private:
    Viagem mapearParaEntidade(sqlite3_stmt *stmt);
};

#endif // REPOSITORIO_VIAGEM_HPP