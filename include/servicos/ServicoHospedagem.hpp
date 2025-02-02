#ifndef SERVICO_HOSPEDAGEM_HPP
#define SERVICO_HOSPEDAGEM_HPP

#include "../repositorios/RepositorioHospedagem.hpp"

class ServicoHospedagem {
public:
    explicit ServicoHospedagem(RepositorioHospedagem* rep);
    bool criarHospedagem(const Hospedagem& hospedagem);
    Hospedagem* buscarHospedagem(const Codigo& codigo);
    bool atualizarHospedagem(const Hospedagem& hospedagem);
    bool excluirHospedagem(const Codigo& codigo);
    Hospedagem* buscarPorDestino(const Codigo& codigoDestino);

private:
    RepositorioHospedagem* repositorioHospedagem;
};

#endif
