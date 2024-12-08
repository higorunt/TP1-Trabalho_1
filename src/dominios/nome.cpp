#include "../../include/dominios/Nome.hpp"

/**
 * @brief Valida o valor do nome.
 *
 * O nome deve conter entre 1 e 30 caracteres.
 *
 * @param valor String que representa o nome a ser validado.
 * @throw std::invalid_argument Se o nome for vazio ou tiver mais de 30 caracteres.
 */
void Nome::validar(const std::string &valor)
{
    if (valor.empty() || valor.size() > TAMANHO_MAXIMO)
    {
        throw std::invalid_argument("Erro: Nome inválido. Deve conter entre 1 e 30 caracteres.");
    }
}

/**
 * @brief Construtor da classe Nome.
 *
 * Inicializa o objeto Nome com um valor válido.
 *
 * @param valor String que representa o nome inicial.
 * @throw std::invalid_argument Se o nome for inválido.
 */
Nome::Nome(const std::string &valor)
{
    setValor(valor);
}

/**
 * @brief Define o valor do nome.
 *
 * Valida o nome antes de atribuí-lo ao atributo interno.
 *
 * @param valor String que representa o novo valor do nome.
 * @throw std::invalid_argument Se o nome for inválido.
 */
void Nome::setValor(const std::string &valor)
{
    validar(valor);
    this->valor = valor;
}

/**
 * @brief Retorna o valor do nome armazenado.
 *
 * @return String que representa o nome.
 */
std::string Nome::getValor() const
{
    return valor;
}
