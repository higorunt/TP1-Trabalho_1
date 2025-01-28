// include/interfaces/IAutenticacaoRepository.hpp
#ifndef IAUTENTICACAO_REPOSITORY_HPP
#define IAUTENTICACAO_REPOSITORY_HPP

#include "../entidades/Viajante.hpp"
#include "../dominios/Codigo.hpp"

class IAutenticacaoRepository {
public:
    virtual ~IAutenticacaoRepository() = default;
    virtual Viajante* buscarPorCodigo(const Codigo& codigo) = 0;
    virtual bool salvar(const Viajante& viajante) = 0;
};

#endif