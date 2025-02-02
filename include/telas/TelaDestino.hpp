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
 * o usuário seleciona uma viagem dentre as viagens cadastradas para o viajante
 * e, em seguida, informa os dados do destino. O código do destino é gerado automaticamente.
 */
class TelaDestino : public TelaBase {
private:
    ServicoDestino* servicoDestino;  ///< Serviço de destino.
    ServicoViagem* servicoViagem;    ///< Serviço de viagem (para obter viagens reais do usuário).
    Viajante* viajante;              ///< Viajante autenticado.
    WINDOW* painelDestino;           ///< Janela para exibição do menu ou formulário.
    
    // Layout para o menu/formulário
    struct {
        int altura = 16;
        int largura = 70;
        int centralX;
        int centralY;
    } layout;
    
    // Constantes para os campos (a data é digitada sem separadores)
    static const int TAM_MAX_NOME = 30;      ///< Nome do destino.
    static const int TAM_MAX_DATA = 6;       ///< Data digitada como 6 dígitos (ex: "050722").
    static const int TAM_MAX_AVALIACAO = 1;    ///< Avaliação (1 dígito: 1-5).
    
    // Menu de gerenciamento de destinos
    void desenharMenuDestino();
    void processarOpcaoDestino(int opcao);
    void desenharFormulario(const std::string& infoViagem);

    // Fluxo de cadastro
    bool cadastrarDestino();
    
    // Placeholders para outras operações
    void listarDestinos();
    void editarDestino();
    void excluirDestino();
    
    // Métodos auxiliares
    std::string formatarData(const std::string& dataStr);
    time_t dataToTime(const Data& d);
    Codigo selecionarViagem();
    
    // Fluxo de processamento do cadastro
    bool processarDestino(const Codigo& codigoViagem);
    
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
     * @brief Exibe o menu principal da TelaDestino.
     */
    void mostrar() override;
    
    /**
     * @brief Executa o fluxo completo de gerenciamento de destinos.
     * @return true se o fluxo foi executado, false se cancelado.
     */
    bool executar();
};

#endif // TELA_DESTINO_HPP
