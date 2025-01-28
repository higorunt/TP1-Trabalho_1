// include/repositories/MockAutenticacaoRepository.hpp
#ifndef MOCK_AUTENTICACAO_REPOSITORY_HPP
#define MOCK_AUTENTICACAO_REPOSITORY_HPP

#include "../interfaces/IAutenticacaoRepository.hpp"
#include "../entidades/Viajante.hpp"
#include "../dominios/Nome.hpp"

class MockAutenticacaoRepository : public IAutenticacaoRepository {
public:
    MockAutenticacaoRepository() = default;
    ~MockAutenticacaoRepository() override = default;
    
    Viajante* buscarPorCodigo(const Codigo& codigo) override;
    bool salvar(const Viajante& viajante) override;
};

#endif