#include "../../include/telas/TelaHospedagem.hpp"
#include "../../include/entidades/Hospedagem.hpp"
#include "../../include/servicos/ServicoHospedagem.hpp"

TelaHospedagem::TelaHospedagem(ServicoHospedagem *srv)
    : servico(srv), painelHospedagem(nullptr)
{
}

TelaHospedagem::~TelaHospedagem()
{
    if (painelHospedagem != nullptr)
    {
        delwin(painelHospedagem);
        painelHospedagem = nullptr;
    }
}

void TelaHospedagem::desenharModal()
{
    int altura, largura;
    getmaxyx(janela, altura, largura);

    int modalAltura = 12;
    int modalLargura = 60;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;

    if (painelHospedagem != nullptr)
    {
        delwin(painelHospedagem);
    }

    painelHospedagem = newwin(modalAltura, modalLargura,
                              modalY + getbegy(janela),
                              modalX + getbegx(janela));

    wbkgd(painelHospedagem, COLOR_PAIR(COR_INVERSA));
    box(painelHospedagem, 0, 0);

    std::string titulo = "Gerenciar Hospedagens";
    mvwprintw(painelHospedagem, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());

    mvwprintw(painelHospedagem, 3, 2, "Codigo: ");
    mvwaddch(painelHospedagem, 3, 10, '[');
    mvwhline(painelHospedagem, 3, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(painelHospedagem, 3, 11 + TAM_MAX_CODIGO, ']');

    mvwprintw(painelHospedagem, 5, 2, "Nome: ");
    mvwaddch(painelHospedagem, 5, 10, '[');
    mvwhline(painelHospedagem, 5, 11, ' ', TAM_MAX_NOME);
    mvwaddch(painelHospedagem, 5, 11 + TAM_MAX_NOME, ']');

    mvwprintw(painelHospedagem, 7, 2, "Diaria: ");
    mvwaddch(painelHospedagem, 7, 10, '[');
    mvwhline(painelHospedagem, 7, 11, ' ', TAM_MAX_DINHEIRO);
    mvwaddch(painelHospedagem, 7, 11 + TAM_MAX_DINHEIRO, ']');

    mvwprintw(painelHospedagem, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");

    wrefresh(painelHospedagem);
}

void TelaHospedagem::mostrar()
{
    limparTela();
    desenharModal();
}

bool TelaHospedagem::processarHospedagem()
{
    wmove(painelHospedagem, 3, 11);
    std::string codigoStr = campoTexto(painelHospedagem, 3, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty())
        return false;

    wmove(painelHospedagem, 5, 11);
    std::string nomeStr = campoTexto(painelHospedagem, 5, 11, TAM_MAX_NOME);
    if (nomeStr.empty())
        return false;

    wmove(painelHospedagem, 7, 11);
    std::string diariaStr = campoTexto(painelHospedagem, 7, 11, TAM_MAX_DINHEIRO);
    if (diariaStr.empty())
        return false;

    try
    {
        Codigo codigo(codigoStr);
        Nome nome(nomeStr);
        Dinheiro diaria(diariaStr);

        Hospedagem hospedagem(nome, codigo, avaliacao, diaria, destinoCodigo);

        if (servico->criarHospedagem(hospedagem))
        {
            mostrarAlerta("Hospedagem criada com sucesso!");
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

bool TelaHospedagem::executar()
{
    mostrar();
    return processarHospedagem();
}