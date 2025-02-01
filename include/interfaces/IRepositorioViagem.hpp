// include/interfaces/IRepositorioViagem.hpp
#ifndef IREPOSITORIO_VIAGEM_HPP
#define IREPOSITORIO_VIAGEM_HPP

#include "../entidades/Viagem.hpp"
#include "../dominios/Codigo.hpp"
#include <vector>

class IRepositorioViagem {
public:
    virtual ~IRepositorioViagem() = default;
    virtual bool salvar(const Viagem& viagem) = 0;
    virtual Viagem* buscar(const Codigo& codigo) = 0;
    virtual bool atualizar(const Viagem& viagem) = 0;
    virtual bool deletar(const Codigo& codigo) = 0;
    virtual std::vector<Viagem> listarPorViajante(const Codigo& codigoViajante) = 0;
};

#endif