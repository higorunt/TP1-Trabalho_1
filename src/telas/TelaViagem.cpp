#include "../../include/telas/TelaViagem.hpp"
#include "../../include/entidades/Viagem.hpp"
#include "../../include/servicos/ServicoViagem.hpp"
#include "../../include/dominios/Data.hpp"

TelaViagem::TelaViagem(ServicoViagem *srv)
    : servico(srv), painelViagem(nullptr)
{
}

TelaViagem::~TelaViagem()
{
    if (painelViagem != nullptr)
    {
        delwin(painelViagem);
        painelViagem = nullptr;
    }
}

void TelaViagem::desenharModal()
{
    int altura, largura;
    getmaxyx(janela, altura, largura);

    int modalAltura = 14;
    int modalLargura = 60;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;

    if (painelViagem != nullptr)
    {
        delwin(painelViagem);
    }

    painelViagem = newwin(modalAltura, modalLargura,
                          modalY + getbegy(janela),
                          modalX + getbegx(janela));

    wbkgd(painelViagem, COLOR_PAIR(COR_INVERSA));
    box(painelViagem, 0, 0);

    std::string titulo = "Gerenciar Viagens";
    mvwprintw(painelViagem, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());

    mvwprintw(painelViagem, 3, 2, "Codigo: ");
    mvwaddch(painelViagem, 3, 10, '[');
    mvwhline(painelViagem, 3, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(painelViagem, 3, 11 + TAM_MAX_CODIGO, ']');

    mvwprintw(painelViagem, 5, 2, "Nome: ");
    mvwaddch(painelViagem, 5, 10, '[');
    mvwhline(painelViagem, 5, 11, ' ', TAM_MAX_NOME);
    mvwaddch(painelViagem, 5, 11 + TAM_MAX_NOME, ']');

    mvwprintw(painelViagem, 7, 2, "Data Inicio: ");
    mvwaddch(painelViagem, 7, 15, '[');
    mvwhline(painelViagem, 7, 16, ' ', TAM_MAX_DATA);
    mvwaddch(painelViagem, 7, 16 + TAM_MAX_DATA, ']');

    mvwprintw(painelViagem, 9, 2, "Data Fim: ");
    mvwaddch(painelViagem, 9, 12, '[');
    mvwhline(painelViagem, 9, 13, ' ', TAM_MAX_DATA);
    mvwaddch(painelViagem, 9, 13 + TAM_MAX_DATA, ']');

    mvwprintw(painelViagem, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");

    wrefresh(painelViagem);
}

void TelaViagem::mostrar()
{
    limparTela();
    desenharModal();
}

bool TelaViagem::processarViagem()
{

    wmove(painelViagem, 3, 11);
    std::string codigoStr = campoTexto(painelViagem, 3, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty())
        return false;

    wmove(painelViagem, 5, 11);
    std::string nomeStr = campoTexto(painelViagem, 5, 11, TAM_MAX_NOME);
    if (nomeStr.empty())
        return false;

    wmove(painelViagem, 7, 16);
    std::string dataInicioStr = campoTexto(painelViagem, 7, 16, TAM_MAX_DATA);
    if (dataInicioStr.empty())
        return false;

    wmove(painelViagem, 9, 13);
    std::string dataFimStr = campoTexto(painelViagem, 9, 13, TAM_MAX_DATA);
    if (dataFimStr.empty())
        return false;

    try
    {
        Codigo codigo(codigoStr);
        Nome nome(nomeStr);
        Data dataInicio(dataInicioStr);
        Data dataFim(dataFimStr);

        Viagem viagem(codigo, nome, dataInicio, dataFim);

        if (servico->criarViagem(viagem))
        {
            mostrarAlerta("Viagem criada com sucesso!");
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

bool TelaViagem::executar()
{
    mostrar();
    return processarViagem();
}