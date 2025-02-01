#include "../../include/telas/TelaPrincipal.hpp"

TelaPrincipal::TelaPrincipal(Viajante* v, ServicoViagem* sv) 
    : viajante(v), servicoViagem(sv), painelMenu(nullptr) {
    layout.centralX = 0;
    layout.centralY = 0;
    telaViagem = new TelaViagem(servicoViagem, viajante);
}

TelaPrincipal::~TelaPrincipal() {
    if (painelMenu != nullptr) {
        delwin(painelMenu);
        painelMenu = nullptr;
    }
    delete telaViagem;
}

void TelaPrincipal::mostrar() {
    limparTela();
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Desenhar cabeçalho
    std::string bemVindo = "Bem-vindo, " + viajante->getNome().getValor();
    mvwprintw(janela, 2, (largura - bemVindo.length()) / 2, "%s", bemVindo.c_str());
    
    desenharMenu();
}

void TelaPrincipal::desenharMenu() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Calcular posições
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
    
    if (painelMenu != nullptr) {
        delwin(painelMenu);
    }
    
    painelMenu = subwin(janela, layout.altura, layout.largura,
                       layout.centralY + getbegy(janela),
                       layout.centralX + getbegx(janela));
    
    wbkgd(painelMenu, COLOR_PAIR(COR_PRINCIPAL));
    box(painelMenu, 0, 0);
    
    // Título do menu
    mvwprintw(painelMenu, 1, (layout.largura - 15) / 2, "Menu de Viagens");
    
    // Opções do menu
    const char* opcoes[] = {
        "1. Gerenciar Viagens",
        "2. Gerenciar Destinos",
        "3. Gerenciar Atividades",
        "4. Gerenciar Hospedagens",
        "5. Consultar Custo de Viagem",
        "6. Listar Minhas Viagens",
        "7. Listar Destinos da Viagem",
        "8. Listar Atividades do Destino",
        "9. Listar Hospedagens do Destino",
        "0. Sair"
    };
    
    for (int i = 0; i < 10; i++) {
        mvwprintw(painelMenu, i + 3, 3, "%s", opcoes[i]);
    }
    
    // Instruções
    mvwprintw(painelMenu, layout.altura - 2, 2, "Digite o numero da opcao desejada");
    
    wrefresh(painelMenu);
    wrefresh(janela);
}

void TelaPrincipal::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            telaViagem->mostrar();  // Usar a TelaViagem para gerenciar viagens
            break;
        case 2:
            mostrarAlerta("Menu Gerenciar Destinos - Em desenvolvimento");
            break;
        case 3:
            mostrarAlerta("Menu Gerenciar Atividades - Em desenvolvimento");
            break;
        case 4:
            mostrarAlerta("Menu Gerenciar Hospedagens - Em desenvolvimento");
            break;
        case 5: {
            // Usar o ServicoViagem para consultar custo
            try {
                std::string codigoStr = mostrarInput("Digite o código da viagem:");
                if (!codigoStr.empty()) {
                    Codigo codigo(codigoStr);
                    double custo = servicoViagem->calcularCustoViagem(codigo);
                    std::string msg = "Custo total da viagem: R$ " + std::to_string(custo);
                    mostrarAlerta(msg);
                }
            } catch (const std::exception& e) {
                mostrarAlerta(e.what());
            }
            break;
        }
        case 6: {
            // Usar o ServicoViagem para listar viagens
            try {
                std::vector<Viagem> viagens = servicoViagem->listarViagensPorViajante(viajante->getConta().getCodigo());
                if (viagens.empty()) {
                    mostrarAlerta("Nenhuma viagem encontrada.");
                } else {
                    // TODO: Implementar uma forma de mostrar a lista de viagens
                    mostrarAlerta("Função em desenvolvimento");
                }
            } catch (const std::exception& e) {
                mostrarAlerta(e.what());
            }
            break;
        }
        case 7: {
            // Usar o ServicoViagem para listar destinos
            try {
                std::string codigoStr = mostrarInput("Digite o código da viagem:");
                if (!codigoStr.empty()) {
                    Codigo codigo(codigoStr);
                    std::vector<Destino> destinos = servicoViagem->listarDestinosPorViagem(codigo);
                    if (destinos.empty()) {
                        mostrarAlerta("Nenhum destino encontrado para esta viagem.");
                    } else {
                        // TODO: Implementar uma forma de mostrar a lista de destinos
                        mostrarAlerta("Função em desenvolvimento");
                    }
                }
            } catch (const std::exception& e) {
                mostrarAlerta(e.what());
            }
            break;
        }
        case 8:
            mostrarAlerta("Atividades do Destino - Em desenvolvimento");
            break;
        case 9:
            mostrarAlerta("Hospedagens do Destino - Em desenvolvimento");
            break;
    }
}

void TelaPrincipal::executar() {
    mostrar();
    
    while (true) {
        int ch = wgetch(janela);
        
        if (ch == '0') break;
        
        if (ch >= '1' && ch <= '9') {
            processarOpcao(ch - '0');
            mostrar();
        }
    }
}