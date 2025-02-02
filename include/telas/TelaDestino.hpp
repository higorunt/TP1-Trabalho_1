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
 * o usu�rio primeiro seleciona uma viagem dentre as viagens cadastradas (do usu�rio real)
 * e, em seguida, informa os dados do destino a ser cadastrado. O c�digo do destino �
 * gerado automaticamente.
 */
class TelaDestino : public TelaBase {
private:
    ServicoDestino* servicoDestino;  ///< Servi�o de destino.
    ServicoViagem* servicoViagem;    ///< Servi�o de viagem (para listar as viagens reais do usu�rio).
    Viajante* viajante;              ///< Viajante autenticado.
    WINDOW* painelDestino;           ///< Janela para exibi��o do formul�rio.
    
    // Layout do formul�rio
    struct {
        int altura = 16;
        int largura = 70;
        int centralX;
        int centralY;
    } layout;
    
    // Constantes para tamanho dos campos
    static const int TAM_MAX_NOME = 30;      ///< Tamanho m�ximo para o nome do destino.
    static const int TAM_MAX_DATA = 8;       ///< Tamanho m�ximo para datas (ex: "05-07-22").
    static const int TAM_MAX_AVALIACAO = 1;    ///< Tamanho m�ximo para a avalia��o (1 d�gito: 1-5).
    
    /**
     * @brief Exibe a lista de viagens do usu�rio e permite a sele��o.
     * @return C�digo da viagem selecionada ou um c�digo "sentinela" (ex: "000000") se cancelado.
     */
    Codigo selecionarViagem();
    
    /**
     * @brief Desenha o formul�rio para cadastro de destino, exibindo informa��es da viagem selecionada.
     * @param infoViagem Informa��o da viagem (por exemplo, "Viagem: TRI123 - Nome da Viagem").
     */
    void desenharFormulario(const std::string& infoViagem);
    
    /**
     * @brief Processa os dados inseridos no formul�rio e cria o destino.
     * @param codigoViagem C�digo da viagem selecionada (foreign key).
     * @return true se o cadastro ocorrer com sucesso, false caso contr�rio.
     */
    bool processarDestino(const Codigo& codigoViagem);
    
    // (Outras funcionalidades, como listar, editar e excluir destinos, podem ser implementadas posteriormente.)
    
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
     * @brief Exibe a tela de destinos.
     */
    void mostrar() override;
    
    /**
     * @brief Executa o fluxo de cadastro de destino.
     * @return true se o cadastro ocorrer com sucesso, false caso contr�rio.
     */
    bool executar();
};

#endif // TELA_DESTINO_HPP
