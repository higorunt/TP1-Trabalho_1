#include "../../include/telas/TelaPrincipal.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>

TelaPrincipal::TelaPrincipal(Viajante* v, ServicoViagem* sv, ServicoDestino* sd, 
                             ServicoAtividade* sa, ServicoHospedagem* sh)
    : viajante(v), servicoViagem(sv), servicoDestino(sd), 
      servicoAtividade(sa), servicoHospedagem(sh), painelMenu(nullptr)
{
    layout.centralX = 0;
    layout.centralY = 0;
    telaViagem = new TelaViagem(servicoViagem, viajante);
    telaDestino = new TelaDestino(servicoDestino, servicoViagem, viajante);
    telaAtividade = new TelaAtividade(servicoAtividade, servicoDestino, viajante);
    telaHospedagem = new TelaHospedagem(servicoHospedagem, servicoDestino, viajante);
}

TelaPrincipal::~TelaPrincipal() {
    if (painelMenu != nullptr) {
        delwin(painelMenu);
        painelMenu = nullptr;
    }
    delete telaViagem;
    delete telaDestino;
    delete telaAtividade;
    delete telaHospedagem;
}

void TelaPrincipal::mostrar() {
    limparTela();
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    std::string bemVindo = "Bem-vindo, " + viajante->getNome().getValor();
    mvwprintw(janela, 2, (largura - bemVindo.length()) / 2, "%s", bemVindo.c_str());
    
    desenharMenu();
}

void TelaPrincipal::desenharMenu() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
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
    
    mvwprintw(painelMenu, 1, (layout.largura - 18) / 2, "Menu Principal");
    
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
    
    mvwprintw(painelMenu, layout.altura - 2, 2, "Digite o numero da opcao desejada");
    
    wrefresh(painelMenu);
    wrefresh(janela);
}

void TelaPrincipal::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            telaViagem->mostrar();
            break;
        case 2:
            telaDestino->executar();
            break;
        case 3:
            telaAtividade->mostrar();
            break;
        case 4:
            telaHospedagem->mostrar();
            break;
        case 5: {
            try {
                std::string codigoStr = mostrarInput("Digite o codigo da viagem:");
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
            try {
                std::vector<Viagem> viagens = servicoViagem->listarViagensPorViajante(viajante->getConta().getCodigo());
                if (viagens.empty()) {
                    mostrarAlerta("Nenhuma viagem encontrada.");
                } else {
                    // TODO: Implementar exibição da lista de viagens
                    mostrarAlerta("Funcao em desenvolvimento");
                }
            } catch (const std::exception& e) {
                mostrarAlerta(e.what());
            }
            break;
        }
        case 7: {
            try {
                std::string codigoStr = mostrarInput("Digite o codigo da viagem:");
                if (!codigoStr.empty()) {
                    Codigo codigo(codigoStr);
                    // TODO: Implementar listagem de destinos
                    mostrarAlerta("Funcao em desenvolvimento");
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
        default:
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
