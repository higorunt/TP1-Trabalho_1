#include "../../include/telas/TelaAtividade.hpp"
#include "../../include/entidades/Atividade.hpp"
#include "../../include/servicos/ServicoAtividade.hpp"

TelaAtividade::TelaAtividade(ServicoAtividade *srv)
    : servico(srv), painelAtividade(nullptr)
{
}

TelaAtividade::~TelaAtividade()
{
    if (painelAtividade != nullptr)
    {
        delwin(painelAtividade);
        painelAtividade = nullptr;
    }
}

void TelaAtividade::desenharModal()
{
    int altura, largura;
    getmaxyx(janela, altura, largura);

    int modalAltura = 14;
    int modalLargura = 60;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;

    if (painelAtividade != nullptr)
    {
        delwin(painelAtividade);
    }

    painelAtividade = newwin(modalAltura, modalLargura,
                             modalY + getbegy(janela),
                             modalX + getbegx(janela));

    wbkgd(painelAtividade, COLOR_PAIR(COR_INVERSA));
    box(painelAtividade, 0, 0);

    std::string titulo = "Gerenciar Atividades";
    mvwprintw(painelAtividade, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());

    mvwprintw(painelAtividade, 3, 2, "Codigo: ");
    mvwaddch(painelAtividade, 3, 10, '[');
    mvwhline(painelAtividade, 3, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(painelAtividade, 3, 11 + TAM_MAX_CODIGO, ']');

    mvwprintw(painelAtividade, 5, 2, "Nome: ");
    mvwaddch(painelAtividade, 5, 10, '[');
    mvwhline(painelAtividade, 5, 11, ' ', TAM_MAX_NOME);
    mvwaddch(painelAtividade, 5, 11 + TAM_MAX_NOME, ']');

    mvwprintw(painelAtividade, 7, 2, "Data: ");
    mvwaddch(painelAtividade, 7, 10, '[');
    mvwhline(painelAtividade, 7, 11, ' ', TAM_MAX_DATA);
    mvwaddch(painelAtividade, 7, 11 + TAM_MAX_DATA, ']');

    mvwprintw(painelAtividade, 9, 2, "Horario: ");
    mvwaddch(painelAtividade, 9, 11, '[');
    mvwhline(painelAtividade, 9, 12, ' ', TAM_MAX_HORARIO);
    mvwaddch(painelAtividade, 9, 12 + TAM_MAX_HORARIO, ']');

    mvwprintw(painelAtividade, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");

    wrefresh(painelAtividade);
}

void TelaAtividade::mostrar()
{
    limparTela();
    desenharModal();
}

bool TelaAtividade::processarAtividade()
{
    wmove(painelAtividade, 3, 11);
    std::string codigoStr = campoTexto(painelAtividade, 3, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty())
        return false;

    wmove(painelAtividade, 5, 11);
    std::string nomeStr = campoTexto(painelAtividade, 5, 11, TAM_MAX_NOME);
    if (nomeStr.empty())
        return false;

    wmove(painelAtividade, 7, 11);
    std::string dataStr = campoTexto(painelAtividade, 7, 11, TAM_MAX_DATA);
    if (dataStr.empty())
        return false;

    wmove(painelAtividade, 9, 12);
    std::string horarioStr = campoTexto(painelAtividade, 9, 12, TAM_MAX_HORARIO);
    if (horarioStr.empty())
        return false;

    try
    {
        Codigo codigo(codigoStr);
        Nome nome(nomeStr);
        Data data(dataStr);
        Horario horario(horarioStr);

        Atividade atividade(codigo, nome, data, horario);

        if (servico->criarAtividade(atividade))
        {
            mostrarAlerta("Atividade criada com sucesso!");
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

bool TelaAtividade::executar()
{
    mostrar();
    return processarAtividade();
}