#include "../../include/telas/TelaPrincipal.hpp"

TelaPrincipal::TelaPrincipal(Viajante *v,
                             ServicoViagem *sv,
                             ServicoDestino *sd,
                             ServicoAtividade *sa,
                             ServicoHospedagem *sh,
                             ServicoViajante *svt,
                             ServicoConta *sc)
    : viajante(v),
      servicoViagem(sv),
      servicoDestino(sd),
      servicoAtividade(sa),
      servicoHospedagem(sh),
      servicoViajante(svt),
      servicoConta(sc),
      telaViagem(nullptr),
      telaDestino(nullptr),
      telaAtividade(nullptr),
      telaHospedagem(nullptr),
      telaViajante(nullptr),
      telaConta(nullptr),
      painelMenu(nullptr)
{
    // Inicializa as telas
    telaViagem = new TelaViagem(servicoViagem);
    telaDestino = new TelaDestino(servicoDestino);
    telaAtividade = new TelaAtividade(servicoAtividade);
    telaHospedagem = new TelaHospedagem(servicoHospedagem);
    telaViajante = new TelaViajante(servicoViajante);
    telaConta = new TelaConta(servicoConta);
}

TelaPrincipal::~TelaPrincipal()
{
    if (painelMenu != nullptr)
    {
        delwin(painelMenu);
        painelMenu = nullptr;
    }

    // Libera a memória das telas
    if (telaViagem != nullptr)
        delete telaViagem;
    if (telaDestino != nullptr)
        delete telaDestino;
    if (telaAtividade != nullptr)
        delete telaAtividade;
    if (telaHospedagem != nullptr)
        delete telaHospedagem;
    if (telaViajante != nullptr)
        delete telaViajante;
    if (telaConta != nullptr)
        delete telaConta;
}

void TelaPrincipal::desenharMenu()
{
    int altura, largura;
    getmaxyx(janela, altura, largura);

    layout.centralX = (largura - layout.largura) / 2;
    layout.centralY = (altura - layout.altura) / 2;

    if (painelMenu != nullptr)
    {
        delwin(painelMenu);
    }

    painelMenu = newwin(layout.altura, layout.largura, layout.centralY, layout.centralX);
    wbkgd(painelMenu, COLOR_PAIR(COR_INVERSA));
    box(painelMenu, 0, 0);

    std::string titulo = "Menu Principal";
    mvwprintw(painelMenu, 1, (layout.largura - titulo.length()) / 2, "%s", titulo.c_str());

    mvwprintw(painelMenu, layout.menuY, 2, "1. Gerenciar Viagens");
    mvwprintw(painelMenu, layout.menuY + 2, 2, "2. Gerenciar Destinos");
    mvwprintw(painelMenu, layout.menuY + 4, 2, "3. Gerenciar Atividades");
    mvwprintw(painelMenu, layout.menuY + 6, 2, "4. Gerenciar Hospedagens");
    mvwprintw(painelMenu, layout.menuY + 8, 2, "5. Gerenciar Viajante");
    mvwprintw(painelMenu, layout.menuY + 10, 2, "6. Gerenciar Conta");
    mvwprintw(painelMenu, layout.menuY + 12, 2, "0. Sair");

    mvwprintw(painelMenu, layout.altura - 2, 2, "Escolha uma opção: ");

    wrefresh(painelMenu);
}

void TelaPrincipal::processarOpcao(int opcao)
{
    switch (opcao)
    {
    case 1:
        telaViagem->executar();
        break;
    case 2:
        telaDestino->executar();
        break;
    case 3:
        telaAtividade->executar();
        break;
    case 4:
        telaHospedagem->executar();
        break;
    case 5:
        telaViajante->executar();
        break;
    case 6:
        telaConta->executar();
        break;
    case 0:
        mostrarAlerta("Saindo do sistema...");
        break;
    default:
        mostrarAlerta("Opção inválida!");
        break;
    }
}

void TelaPrincipal::mostrar()
{
    limparTela();
    desenharMenu();
}

void TelaPrincipal::executar()
{
    int opcao = -1;
    while (opcao != 0)
    {
        mostrar();
        opcao = campoInteiro(painelMenu, layout.altura - 2, 20, 1);
        processarOpcao(opcao);
    }
}