#include "../../include/telas/TelaRelatorios.hpp"
#include <iomanip>
#include <sstream>

void TelaRelatorios::mostrar() {
    limparTela();
    desenharMenu();
    
    while (true) {
        int ch = wgetch(janela);
        if (ch == '0') break;
        if (ch >= '1' && ch <= '3') {
            processarOpcao(ch - '0');
            limparTela();
            desenharMenu();
        }
    }
}

void TelaRelatorios::desenharMenu() {
    // ...similar ao desenharMenu de outras telas...
    const char* opcoes[] = {
        "1. Relatorio Geral",
        "2. Relatorio por Viagem",
        "3. Relatorio por Destino",
        "0. Voltar"
    };
    // ...desenhar menu...
}

void TelaRelatorios::relatorioPorViagem() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Relatorio de Custos por Viagem ===");

    try {
        std::string codigo = lerInput("Digite o codigo da viagem: ", 3, 2);
        if (codigo.empty()) return;

        Codigo codigoViagem(codigo);
        Viagem* viagem = servicoViagem->buscarViagem(codigoViagem);
        
        if (!viagem) {
            mostrarAlerta("Viagem não encontrada.");
            return;
        }

        std::vector<Destino> destinos = servicoDestino->listarPorViagem(codigoViagem);
        double custoTotal = servicoViagem->calcularCustoViagem(codigoViagem);

        int linha = 3;
        mvwprintw(janela, linha++, 2, "Viagem: %s", viagem->getNome().getValor().c_str());
        mvwprintw(janela, linha++, 2, "Codigo: %s", viagem->getCodigo().getValor().c_str());
        linha++;

        mvwprintw(janela, linha++, 2, "=== Destinos ===");
        for (const auto& destino : destinos) {
            exibirDetalhesDestino(destino);
            linha += 3;
        }

        mvwprintw(janela, linha + 2, 2, "Custo Total da Viagem: R$ %.2f", custoTotal);
        
        delete viagem;
        
        mvwprintw(janela, linha + 4, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaRelatorios::exibirDetalhesDestino(const Destino& destino) {
    int linha = 3;
    mvwprintw(janela, linha++, 2, "Destino: %s", destino.getNome().getValor().c_str());
    mvwprintw(janela, linha++, 2, "Codigo: %s", destino.getCodigo().getValor().c_str());
    mvwprintw(janela, linha++, 2, "Periodo: %s a %s", 
             destino.getDataInicio().getValor().c_str(),
             destino.getDataFim().getValor().c_str());
    linha++;

    // Listar atividades
    std::vector<Atividade> atividades = servicoAtividade->listarPorDestino(destino.getCodigo());
    if (!atividades.empty()) {
        mvwprintw(janela, linha++, 2, "Atividades:");
        double custoAtividades = 0.0;
        
        for (const auto& ativ : atividades) {
            mvwprintw(janela, linha++, 4, "- %s: R$ %s", 
                     ativ.getNome().getValor().c_str(),
                     ativ.getPreco().getValor().c_str());
            custoAtividades += std::stod(ativ.getPreco().getValor());
        }
        
        mvwprintw(janela, linha++, 4, "Total Atividades: R$ %.2f", custoAtividades);
    }
    linha++;

    // Buscar hospedagem
    Hospedagem* hosp = servicoHospedagem->buscarPorDestino(destino.getCodigo());
    if (hosp) {
        mvwprintw(janela, linha++, 2, "Hospedagem:");
        mvwprintw(janela, linha++, 4, "- %s: R$ %s/dia", 
                 hosp->getNome().getValor().c_str(),
                 hosp->getDiaria().getValor().c_str());
        
        // Calcular total de dias
        tm tmInicio = {}, tmFim = {};
        std::string dataInicio = destino.getDataInicio().getValor();
        std::string dataFim = destino.getDataFim().getValor();
        
        tmInicio.tm_mday = std::stoi(dataInicio.substr(0, 2));
        tmInicio.tm_mon = std::stoi(dataInicio.substr(3, 2)) - 1;
        tmInicio.tm_year = std::stoi(dataInicio.substr(6, 2)) + 2000 - 1900;
        
        tmFim.tm_mday = std::stoi(dataFim.substr(0, 2));
        tmFim.tm_mon = std::stoi(dataFim.substr(3, 2)) - 1;
        tmFim.tm_year = std::stoi(dataFim.substr(6, 2)) + 2000 - 1900;
        
        time_t t1 = mktime(&tmInicio);
        time_t t2 = mktime(&tmFim);
        
        int dias = (int)((difftime(t2, t1) / (60 * 60 * 24)) + 1);
        double custoHospedagem = std::stod(hosp->getDiaria().getValor()) * dias;
        
        mvwprintw(janela, linha++, 4, "Total Hospedagem (%d dias): R$ %.2f", 
                 dias, custoHospedagem);
        
        delete hosp;
    }
}

void TelaRelatorios::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            relatorioGeral();
            break;
        case 2:
            relatorioPorViagem();
            break;
        case 3:
            relatorioPorDestino();
            break;
    }
}

void TelaRelatorios::relatorioGeral() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Relatorio Geral ===");

    try {
        std::vector<Viagem> viagens = servicoViagem->listarViagensPorViajante(viajante->getConta().getCodigo());
        if (viagens.empty()) {
            mostrarAlerta("Nenhuma viagem encontrada.");
            return;
        }

        double custoTotal = 0.0;
        int linha = 3;

        for (const auto& viagem : viagens) {
            double custoViagem = servicoViagem->calcularCustoViagem(viagem.getCodigo());
            custoTotal += custoViagem;

            mvwprintw(janela, linha++, 2, "Viagem: %s", viagem.getNome().getValor().c_str());
            mvwprintw(janela, linha++, 4, "Codigo: %s", viagem.getCodigo().getValor().c_str());
            mvwprintw(janela, linha++, 4, "Custo: R$ %.2f", custoViagem);
            linha++;
        }

        mvwprintw(janela, linha++, 2, "----------------------------------------");
        mvwprintw(janela, linha++, 2, "Custo Total de Todas as Viagens: R$ %.2f", custoTotal);
        
        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaRelatorios::relatorioPorDestino() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Relatorio por Destino ===");

    try {
        std::string codigoStr = lerInput("Digite o codigo do destino: ", 3, 2);
        if (codigoStr.empty()) return;

        Codigo codigoDestino(codigoStr);
        Destino* destino = servicoDestino->buscarDestino(codigoDestino);
        
        if (!destino) {
            mostrarAlerta("Destino não encontrado.");
            return;
        }

        int linha = 3;
        exibirDetalhesDestino(*destino);
        
        delete destino;
        
        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}
