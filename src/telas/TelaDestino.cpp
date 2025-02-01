#include "../../include/telas/TelaDestino.hpp"
#include "../../include/entidades/Destino.hpp"
#include "../../include/servicos/ServicoDestino.hpp"

TelaDestino::TelaDestino(ServicoDestino *srv)
    : servico(srv), painelDestino(nullptr)
{
}

TelaDestino::~TelaDestino()
{
    if (painelDestino != nullptr)
    {
        delwin(painelDestino);
        painelDestino = nullptr;
    }
}

void TelaDestino::desenharModal()
{
    int altura, largura;
    getmaxyx(janela, altura, largura);

    int modalAltura = 12;
    int modalLargura = 60;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;

    if (painelDestino != nullptr)
    {
        delwin(painelDestino);
    }

    painelDestino = newwin(modalAltura, modalLargura,
                           modalY + getbegy(janela),
                           modalX + getbegx(janela));

    wbkgd(painelDestino, COLOR_PAIR(COR_INVERSA));
    box(painelDestino, 0, 0);

    std::string titulo = "Gerenciar Destinos";
    mvwprintw(painelDestino, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());

    mvwprintw(painelDestino, 3, 2, "Codigo: ");
    mvwaddch(painelDestino, 3, 10, '[');
    mvwhline(painelDestino, 3, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(painelDestino, 3, 11 + TAM_MAX_CODIGO, ']');

    mvwprintw(painelDestino, 5, 2, "Nome: ");
    mvwaddch(painelDestino, 5, 10, '[');
    mvwhline(painelDestino, 5, 11, ' ', TAM_MAX_NOME);
    mvwaddch(painelDestino, 5, 11 + TAM_MAX_NOME, ']');

    mvwprintw(painelDestino, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");

    wrefresh(painelDestino);
}

void TelaDestino::mostrar()
{
    limparTela();
    desenharModal();
}

bool TelaDestino::processarDestino()
{
    wmove(painelDestino, 3, 11);
    std::string codigoStr = campoTexto(painelDestino, 3, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty())
        return false;

    wmove(painelDestino, 5, 11);
    std::string nomeStr = campoTexto(painelDestino, 5, 11, TAM_MAX_NOME);
    if (nomeStr.empty())
        return false;

    try
    {
        Codigo codigo(codigoStr);
        Nome nome(nomeStr);

        Destino destino(codigo, nome);

        if (servico->criarDestino(destino))
        {
            mostrarAlerta("Destino criado com sucesso!");
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

bool TelaDestino::executar()
{
    mostrar();
    return processarDestino();
}