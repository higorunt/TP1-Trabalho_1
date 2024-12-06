#ifndef NOME_H
#define NOME_H

#include <string>
#include <stdexcept>

/**
 * @class Nome
 * @brief Classe que representa o dom�nio Nome.
 *
 * Esta classe valida e armazena nomes de 1 a 30 caracteres.
 */
class Nome {
private:
    std::string valor;
    static const int TAMANHO_MAXIMO = 30;
    void validar(const std::string& valor);

public:
    /**
     * @brief Construtor que inicializa e valida o nome.
     * @param valor Nome a ser atribu�do.
     * @throw std::invalid_argument Se o nome for inv�lido.
     */
    explicit Nome(const std::string& valor);

    /**
     * @brief Define o valor do nome ap�s valida��o.
     * @param valor Nome a ser atribu�do.
     * @throw std::invalid_argument Se o nome for inv�lido.
     */
    void setValor(const std::string& valor);

    /**
     * @brief Retorna o valor do nome.
     * @return Nome armazenado.
     */
    std::string getValor() const;
};

#endif // NOME_H
