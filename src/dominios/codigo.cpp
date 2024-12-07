#include "../../include/dominios/codigo.hpp"

/**
 * @brief Método para validar o código.
 * @param valor Código a ser validado.
 * @throw std::invalid_argument Se o código não atender aos critérios.
 */
void Codigo::validar(const std::string &valor)
{
    // Verifica se o código tem o tamanho correto.
    if (valor.length() != TAMANHO)
    {
        throw std::invalid_argument("Codigo invalido: deve ter exatamente 6 caracteres.");
    }

    // Regex para validar que o código é alfanumérico (letras ou dígitos).
    std::regex regexAlfanumerico("^[a-zA-Z0-9]{6}$");
    if (!std::regex_match(valor, regexAlfanumerico))
    {
        throw std::invalid_argument("Codigo invalido: deve conter apenas letras e numeros.");
    }
}

/**
 * @brief Construtor que inicializa e valida o código.
 * @param valor Código inicial a ser atribuído.
 */
Codigo::Codigo(const std::string &valor)
{
    validar(valor);
        this->valor = valor;
    }


/**
 * @brief Define o valor do código após validação.
 * @param valor Código a ser atribuído.
 */
void Codigo::setValor(const std::string &valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor do código.
 * @return Código armazenado.
 */
std::string Codigo::getValor() const
{
    return valor;
}