#include "../../include/dominios/Nome.h"

void Nome::validar(const std::string& valor) {
    if (valor.empty() || valor.size() > TAMANHO_MAXIMO) {
        throw std::invalid_argument("Erro: Nome inválido. Deve conter entre 1 e 30 caracteres.");
    }
}

Nome::Nome(const std::string& valor) {
    setValor(valor);
}

void Nome::setValor(const std::string& valor) {
    validar(valor);
    this->valor = valor;
}

std::string Nome::getValor() const {
    return valor;
}
