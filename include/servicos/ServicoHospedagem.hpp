//221006404

#ifndef SERVICO_HOSPEDAGEM_HPP
#define SERVICO_HOSPEDAGEM_HPP

#include "../repositorios/RepositorioHospedagem.hpp"

/**
 * @brief Classe que gerencia as regras de negócio relacionadas a Hospedagens.
 */
class ServicoHospedagem {
public:
    /**
     * @brief Construtor do serviço de hospedagem.
     * @param rep Repositório de hospedagens.
     */
    explicit ServicoHospedagem(RepositorioHospedagem* rep);

    /**
     * @brief Cria uma nova hospedagem.
     * @param hospedagem Hospedagem a ser criada.
     * @return true se criada com sucesso.
     */
    bool criarHospedagem(const Hospedagem& hospedagem);

    /**
     * @brief Busca uma hospedagem pelo código.
     * @param codigo Código da hospedagem.
     * @return Ponteiro para hospedagem encontrada ou nullptr.
     */
    Hospedagem* buscarHospedagem(const Codigo& codigo);

    /**
     * @brief Atualiza uma hospedagem existente.
     * @param hospedagem Hospedagem a ser atualizada.
     * @return true se atualizada com sucesso.
     */
    bool atualizarHospedagem(const Hospedagem& hospedagem);

    /**
     * @brief Exclui uma hospedagem pelo código.
     * @param codigo Código da hospedagem.
     * @return true se excluída com sucesso.
     */
    bool excluirHospedagem(const Codigo& codigo);

    /**
     * @brief Busca uma hospedagem pelo destino.
     * @param codigoDestino Código do destino.
     * @return Ponteiro para hospedagem encontrada ou nullptr.
     */
    Hospedagem* buscarPorDestino(const Codigo& codigoDestino);

private:
    RepositorioHospedagem* repositorioHospedagem;
};

#endif
