//221006404


#ifndef VIAJANTE_HPP
#define VIAJANTE_HPP

#include "../dominios/Nome.hpp"
#include "../entidades/Conta.hpp"

class Viajante
{
private:
    Nome nome;   ///< Nome do viajante.
    Conta conta; ///< Conta associada ao viajante.

public:
    /**
     * Construtor para inicializar um viajante.
     * @param nome Nome do viajante.
     * @param conta Conta associada ao viajante.
     */
    Viajante(const Nome &nome, const Conta &conta) : nome(nome), conta(conta) {}

    // Métodos para acessar e modificar o nome.
    void setNome(const Nome &nome) { this->nome = nome; }
    Nome getNome() const { return nome; }

    // Métodos para acessar a conta.
    Conta getConta() const { return conta; }
};

#endif // VIAJANTE_HPP
