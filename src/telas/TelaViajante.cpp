#include "../../include/telas/TelaViajante.hpp"
#include "../../include/entidades/Viajante.hpp"
#include "../../include/servicos/ServicoViajante.hpp"

TelaViajante::TelaViajante(ServicoViajante *srv)
    : servico(srv), painelViajante(nullptr)
{
}

TelaViajante::~TelaViajante()
{
    if (painelViajante != nullptr)
    {
        delwin(painelViajante);
        painelViajante = nullptr;
    }
}

void TelaViajante::desenharModal()
{
    int altura, largura;
    getmaxyx(janela, altura, largura);

    int modalAltura = 10;
    int modalLargura = 60;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;

    if (painelViajante != nullptr)
    {
        delwin(painelViajante);
    }

    painelViajante = newwin(modalAltura, modalLargura,
                            modalY + getbegy(janela),
                            modalX + getbegx(janela));

    wbkgd(painelViajante, COLOR_PAIR(COR_INVERSA));
    box(painelViajante, 0, 0);

    std::string titulo = "Gerenciar Viajantes";
    mvwprintw(painelViajante, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());

    mvwprintw(painelViajante, 3, 2, "Codigo: ");
    mvwaddch(painelViajante, 3, 10, '[');
    mvwhline(painelViajante, 3, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(painelViajante, 3, 11 + TAM_MAX_CODIGO, ']');

    mvwprintw(painelViajante, 5, 2, "Nome: ");
    mvwaddch(painelViajante, 5, 10, '[');
    mvwhline(painelViajante, 5, 11, ' ', TAM_MAX_NOME);
    mvwaddch(painelViajante, 5, 11 + TAM_MAX_NOME, ']');

    mvwprintw(painelViajante, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");

    wrefresh(painelViajante);
}

void TelaViajante::mostrar()
{
    limparTela();
    desenharModal();
}

bool TelaViajante::processarViajante()
{
    wmove(painelViajante, 3, 11);
    std::string codigoStr = campoTexto(painelViajante, 3, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty())
        return false;

    wmove(painelViajante, 5, 11);
    std::string nomeStr = campoTexto(painelViajante, 5, 11, TAM_MAX_NOME);
    if (nomeStr.empty())
        return false;

    try
    {
        Codigo codigo(codigoStr);
        Nome nome(nomeStr);

        Viajante viajante(nome, codigo, conta);

        if (servico->criarViajante(viajante))
        {
            mostrarAlerta("Viajante criado com sucesso!");
            return true;
        }
        return false;
    }
    catch (const std::invalid_argument &e)
    {
        mostrarAlerta(e.what());
        return false;
    }
    catch (const std::runtime_error &e)
    {
        mostrarAlerta(e.what());
        return false;
    }
    catch (const std::exception &e)
    {
        mostrarAlerta("Erro no sistema");
        return false;
    }
}

bool TelaViajante::executar()
{
    mostrar();
    return processarViajante();
}