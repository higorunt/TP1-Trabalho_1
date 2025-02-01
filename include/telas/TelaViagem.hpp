#ifndef TELA_VIAGEM_HPP
#define TELA_VIAGEM_HPP

#include "../../include/servicos/ServicoViagem.hpp"
#include "../../include/entidades/Viagem.hpp"
#include "../../include/telas/TelaBase.hpp"
#include <string>

/**
 * @class TelaViagem
 * @brief Classe respons�vel por gerenciar a interface de usu�rio para opera��es relacionadas a viagens.
 *
 * Esta classe permite ao usu�rio criar, visualizar, atualizar e excluir viagens, interagindo com o servi�o de viagens.
 */
class TelaViagem : public TelaBase
{
private:
    ServicoViagem *servico; ///< Ponteiro para o servi�o de viagens.
    WINDOW *painelViagem;   ///< Janela do painel de viagem.

    /**
     * @brief Desenha o modal da tela de viagem.
     */
    void desenharModal();

    /**
     * @brief Processa a entrada do usu�rio para criar ou atualizar uma viagem.
     * @return true se a opera��o foi bem-sucedida, false caso contr�rio.
     */
    bool processarViagem();

public:
    /**
     * @brief Construtor da classe TelaViagem.
     * @param srv Ponteiro para o servi�o de viagens.
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
     * @return true se a opera��o foi bem-sucedida, false caso contr�rio.
     */
    bool executar();
};

#endif // TELA_VIAGEM_HPP