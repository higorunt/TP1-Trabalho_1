#ifndef REPOSITORIO_HOSPEDAGEM_HPP
#define REPOSITORIO_HOSPEDAGEM_HPP

#include "../entidades/Hospedagem.hpp"
#include "RepositorioBase.hpp"
#include <vector>

class RepositorioHospedagem : public RepositorioBase
{
public:
    RepositorioHospedagem(const std::string &caminhoBD);

    bool criarHospedagem(const Hospedagem &hospedagem);
    Hospedagem *lerHospedagem(const Codigo &codigo);
    bool atualizarHospedagem(const Hospedagem &hospedagem);
    bool excluirHospedagem(const Codigo &codigo);
    std::vector<Hospedagem> listarHospedagens(const Codigo &destinoCodigo);

private:
    Hospedagem mapearParaEntidade(sqlite3_stmt *stmt);
};

#endif // REPOSITORIO_HOSPEDAGEM_HPP