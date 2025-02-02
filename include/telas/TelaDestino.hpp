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
 * @brief TelaDestino: Gerencia a interface para opera��es com Destino.
 *
 * Permite cadastrar, listar, editar e excluir destinos. No fluxo de cadastro,
 * o usu�rio seleciona uma viagem dentre as viagens cadastradas para o viajante
 * e, em seguida, informa os dados do destino. O c�digo do destino � gerado automaticamente.
 */
class TelaDestino : public TelaBase {
private:
    ServicoDestino* servicoDestino;  ///< Servi�o de destino.
    ServicoViagem* servicoViagem;    ///< Servi�o de viagem (para obter viagens reais do usu�rio).
    Viajante* viajante;              ///< Viajante autenticado.
    WINDOW* painelDestino;           ///< Janela para exibi��o do menu ou formul�rio.
    
    // Layout para o menu/formul�rio
    struct {
        int altura = 16;
        int largura = 70;
        int centralX;
        int centralY;
    } layout;
    
    // Constantes para os campos (a data � digitada sem separadores)
    static const int TAM_MAX_NOME = 30;      ///< Nome do destino.
    static const int TAM_MAX_DATA = 6;       ///< Data digitada como 6 d�gitos (ex: "050722").
    static const int TAM_MAX_AVALIACAO = 1;    ///< Avalia��o (1 d�gito: 1-5).
    
    // Menu de gerenciamento de destinos
    void desenharMenuDestino();
    void processarOpcaoDestino(int opcao);
    void desenharFormulario(const std::string& infoViagem);

    // Fluxo de cadastro
    bool cadastrarDestino();
    
    // Placeholders para outras opera��es
    void listarDestinos();
    void editarDestino();
    void excluirDestino();
    
    // M�todos auxiliares
    std::string formatarData(const std::string& dataStr);
    time_t dataToTime(const Data& d);
    Codigo selecionarViagem();
    
    // Fluxo de processamento do cadastro
    bool processarDestino(const Codigo& codigoViagem);
    
public:
    /**
     * @brief Construtor da TelaDestino.
     * @param srvDestino Servi�o de destino.
     * @param srvViagem Servi�o de viagem.
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
