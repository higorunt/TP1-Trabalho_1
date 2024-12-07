#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <stdexcept>

/**
 * @class Data
 * @brief Classe que representa o domínio Data.
 *
 * Esta classe valida e armazena uma data no formato DD-MM-AA.
 */
class Data
{
private:
    int dia;                                 ///< Dia do mês (0 a 31).
    int mes;                                 ///< Mês do ano (1 a 12).
    int ano;                                 ///< Ano (00 a 99).
    void validar(int dia, int mes, int ano); ///< Método para validar a data.

    /**
     * @brief Verifica se um ano é bissexto.
     * @param ano Ano a ser verificado.
     * @return `true` se o ano for bissexto, caso contrário `false`.
     */
    bool isAnoBissexto(int ano) const;

public:
    /**
     * @brief Construtor que inicializa e valida a data.
     * @param dia Dia do mês.
     * @param mes Mês do ano.
     * @param ano Ano.
     * @throw std::invalid_argument Se a data for inválida.
     */
    Data(int dia, int mes, int ano);

    /**
     * @brief Define o valor da data após validação.
     * @param dia Dia do mês.
     * @param mes Mês do ano.
     * @param ano Ano.
     * @throw std::invalid_argument Se a data for inválida.
     */
    void setValor(int dia, int mes, int ano);

    /**
     * @brief Retorna a data no formato DD-MM-AA.
     * @return Data formatada como string.
     */
    std::string getValor() const;
};

#endif // DATA_HPP
