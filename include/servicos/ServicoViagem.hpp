//221006440
#ifndef SERVICO_VIAGEM_HPP
#define SERVICO_VIAGEM_HPP

#include "../repositorios/RepositorioViagem.hpp"
#include "../repositorios/RepositorioDestino.hpp"
#include "../entidades/Viagem.hpp"
#include "../entidades/Destino.hpp"
#include <vector>
#include <memory>

/**
 * @brief Classe que gerencia as regras de neg�cio relacionadas a Viagens.
 */
class ServicoViagem {
private:
    RepositorioViagem* repositorioViagem;
    RepositorioDestino* repositorioDestino;

public:
    /**
     * @brief Construtor do servi�o de viagem.
     * @param repViagem Reposit�rio de viagens.
     * @param repDestino Reposit�rio de destinos.
     */
    ServicoViagem(RepositorioViagem* repViagem, RepositorioDestino* repDestino)
        : repositorioViagem(repViagem), repositorioDestino(repDestino) {}

    /**
     * @brief Cria uma nova viagem.
     * @param viagem Viagem a ser criada.
     * @return true se criada com sucesso.
     */
    bool criarViagem(const Viagem& viagem);

    Viagem* buscarViagem(const Codigo& codigo);
    bool atualizarViagem(const Viagem& viagem);
    bool excluirViagem(const Codigo& codigo);

    /**
     * @brief Calcula o custo total da viagem.
     * @param codigoViagem C�digo da viagem.
     * @return Valor total da viagem.
     */
    double calcularCustoViagem(const Codigo& codigoViagem);

    std::vector<Viagem> listarViagensPorViajante(const Codigo& codigoViajante);
    std::vector<Destino> listarDestinosPorViagem(const Codigo& codigoViagem);

    bool possuiDestinos(const Codigo& codigoViagem);
};

#endif