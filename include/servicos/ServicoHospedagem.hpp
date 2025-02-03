//221006404

#ifndef SERVICO_HOSPEDAGEM_HPP
#define SERVICO_HOSPEDAGEM_HPP

#include "../repositorios/RepositorioHospedagem.hpp"

/**
 * @brief Classe que gerencia as regras de neg�cio relacionadas a Hospedagens.
 */
class ServicoHospedagem {
public:
    /**
     * @brief Construtor do servi�o de hospedagem.
     * @param rep Reposit�rio de hospedagens.
     */
    explicit ServicoHospedagem(RepositorioHospedagem* rep);

    /**
     * @brief Cria uma nova hospedagem.
     * @param hospedagem Hospedagem a ser criada.
     * @return true se criada com sucesso.
     */
    bool criarHospedagem(const Hospedagem& hospedagem);

    /**
     * @brief Busca uma hospedagem pelo c�digo.
     * @param codigo C�digo da hospedagem.
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
     * @brief Exclui uma hospedagem pelo c�digo.
     * @param codigo C�digo da hospedagem.
     * @return true se exclu�da com sucesso.
     */
    bool excluirHospedagem(const Codigo& codigo);

    /**
     * @brief Busca uma hospedagem pelo destino.
     * @param codigoDestino C�digo do destino.
     * @return Ponteiro para hospedagem encontrada ou nullptr.
     */
    Hospedagem* buscarPorDestino(const Codigo& codigoDestino);

private:
    RepositorioHospedagem* repositorioHospedagem;
};

#endif
