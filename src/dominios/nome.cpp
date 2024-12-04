#include "../../include/dominios/Nome.h"

// Validação do nome
void Nome::validar(const std::string& valor) {
    if (valor.empty() || valor.size() > TAMANHO_MAXIMO) {
        throw std::invalid_argument("Erro: Nome invalido. Deve conter entre 1 e 30 caracteres.");
    }
}

// Definir o valor do nome
void Nome::setValor(const std::string& valor) {
    validar(valor); // Valida o nome antes de atribuir
    this->valor = valor;
}

// Obter o valor do nome
std::string Nome::getValor() const {
    return valor;
}
