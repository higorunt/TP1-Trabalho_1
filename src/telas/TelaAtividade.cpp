#include "telas/TelaAtividade.hpp"

TelaAtividade::TelaAtividade(ServicoAtividade *srv)
    : servico(srv), painelAtividade(nullptr) {}

TelaAtividade::~TelaAtividade()
{
    if (painelAtividade != nullptr)
    {
        delwin(painelAtividade);
    }
}

void TelaAtividade::desenharModal()
{
    int altura, largura;
    getmaxyx(stdscr, altura, largura);
    int modalAltura = 15;
    int modalLargura = 40;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;

    if (painelAtividade != nullptr)
    {
        delwin(painelAtividade);
    }
    painelAtividade = newwin(modalAltura, modalLargura, modalY, modalX);
    wbkgd(painelAtividade, COLOR_PAIR(1));
    box(painelAtividade, 0, 0);
    std::string titulo = "Atividade";
    mvwprintw(painelAtividade, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());
    mvwaddch(painelAtividade, 3, 10, '[');
    mvwhline(painelAtividade, 3, 11, ' ', 10);
    mvwaddch(painelAtividade, 3, 21, ']');
    wrefresh(painelAtividade);
}

void TelaAtividade::mostrar()
{
    clear();
    desenharModal();
    refresh();
}

bool TelaAtividade::processarAtividade()
{
    wmove(painelAtividade, 3, 11);
    std::string codigoStr = "12345"; // Exemplo de código
    mvwprintw(painelAtividade, 3, 11, "%s", codigoStr.c_str());
    wrefresh(painelAtividade);
    return true;
}