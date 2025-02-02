#ifndef SERVICO_DESTINO_HPP
#define SERVICO_DESTINO_HPP

#include "../../include/entidades/Destino.hpp"
#include "../../include/repositorios/RepositorioDestino.hpp"
#include "../../include/dominios/Codigo.hpp"
#include <vector>
#include <string>

/**
 * @brief Classe de serviço para operações com Destino.
 */
class ServicoDestino {
private:
    RepositorioDestino* repositorioDestino;
public:
    /**
     * @brief Construtor do serviço de destino.
     * @param repDestino Ponteiro para o repositório de destino.
     */
    ServicoDestino(RepositorioDestino* repDestino);

    /**
     * @brief Cria um novo destino.
     * @param destino Objeto Destino a ser criado.
     * @return true se criado com sucesso, false caso contrário.
     */
    bool criarDestino(const Destino& destino);

    /**
     * @brief Busca um destino pelo seu código.
     * @param codigo Código do destino.
     * @return Ponteiro para o Destino encontrado, ou nullptr.
     */
    Destino* buscarDestino(const Codigo& codigo);

    /**
     * @brief Atualiza um destino.
     * @param destino Objeto Destino com os novos dados.
     * @return true se atualizado com sucesso, false caso contrário.
     */
    bool atualizarDestino(const Destino& destino);

    /**
     * @brief Exclui um destino.
     * @param codigo Código do destino.
     * @return true se excluído com sucesso, false caso contrário.
     */
    bool excluirDestino(const Codigo& codigo);

    /**
     * @brief Lista todos os destinos associados a uma determinada viagem.
     * @param codigoViagem Código da viagem.
     * @return Vetor com os destinos encontrados.
     */
    std::vector<Destino> listarPorViagem(const Codigo& codigoViagem);
};

#endif // SERVICO_DESTINO_HPP
