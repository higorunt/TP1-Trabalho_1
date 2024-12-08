#include "../../include/dominios/Senha.hpp"

/**
 * @brief Verifica se a sequ�ncia de d�gitos est� em ordem crescente.
 *
 * @param s String representando a senha.
 * @return true Se a sequ�ncia estiver em ordem crescente.
 * @return false Caso contr�rio.
 */
bool VerificaCrescente(const std::string &s)
{
    for (size_t i = 1; i < s.size(); ++i)
    {
        if (s[i] < s[i - 1])
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Verifica se a sequ�ncia de d�gitos est� em ordem decrescente.
 *
 * @param s String representando a senha.
 * @return true Se a sequ�ncia estiver em ordem decrescente.
 * @return false Caso contr�rio.
 */
bool VerificaDescrente(const std::string &s)
{
    for (size_t i = 1; i < s.size(); ++i)
    {
        if (s[i] > s[i - 1])
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Valida a senha de acordo com as regras estabelecidas.
 *
 * A senha deve:
 * - Ter exatamente 5 d�gitos.
 * - Conter apenas caracteres num�ricos.
 * - N�o possuir d�gitos repetidos.
 * - N�o estar em ordem crescente ou decrescente.
 *
 * @param valor String representando a senha a ser validada.
 * @throw std::invalid_argument Se a senha n�o cumprir os crit�rios de valida��o.
 */
void Senha::validar(const std::string &valor)
{
    if (valor.size() != TAMANHO)
    {
        throw std::invalid_argument("Erro: Senha deve conter exatamente 5 d�gitos.");
    }
    for (char c : valor)
    {
        if (!isdigit(c))
        {
            throw std::invalid_argument("Erro: Senha deve conter apenas d�gitos.");
        }
    }
    for (size_t i = 0; i < valor.size(); ++i)
    {
        for (size_t j = i + 1; j < valor.size(); ++j)
        {
            if (valor[i] == valor[j])
            {
                throw std::invalid_argument("Erro: Senha n�o pode conter d�gitos duplicados.");
            }
        }
    }
    if (VerificaCrescente(valor) || VerificaDescrente(valor))
    {
        throw std::invalid_argument("Erro: Senha n�o pode estar em ordem crescente ou decrescente.");
    }
}

/**
 * @brief Construtor da classe Senha.
 *
 * Inicializa o objeto com uma senha v�lida.
 *
 * @param valor String representando a senha inicial.
 * @throw std::invalid_argument Se a senha n�o cumprir os crit�rios de valida��o.
 */
Senha::Senha(const std::string &valor)
{
    setValor(valor);
}

/**
 * @brief Define o valor da senha.
 *
 * Valida a senha antes de atribu�-la ao atributo interno.
 *
 * @param valor String representando o novo valor da senha.
 * @throw std::invalid_argument Se a senha n�o cumprir os crit�rios de valida��o.
 */
void Senha::setValor(const std::string &valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor da senha armazenada.
 *
 * @return String que representa a senha.
 */
std::string Senha::getValor() const
{
    return valor;
}
