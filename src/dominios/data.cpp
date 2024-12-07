#include "../../include/dominios/data.hpp"
#include <sstream>

/**
 * @brief Verifica se um ano é bissexto.
 * @param ano Ano a ser verificado.
 * @return `true` se o ano for bissexto, caso contrário `false`.
 */
bool Data::isAnoBissexto(int ano) const
{
    ano += 2000; // Ajusta o ano para o intervalo completo (2000 a 2099).
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

/**
 * @brief Método para validar uma data.
 * @param dia Dia do mês.
 * @param mes Mês do ano.
 * @param ano Ano.
 * @throw std::invalid_argument Se a data for inválida.
 */
void Data::validar(int dia, int mes, int ano)
{
    if (mes < 1 || mes > 12)
    {
        throw std::invalid_argument("Mes invalido. Deve estar entre 1 e 12.");
    }

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verifica ano bissexto para fevereiro.
    if (mes == 2 && isAnoBissexto(ano))
    {
        diasPorMes[1] = 29;
    }

    if (dia < 1 || dia > diasPorMes[mes - 1])
    {
        throw std::invalid_argument("Dia invalido para o mes fornecido.");
    }

    if (ano < 0 || ano > 99)
    {
        throw std::invalid_argument("Ano invalido. Deve estar entre 00 e 99.");
    }
}

/**
 * @brief Construtor da classe Data.
 * @param dia Dia do mês.
 * @param mes Mês do ano.
 * @param ano Ano.
 */
Data::Data(int dia, int mes, int ano)
{
    validar(dia, mes, ano);
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

/**
 * @brief Define o valor da data.
 * @param dia Dia do mês.
 * @param mes Mês do ano.
 * @param ano Ano.
 */
void Data::setValor(int dia, int mes, int ano)
{
    validar(dia, mes, ano);
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

/**
 * @brief Retorna a data formatada como string.
 * @return String no formato DD-MM-AA.
 */
std::string Data::getValor() const
{
    std::ostringstream o;
}