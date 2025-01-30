// src/telas/TelaPrincipal.cpp
#include "../../include/telas/TelaPrincipal.hpp"

TelaPrincipal::TelaPrincipal(Viajante* v) : viajante(v), painelMenu(nullptr) {
    layout.centralX = 0;
    layout.centralY = 0;
}

TelaPrincipal::~TelaPrincipal() {
    if (painelMenu != nullptr) {
        delwin(painelMenu);
        painelMenu = nullptr;
    }
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

// src/telas/TelaPrincipal.cpp
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
            mostrarAlerta("Menu Gerenciar Viagens - Em desenvolvimento");
            // TODO: Submenu com: Criar, Ler, Atualizar e Excluir Viagem
            break;
        case 2:
            mostrarAlerta("Menu Gerenciar Destinos - Em desenvolvimento");
            // TODO: Submenu com: Criar, Ler, Atualizar e Excluir Destino
            break;
        case 3:
            mostrarAlerta("Menu Gerenciar Atividades - Em desenvolvimento");
            // TODO: Submenu com: Criar, Ler, Atualizar e Excluir Atividade
            break;
        case 4:
            mostrarAlerta("Menu Gerenciar Hospedagens - Em desenvolvimento");
            // TODO: Submenu com: Criar, Ler, Atualizar e Excluir Hospedagem
            break;
        case 5:
            mostrarAlerta("Consulta de Custo - Em desenvolvimento");
            // TODO: Implementar consulta de custo de viagem
            break;
        case 6:
            mostrarAlerta("Minhas Viagens - Em desenvolvimento");
            // TODO: Listar viagens do viajante atual
            break;
        case 7:
            mostrarAlerta("Destinos da Viagem - Em desenvolvimento");
            // TODO: Listar destinos de uma viagem selecionada
            break;
        case 8:
            mostrarAlerta("Atividades do Destino - Em desenvolvimento");
            // TODO: Listar atividades de um destino selecionado
            break;
        case 9:
            mostrarAlerta("Hospedagens do Destino - Em desenvolvimento");
            // TODO: Listar hospedagens de um destino selecionado
            break;
    }
}


void TelaPrincipal::executar() {
    mostrar();
    
    while (true) {
        int ch = wgetch(janela);
        
        if (ch == '0') break;
        
        if (ch >= '1' && ch <= '5') {
            processarOpcao(ch - '0');
            mostrar();
        }
    }
}