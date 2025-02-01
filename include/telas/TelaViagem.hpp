#ifndef TELA_VIAGEM_HPP
#define TELA_VIAGEM_HPP

#include "../../include/servicos/ServicoViagem.hpp"
#include "../../include/entidades/Viagem.hpp"
#include "../../include/telas/TelaBase.hpp"
#include <string>

/**
 * @class TelaViagem
 * @brief Classe responsável por gerenciar a interface de usuário para operações relacionadas a viagens.
 *
 * Esta classe permite ao usuário criar, visualizar, atualizar e excluir viagens, interagindo com o serviço de viagens.
 */
class TelaViagem : public TelaBase
{
private:
    ServicoViagem *servico; ///< Ponteiro para o serviço de viagens.
    WINDOW *painelViagem;   ///< Janela do painel de viagem.

    /**
     * @brief Desenha o modal da tela de viagem.
     */
    void desenharModal();

    /**
     * @brief Processa a entrada do usuário para criar ou atualizar uma viagem.
     * @return true se a operação foi bem-sucedida, false caso contrário.
     */
    bool processarViagem();

public:
    /**
     * @brief Construtor da classe TelaViagem.
     * @param srv Ponteiro para o serviço de viagens.
     */
    TelaViagem(ServicoViagem *srv);

    /**
     * @brief Destrutor da classe TelaViagem.
     */
    ~TelaViagem();

    /**
     * @brief Exibe a tela de viagem.
     */
    void mostrar();

    /**
     * @brief Executa a tela de viagem.
     * @return true se a operação foi bem-sucedida, false caso contrário.
     */
    bool executar();
};

#endif // TELA_VIAGEM_HPP