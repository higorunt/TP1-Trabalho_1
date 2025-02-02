#include "../../include/telas/TelaConta.hpp"
#include "../../include/servicos/ServicoConta.hpp"
#include "../../include/dominios/Codigo.hpp"
#include "../../include/dominios/Senha.hpp"

TelaConta::TelaConta(ServicoConta *srv)
    : servico(srv), painelConta(nullptr)
{
}

TelaConta::~TelaConta()
{
    if (painelConta != nullptr)
    {
        delwin(painelConta);
        painelConta = nullptr;
    }
}

void TelaConta::desenharModal()
{
    int altura, largura;
    getmaxyx(janela, altura, largura);

    int modalAltura = 14;
    int modalLargura = 60;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;

    if (painelConta != nullptr)
    {
        delwin(painelConta);
    }

    painelConta = newwin(modalAltura, modalLargura,
                         modalY + getbegy(janela),
                         modalX + getbegx(janela));

    wbkgd(painelConta, COLOR_PAIR(COR_INVERSA));
    box(painelConta, 0, 0);

    std::string titulo = "Gerenciar Conta";
    mvwprintw(painelConta, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());

    mvwprintw(painelConta, 3, 2, "Codigo: ");
    mvwaddch(painelConta, 3, 10, '[');
    mvwhline(painelConta, 3, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(painelConta, 3, 11 + TAM_MAX_CODIGO, ']');

    mvwprintw(painelConta, 5, 2, "Senha: ");
    mvwaddch(painelConta, 5, 10, '[');
    mvwhline(painelConta, 5, 11, ' ', TAM_MAX_SENHA);
    mvwaddch(painelConta, 5, 11 + TAM_MAX_SENHA, ']');

    mvwprintw(painelConta, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");

    wrefresh(painelConta);
}

void TelaConta::mostrar()
{
    limparTela();
    desenharModal();
}

bool TelaConta::processarConta()
{
    wmove(painelConta, 3, 11);
    std::string codigoStr = campoTexto(painelConta, 3, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty())
        return false;

    wmove(painelConta, 5, 11);
    std::string senhaStr = campoTexto(painelConta, 5, 11, TAM_MAX_SENHA);
    if (senhaStr.empty())
        return false;

    try
    {
        Codigo codigo(codigoStr);
        Senha senha(senhaStr);

        Conta conta(codigo, senha);

        if (servico->criarConta(conta))
        {
            mostrarAlerta("Conta criada com sucesso!");
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

bool TelaConta::executar()
{
    mostrar();
    return processarConta();
}
