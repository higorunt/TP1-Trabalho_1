// include/interfaces/IRepositorio.hpp
#ifndef I_REPOSITORIO_HPP
#define I_REPOSITORIO_HPP

template<typename T, typename K>
class IRepositorio {
public:
    virtual ~IRepositorio() = default;
    virtual T* buscar(const K& chave) = 0;
    virtual bool salvar(const T& entidade) = 0;
    virtual bool atualizar(const T& entidade) = 0;
    virtual bool deletar(const K& chave) = 0;
};

#endif