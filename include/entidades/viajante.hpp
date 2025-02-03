//221006404

#ifndef VIAJANTE_HPP
#define VIAJANTE_HPP

#include "../dominios/Nome.hpp"
#include "../entidades/Conta.hpp"

/**
 * @brief Classe que representa um Viajante no sistema.
 * 
 * Esta classe mantém as informações básicas de um viajante,
 * incluindo seu nome e conta associada.
 */
class Viajante
{
private:
    Nome nome;   ///< Nome do viajante.
    Conta conta; ///< Conta associada ao viajante.

public:
    /**
     * @brief Construtor da classe Viajante.
     * @param nome Nome do viajante.
     * @param conta Conta associada ao viajante.
     */
    Viajante(const Nome &nome, const Conta &conta) : nome(nome), conta(conta) {}

    /**
     * @brief Define o nome do viajante.
     * @param nome Novo nome a ser atribuído.
     */
    void setNome(const Nome &nome) { this->nome = nome; }

    /**
     * @brief Obtém o nome do viajante.
     * @return Nome atual do viajante.
     */
    Nome getNome() const { return nome; }

    /**
     * @brief Obtém a conta associada ao viajante.
     * @return Conta do viajante.
     */
    Conta getConta() const { return conta; }
};

#endif // VIAJANTE_HPP
