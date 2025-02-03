//221006440
// include/interfaces/IRepositorioViagem.hpp
#ifndef IREPOSITORIO_VIAGEM_HPP
#define IREPOSITORIO_VIAGEM_HPP

#include "../entidades/Viagem.hpp"
#include "../dominios/Codigo.hpp"
#include <vector>

/**
 * @brief Interface para o reposit�rio de viagens.
 * 
 * Define as opera��es b�sicas de persist�ncia e consulta para entidades do tipo Viagem.
 */
class IRepositorioViagem {
public:
    virtual ~IRepositorioViagem() = default;

    /**
     * @brief Salva uma nova viagem no reposit�rio.
     * @param viagem Viagem a ser salva.
     * @return true se salvou com sucesso, false caso contr�rio.
     */
    virtual bool salvar(const Viagem& viagem) = 0;

    /**
     * @brief Busca uma viagem pelo c�digo.
     * @param codigo C�digo da viagem.
     * @return Ponteiro para a viagem encontrada ou nullptr se n�o encontrada.
     */
    virtual Viagem* buscar(const Codigo& codigo) = 0;

    /**
     * @brief Atualiza uma viagem existente.
     * @param viagem Viagem com os dados atualizados.
     * @return true se atualizou com sucesso, false caso contr�rio.
     */
    virtual bool atualizar(const Viagem& viagem) = 0;

    /**
     * @brief Remove uma viagem do reposit�rio.
     * @param codigo C�digo da viagem a ser removida.
     * @return true se removeu com sucesso, false caso contr�rio.
     */
    virtual bool deletar(const Codigo& codigo) = 0;

    /**
     * @brief Lista todas as viagens de um viajante espec�fico.
     * @param codigoViajante C�digo do viajante.
     * @return Vector contendo todas as viagens do viajante.
     */
    virtual std::vector<Viagem> listarPorViajante(const Codigo& codigoViajante) = 0;
};

#endif