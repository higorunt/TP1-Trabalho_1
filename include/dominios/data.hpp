//221006440
#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

/**
 * @brief Classe que representa uma data no formato "dd-mm-aa".
 */
class Data {
private:
    int dia; ///< Dia da data.
    int mes; ///< Mês da data.
    int ano; ///< Ano da data (dois dígitos).

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
     * @return true se for bissexto, false caso contrário.
     */
    bool isAnoBissexto(int ano) const;

public:
    /**
     * @brief Construtor que recebe os valores inteiros para dia, mês e ano.
     * @param dia Dia.
     * @param mes Mês.
     * @param ano Ano (dois dígitos).
     */
    Data(int dia, int mes, int ano);

    /**
     * @brief Construtor que recebe uma data em formato de string.
     * Espera o formato "dd-mm-aa" ou "dd/mm/aa".
     * @param valor String contendo a data.
     * @throw std::invalid_argument Se o formato ou os valores forem inválidos.
     */
    Data(const std::string &valor);

    /**
     * @brief Define o valor da data.
     * @param dia Dia.
     * @param mes Mês.
     * @param ano Ano.
     */
    void setValor(int dia, int mes, int ano);

    /**
     * @brief Obtém a data no formato "dd-mm-aa".
     * @return String formatada.
     */
    std::string getValor() const;
};

#endif // DATA_HPP
