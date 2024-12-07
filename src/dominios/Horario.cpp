#include "../../include/dominios/Horario.hpp"


class Horario {
private:
    std::string horario;

public:
    void validar(std::string horario);
    void setValor(std::string horario);
    std::string getValor() const;
};

void Horario::validar(std::string horario) {
    if (horario.size() != 5 || horario[2] != ':') {
        throw std::invalid_argument("Horario invalido");
    }
    int horas = std::stoi(horario.substr(0, 2));
    int minutos = std::stoi(horario.substr(3, 2));
    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59) {
        throw std::invalid_argument("Horario invalido");
    }
}

void Horario::setValor(std::string horario) {
    validar(horario);
    this->horario = horario;
}

std::string Horario::getValor() const {
    return horario;
}