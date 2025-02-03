//221006440
// include/interfaces/IRepositorioViagem.hpp
#ifndef IREPOSITORIO_VIAGEM_HPP
#define IREPOSITORIO_VIAGEM_HPP

#include "../entidades/Viagem.hpp"
#include "../dominios/Codigo.hpp"
#include <vector>

/**
 * @brief Interface para o repositório de viagens.
 * 
 * Define as operações básicas de persistência e consulta para entidades do tipo Viagem.
 */
class IRepositorioViagem {
public:
    virtual ~IRepositorioViagem() = default;

    /**
     * @brief Salva uma nova viagem no repositório.
     * @param viagem Viagem a ser salva.
     * @return true se salvou com sucesso, false caso contrário.
     */
    virtual bool salvar(const Viagem& viagem) = 0;

    /**
     * @brief Busca uma viagem pelo código.
     * @param codigo Código da viagem.
     * @return Ponteiro para a viagem encontrada ou nullptr se não encontrada.
     */
    virtual Viagem* buscar(const Codigo& codigo) = 0;

    /**
     * @brief Atualiza uma viagem existente.
     * @param viagem Viagem com os dados atualizados.
     * @return true se atualizou com sucesso, false caso contrário.
     */
    virtual bool atualizar(const Viagem& viagem) = 0;

    /**
     * @brief Remove uma viagem do repositório.
     * @param codigo Código da viagem a ser removida.
     * @return true se removeu com sucesso, false caso contrário.
     */
    virtual bool deletar(const Codigo& codigo) = 0;

    /**
     * @brief Lista todas as viagens de um viajante específico.
     * @param codigoViajante Código do viajante.
     * @return Vector contendo todas as viagens do viajante.
     */
    virtual std::vector<Viagem> listarPorViajante(const Codigo& codigoViajante) = 0;
};

#endif