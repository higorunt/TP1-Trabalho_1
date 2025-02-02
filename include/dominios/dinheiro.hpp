#ifndef DINHEIRO_HPP
#define DINHEIRO_HPP

class Dinheiro
{
private:
    double valor;

public:
    explicit Dinheiro(double valor);
    double getValor() const;
};

#endif // DINHEIRO_HPP