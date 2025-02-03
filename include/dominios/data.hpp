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
    int mes; ///< M�s da data.
    int ano; ///< Ano da data (dois d�gitos).

    /**
     * @brief Valida a data fornecida.
     * @param dia Dia da data.
     * @param mes M�s da data.
     * @param ano Ano da data.
     * @throw std::invalid_argument Se a data for inv�lida.
     */
    void validar(int dia, int mes, int ano);

    /**
     * @brief Verifica se o ano � bissexto.
     * @param ano Ano a ser verificado.
     * @return true se for bissexto, false caso contr�rio.
     */
    bool isAnoBissexto(int ano) const;

public:
    /**
     * @brief Construtor que recebe os valores inteiros para dia, m�s e ano.
     * @param dia Dia.
     * @param mes M�s.
     * @param ano Ano (dois d�gitos).
     */
    Data(int dia, int mes, int ano);

    /**
     * @brief Construtor que recebe uma data em formato de string.
     * Espera o formato "dd-mm-aa" ou "dd/mm/aa".
     * @param valor String contendo a data.
     * @throw std::invalid_argument Se o formato ou os valores forem inv�lidos.
     */
    Data(const std::string &valor);

    /**
     * @brief Define o valor da data.
     * @param dia Dia.
     * @param mes M�s.
     * @param ano Ano.
     */
    void setValor(int dia, int mes, int ano);

    /**
     * @brief Obt�m a data no formato "dd-mm-aa".
     * @return String formatada.
     */
    std::string getValor() const;
};

#endif // DATA_HPP
