#include "../../include/dominios/Data.hpp"

bool Data::isAnoBissexto(int ano) const {
    ano += 2000;
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

void Data::validar(int dia, int mes, int ano) {
    if (mes < 1 || mes > 12) {
        throw std::invalid_argument("Mes inválido. Deve estar entre 1 e 12.");
    }
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && isAnoBissexto(ano)) {
        diasPorMes[1] = 29;
    }
    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        throw std::invalid_argument("Dia inválido para o mês fornecido.");
    }
    if (ano < 0 || ano > 99) {
        throw std::invalid_argument("Ano inválido. Deve estar entre 00 e 99.");
    }
}

Data::Data(int dia, int mes, int ano) {
    validar(dia, mes, ano);
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
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