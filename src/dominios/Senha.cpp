#include "../../include/dominios/Senha.hpp"

bool is_sorted_asc(const std::string& s) {
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] < s[i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_sorted_desc(const std::string& s) {
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] > s[i - 1]) {
            return false;
        }
    }
    return true;
}

void Senha::validar(const std::string& valor) {
    if (valor.size() != TAMANHO) {
        throw std::invalid_argument("Erro: Senha deve conter exatamente 5 dígitos.");
    }
    for (char c : valor) {
        if (!isdigit(c)) {
            throw std::invalid_argument("Erro: Senha deve conter apenas dígitos.");
        }
    }
    for (size_t i = 0; i < valor.size(); ++i) {
        for (size_t j = i + 1; j < valor.size(); ++j) {
            if (valor[i] == valor[j]) {
                throw std::invalid_argument("Erro: Senha não pode conter dígitos duplicados.");
            }
        }
    }
    if (is_sorted_asc(valor) || is_sorted_desc(valor)) {
        throw std::invalid_argument("Erro: Senha não pode estar em ordem crescente ou decrescente.");
    }
}

Senha::Senha(const std::string& valor) {
    setValor(valor);
}

void Senha::setValor(const std::string& valor) {
    validar(valor);
    this->valor = valor;
}

std::string Senha::getValor() const {
    return valor;
}