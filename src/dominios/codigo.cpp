#include "../../include/dominios/codigo.hpp"

/**
 * @brief M�todo para validar o c�digo.
 * @param valor C�digo a ser validado.
 * @throw std::invalid_argument Se o c�digo n�o atender aos crit�rios.
 */
void Codigo::validar(const std::string &valor)
{
    // Verifica se o c�digo tem o tamanho correto.
    if (valor.length() != TAMANHO)
    {
        throw std::invalid_argument("Codigo invalido: deve ter exatamente 6 caracteres.");
    }

    // Regex para validar que o c�digo � alfanum�rico (letras ou d�gitos).
    std::regex regexAlfanumerico("^[a-zA-Z0-9]{6}$");
    if (!std::regex_match(valor, regexAlfanumerico))
    {
        throw std::invalid_argument("Codigo invalido: deve conter apenas letras e numeros.");
    }
}

/**
 * @brief Construtor que inicializa e valida o c�digo.
 * @param valor C�digo inicial a ser atribu�do.
 */
Codigo::Codigo(const std::string &valor)
{
    validar(valor);
        this->valor = valor;
    }


/**
 * @brief Define o valor do c�digo ap�s valida��o.
 * @param valor C�digo a ser atribu�do.
 */
void Codigo::setValor(const std::string &valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor do c�digo.
 * @return C�digo armazenado.
 */
std::string Codigo::getValor() const
{
    return valor;
}