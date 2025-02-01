//221006440



#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

/**
 * @class Data
 * @brief Classe que representa uma data.
 */
class Data {
private:
    int dia; ///< Dia da data.
    int mes; ///< Mês da data.
    int ano; ///< Ano da data.

    /**
     * @brief Valida a data fornecida.
     * @param dia Dia da data.
     * @param mes Mês da data.
     * @param ano Ano da data.
     * @throw std::invalid_argument Se a data for inválida.
     */
    void validar(int dia, int mes, int ano);

    /**
     * @brief Verifica se o ano é bissexto.
     * @param ano Ano a ser verificado.
     * @return true se o ano for bissexto, false caso contrário.
     */
    bool isAnoBissexto(int ano) const;

public:
    /**
     * @brief Construtor da classe Data.
     * @param dia Dia da data.
     * @param mes Mês da data.
     * @param ano Ano da data.
     * @throw std::invalid_argument Se a data for inválida.
     */
    Data(int dia, int mes, int ano);

    /**
     * @brief Define o valor da data.
     * @param dia Dia da data.
     * @param mes Mês da data.
     * @param ano Ano da data.
     * @throw std::invalid_argument Se a data for inválida.
     */
    void setValor(int dia, int mes, int ano);

    /**
     * @brief Obtém o valor da data como string.
     * @return String no formato "dd/mm/aaaa".
     */
    std::string getValor() const;
    // Adicionar operadores de comparação
    bool operator<(const Data& outra) const;
    bool operator>(const Data& outra) const;
    bool operator<=(const Data& outra) const;
    bool operator>=(const Data& outra) const;
    bool operator==(const Data& outra) const;

    // Método para comparar datas
    bool estaDentroDoIntervalo(const Data& inicio, const Data& fim) const;

};

#endif // DATA_HPP