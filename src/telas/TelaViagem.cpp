// src/telas/TelaViagem.cpp
#include "../../include/telas/TelaViagem.hpp"
#include <iomanip>
#include <sstream>

void TelaViagem::mostrar() {
    limparTela();
    desenharMenu();
    
    while (true) {
        int ch = wgetch(janela);
        
        if (ch == '0') break;
        
        if (ch >= '1' && ch <= '5') {
            processarOpcao(ch - '0');
            limparTela();
            desenharMenu();
        }
    }
}

void TelaViagem::desenharMenu() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Calcular posições
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
    
    if (painelViagem != nullptr) {
        delwin(painelViagem);
    }
    
    painelViagem = subwin(janela, layout.altura, layout.largura,
                         layout.centralY + getbegy(janela),
                         layout.centralX + getbegx(janela));
    
    wbkgd(painelViagem, COLOR_PAIR(COR_PRINCIPAL));
    box(painelViagem, 0, 0);
    
    // Título do menu
    mvwprintw(painelViagem, 1, (layout.largura - 16) / 2, "Gerenciar Viagens");
    
    // Opções do menu
    const char* opcoes[] = {
        "1. Criar nova viagem",
        "2. Listar minhas viagens",
        "3. Editar viagem",
        "4. Excluir viagem",
        "5. Calcular custo da viagem",
        "0. Voltar"
    };
    
    for (int i = 0; i < 6; i++) {
        mvwprintw(painelViagem, i + 3, 3, "%s", opcoes[i]);
    }
    
    // Instruções
    mvwprintw(painelViagem, layout.altura - 2, 2, "Digite o numero da opcao desejada");
    
    wrefresh(painelViagem);
    wrefresh(janela);
}

void TelaViagem::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            criarViagem();
            break;
        case 2:
            listarViagens();
            break;
        case 3:
            editarViagem();
            break;
        case 4:
            excluirViagem();
            break;
        case 5:
            calcularCustoViagem();
            break;
    }
}

// src/telas/TelaViagem.cpp
void TelaViagem::criarViagem() {
    // Limpar a tela atual
    wclear(janela);
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Criar Nova Viagem ===");

    // Solicitar nome
    std::string nome = mostrarInput("Nome da viagem: ");
    if (nome.empty()) return;

    // Solicitar código
    std::string codigo = mostrarInput("Codigo da viagem (XXX): ");
    if (codigo.empty()) return;

    // Solicitar avaliação
    std::string avalStr = mostrarInput("Avaliacao (1-5): ");
    if (avalStr.empty()) return;

    try {
        int avaliacao = std::stoi(avalStr);
        Nome nomeViagem(nome);
        Codigo codigoViagem(codigo);
        Avaliacao avaliacaoViagem(avaliacao);

        Viagem novaViagem(nomeViagem, codigoViagem, avaliacaoViagem, viajante->getConta());
        
        if (servico->criarViagem(novaViagem)) {
            mostrarAlerta("Viagem criada com sucesso!");
        } else {
            mostrarAlerta("Erro ao criar viagem.");
        }
    } catch (const std::invalid_argument& e) {
        mostrarAlerta(e.what());
    }
}

void TelaViagem::listarViagens() {
    wclear(janela);
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Minhas Viagens ===");

    try {
        std::vector<Viagem> viagens = servico->listarViagensPorViajante(viajante->getConta().getCodigo());
        
        if (viagens.empty()) {
            mostrarAlerta("Nenhuma viagem encontrada.");
            return;
        }

        int linha = 3;
        for (const auto& viagem : viagens) {
            std::string codigoStr = "Codigo: " + viagem.getCodigo().getValor();
            std::string nomeStr = "Nome: " + viagem.getNome().getValor();
            std::string avalStr = "Avaliacao: " + std::to_string(viagem.getAvaliacao().getValor());
            
            mvwprintw(janela, linha, 2, "%s", codigoStr.c_str());
            mvwprintw(janela, linha + 1, 2, "%s", nomeStr.c_str());
            mvwprintw(janela, linha + 2, 2, "%s", avalStr.c_str());
            linha += 4;
        }

        wrefresh(janela);
        wgetch(janela); // Aguardar tecla para continuar
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaViagem::editarViagem() {
    wclear(janela);
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Editar Viagem ===");

    std::string codigo = mostrarInput("Digite o codigo da viagem: ");
    if (codigo.empty()) return;

    try {
        Codigo codigoViagem(codigo);
        Viagem* viagem = servico->buscarViagem(codigoViagem);
        
        if (!viagem) {
            mostrarAlerta("Viagem nao encontrada.");
            return;
        }

        // Solicitar novos dados
        std::string novoNome = mostrarInput("Novo nome (" + viagem->getNome().getValor() + "): ");
        if (novoNome.empty()) novoNome = viagem->getNome().getValor();

        std::string novaAvalStr = mostrarInput("Nova avaliacao (" + 
            std::to_string(viagem->getAvaliacao().getValor()) + "): ");
        
        try {
            Nome nome(novoNome);
            Avaliacao avaliacao(novaAvalStr.empty() ? 
                              viagem->getAvaliacao().getValor() : 
                              std::stoi(novaAvalStr));

            Viagem viagemAtualizada = *viagem;
            viagemAtualizada.setNome(nome);
            viagemAtualizada.setAvaliacao(avaliacao);

            if (servico->atualizarViagem(viagemAtualizada)) {
                mostrarAlerta("Viagem atualizada com sucesso!");
            } else {
                mostrarAlerta("Erro ao atualizar viagem.");
            }
        } catch (const std::invalid_argument& e) {
            mostrarAlerta(e.what());
        }

        delete viagem;
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaViagem::excluirViagem() {
    wclear(janela);
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Excluir Viagem ===");

    std::string codigo = mostrarInput("Digite o codigo da viagem: ");
    if (codigo.empty()) return;

    try {
        Codigo codigoViagem(codigo);
        
        // Confirmar exclusão
        std::string confirma = mostrarInput("Tem certeza? (S/N): ");
        if (confirma == "S" || confirma == "s") {
            if (servico->excluirViagem(codigoViagem)) {
                mostrarAlerta("Viagem excluida com sucesso!");
            } else {
                mostrarAlerta("Erro ao excluir viagem.");
            }
        }
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaViagem::calcularCustoViagem() {
    wclear(janela);
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Calcular Custo da Viagem ===");

    std::string codigo = mostrarInput("Digite o codigo da viagem: ");
    if (codigo.empty()) return;

    try {
        Codigo codigoViagem(codigo);
        double custoTotal = servico->calcularCustoViagem(codigoViagem);
        
        std::stringstream ss;
        ss << "Custo total: R$ " << std::fixed << std::setprecision(2) << custoTotal;
        mostrarAlerta(ss.str());
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}