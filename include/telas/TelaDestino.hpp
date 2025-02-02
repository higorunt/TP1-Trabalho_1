#ifndef TELA_DESTINO_HPP
#define TELA_DESTINO_HPP

#include "../../include/telas/TelaBase.hpp"
#include "../../include/servicos/ServicoDestino.hpp"
#include "../../include/servicos/ServicoViagem.hpp"
#include "../../include/entidades/Destino.hpp"
#include "../../include/dominios/Codigo.hpp"
#include "../../include/entidades/Viajante.hpp"
#include <string>
#include <vector>

/**
 * @brief TelaDestino: Gerencia a interface para operações com Destino.
 *
 * Permite cadastrar, listar, editar e excluir destinos. No fluxo de cadastro,
 * o usuário primeiro seleciona uma viagem dentre as viagens cadastradas (do usuário real)
 * e, em seguida, informa os dados do destino a ser cadastrado. O código do destino é
 * gerado automaticamente.
 */
class TelaDestino : public TelaBase {
private:
    ServicoDestino* servicoDestino;  ///< Serviço de destino.
    ServicoViagem* servicoViagem;    ///< Serviço de viagem (para listar as viagens reais do usuário).
    Viajante* viajante;              ///< Viajante autenticado.
    WINDOW* painelDestino;           ///< Janela para exibição do formulário.
    
    // Layout do formulário
    struct {
        int altura = 16;
        int largura = 70;
        int centralX;
        int centralY;
    } layout;
    
    // Constantes para tamanho dos campos
    static const int TAM_MAX_NOME = 30;      ///< Tamanho máximo para o nome do destino.
    static const int TAM_MAX_DATA = 8;       ///< Tamanho máximo para datas (ex: "05-07-22").
    static const int TAM_MAX_AVALIACAO = 1;    ///< Tamanho máximo para a avaliação (1 dígito: 1-5).
    
    /**
     * @brief Exibe a lista de viagens do usuário e permite a seleção.
     * @return Código da viagem selecionada ou um código "sentinela" (ex: "000000") se cancelado.
     */
    Codigo selecionarViagem();
    
    /**
     * @brief Desenha o formulário para cadastro de destino, exibindo informações da viagem selecionada.
     * @param infoViagem Informação da viagem (por exemplo, "Viagem: TRI123 - Nome da Viagem").
     */
    void desenharFormulario(const std::string& infoViagem);
    
    /**
     * @brief Processa os dados inseridos no formulário e cria o destino.
     * @param codigoViagem Código da viagem selecionada (foreign key).
     * @return true se o cadastro ocorrer com sucesso, false caso contrário.
     */
    bool processarDestino(const Codigo& codigoViagem);
    
    // (Outras funcionalidades, como listar, editar e excluir destinos, podem ser implementadas posteriormente.)
    
public:
    /**
     * @brief Construtor da TelaDestino.
     * @param srvDestino Serviço de destino.
     * @param srvViagem Serviço de viagem.
     * @param v Viajante autenticado.
     */
    TelaDestino(ServicoDestino* srvDestino, ServicoViagem* srvViagem, Viajante* v);
    
    /**
     * @brief Destrutor da TelaDestino.
     */
    ~TelaDestino();
    
    /**
     * @brief Exibe a tela de destinos.
     */
    void mostrar() override;
    
    /**
     * @brief Executa o fluxo de cadastro de destino.
     * @return true se o cadastro ocorrer com sucesso, false caso contrário.
     */
    bool executar();
};

#endif // TELA_DESTINO_HPP
