#include "../../include/dominios/Data.hpp"
#include <cctype>
#include <algorithm>

bool Data::isAnoBissexto(int ano) const {
    ano += 2000;  // Converte o ano de dois dígitos para o formato completo (2000-2099)
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

void Data::validar(int dia, int mes, int ano) {
    if (mes < 1 || mes > 12) {
        throw std::invalid_argument("Mes invalido. Deve estar entre 1 e 12.");
    }
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && isAnoBissexto(ano)) {
        diasPorMes[1] = 29;
    }
    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        throw std::invalid_argument("Dia invalido para o mes fornecido.");
    }
    if (ano < 0 || ano > 99) {
        throw std::invalid_argument("Ano invalido. Deve estar entre 00 e 99.");
    }
}

Data::Data(int dia, int mes, int ano) {
    validar(dia, mes, ano);
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

Data::Data(const std::string &valor) {
    // Remove espaços (opcional)
    std::string str;
    for (char c : valor) {
        if (!std::isspace(static_cast<unsigned char>(c)))
            str.push_back(c);
    }
    
    // Espera o formato "dd-mm-aa" ou "dd/mm/aa" (8 caracteres)
    if (str.length() != 8) {
        throw std::invalid_argument("Formato de data invalido. Esperado dd-mm-aa.");
    }
    
    char sep = str[2];
    if (sep != '-' && sep != '/') {
        throw std::invalid_argument("Formato de data invalido: separador incorreto.");
    }
    
    try {
        int d = std::stoi(str.substr(0, 2));
        int m = std::stoi(str.substr(3, 2));
        int a = std::stoi(str.substr(6, 2));
        validar(d, m, a);
        dia = d;
        mes = m;
        ano = a;
    } catch (...) {
        throw std::invalid_argument("Erro ao converter data.");
    }
}

void Data::setValor(int dia, int mes, int ano) {
    validar(dia, mes, ano);
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

std::string Data::getValor() const {
    std::ostringstream o;
    o << std::setw(2) << std::setfill('0') << dia << "-"
      << std::setw(2) << std::setfill('0') << mes << "-"
      << std::setw(2) << std::setfill('0') << ano;
    return o.str();
}
