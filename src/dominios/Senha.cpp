#include "../../include/dominios/Senha.hpp"

/**
 * @brief Verifica se a sequência de dígitos está em ordem crescente.
 *
 * @param s String representando a senha.
 * @return true Se a sequência estiver em ordem crescente.
 * @return false Caso contrário.
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
 * @brief Verifica se a sequência de dígitos está em ordem decrescente.
 *
 * @param s String representando a senha.
 * @return true Se a sequência estiver em ordem decrescente.
 * @return false Caso contrário.
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
 * - Ter exatamente 5 dígitos.
 * - Conter apenas caracteres numéricos.
 * - Não possuir dígitos repetidos.
 * - Não estar em ordem crescente ou decrescente.
 *
 * @param valor String representando a senha a ser validada.
 * @throw std::invalid_argument Se a senha não cumprir os critérios de validação.
 */
void Senha::validar(const std::string &valor)
{
    if (valor.size() != TAMANHO)
    {
        throw std::invalid_argument("Erro: Senha deve conter exatamente 5 dígitos.");
    }
    for (char c : valor)
    {
        if (!isdigit(c))
        {
            throw std::invalid_argument("Erro: Senha deve conter apenas dígitos.");
        }
    }
    for (size_t i = 0; i < valor.size(); ++i)
    {
        for (size_t j = i + 1; j < valor.size(); ++j)
        {
            if (valor[i] == valor[j])
            {
                throw std::invalid_argument("Erro: Senha não pode conter dígitos duplicados.");
            }
        }
    }
    if (VerificaCrescente(valor) || VerificaDescrente(valor))
    {
        throw std::invalid_argument("Erro: Senha não pode estar em ordem crescente ou decrescente.");
    }
}

/**
 * @brief Construtor da classe Senha.
 *
 * Inicializa o objeto com uma senha válida.
 *
 * @param valor String representando a senha inicial.
 * @throw std::invalid_argument Se a senha não cumprir os critérios de validação.
 */
Senha::Senha(const std::string &valor)
{
    setValor(valor);
}

/**
 * @brief Define o valor da senha.
 *
 * Valida a senha antes de atribuí-la ao atributo interno.
 *
 * @param valor String representando o novo valor da senha.
 * @throw std::invalid_argument Se a senha não cumprir os critérios de validação.
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
