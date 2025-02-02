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

    int modalAltura = 14;
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

    mvwprintw(painelDestino, 7, 2, "Data Inicio: ");
    mvwaddch(painelDestino, 7, 15, '[');
    mvwhline(painelDestino, 7, 16, ' ', TAM_MAX_DATA);
    mvwaddch(painelDestino, 7, 16 + TAM_MAX_DATA, ']');

    mvwprintw(painelDestino, 9, 2, "Data Fim: ");
    mvwaddch(painelDestino, 9, 12, '[');
    mvwhline(painelDestino, 9, 13, ' ', TAM_MAX_DATA);
    mvwaddch(painelDestino, 9, 13 + TAM_MAX_DATA, ']');

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

    wmove(painelDestino, 7, 16);
    std::string dataInicioStr = campoTexto(painelDestino, 7, 16, TAM_MAX_DATA);
    if (dataInicioStr.empty())
        return false;

    wmove(painelDestino, 9, 13);
    std::string dataFimStr = campoTexto(painelDestino, 9, 13, TAM_MAX_DATA);
    if (dataFimStr.empty())
        return false;

    try
    {
        Codigo codigo(codigoStr);
        Nome nome(nomeStr);
        Data dataInicio(dataInicioStr);
        Data dataFim(dataFimStr);

        Destino destino(nome, codigo, avaliacao, dataInicio, dataFim, viagemCodigo);

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