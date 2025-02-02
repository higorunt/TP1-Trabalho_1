#ifndef SERVICO_HOSPEDAGEM_HPP
#define SERVICO_HOSPEDAGEM_HPP

#include "../entidades/Hospedagem.hpp"
#include "../repositorios/RepositorioHospedagem.hpp"

class ServicoHospedagem
{
private:
    RepositorioHospedagem repositorio;

public:
    ServicoHospedagem(const std::string &caminhoBD);

    bool criarHospedagem(const Hospedagem &hospedagem);
    Hospedagem *lerHospedagem(const Codigo &codigo);
    bool atualizarHospedagem(const Hospedagem &hospedagem);
    bool excluirHospedagem(const Codigo &codigo);
    std::vector<Hospedagem> listarHospedagens(const Codigo &destinoCodigo);
};

#endif // SERVICO_HOSPEDAGEM_HPP