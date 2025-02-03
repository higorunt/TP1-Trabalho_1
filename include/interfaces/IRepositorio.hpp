//221006404
// include/interfaces/IRepositorio.hpp
#ifndef I_REPOSITORIO_HPP
#define I_REPOSITORIO_HPP

/**
 * @brief Interface genérica para repositórios.
 * 
 * @tparam T Tipo da entidade a ser armazenada
 * @tparam K Tipo da chave para identificação da entidade
 */
template<typename T, typename K>
class IRepositorio {
public:
    virtual ~IRepositorio() = default;

    /**
     * @brief Busca uma entidade pela chave.
     * @param chave Chave de identificação da entidade.
     * @return Ponteiro para a entidade encontrada ou nullptr se não encontrada.
     */
    virtual T* buscar(const K& chave) = 0;

    /**
     * @brief Salva uma nova entidade no repositório.
     * @param entidade Entidade a ser salva.
     * @return true se salvou com sucesso, false caso contrário.
     */
    virtual bool salvar(const T& entidade) = 0;

    /**
     * @brief Atualiza uma entidade existente.
     * @param entidade Entidade com os dados atualizados.
     * @return true se atualizou com sucesso, false caso contrário.
     */
    virtual bool atualizar(const T& entidade) = 0;

    /**
     * @brief Remove uma entidade do repositório.
     * @param chave Chave da entidade a ser removida.
     * @return true se removeu com sucesso, false caso contrário.
     */
    virtual bool deletar(const K& chave) = 0;
};

#endif