#include "../../include/telas/TelaAutenticacao.hpp"
#include "../../include/telas/TelaCadastro.hpp"
#include <cstring>

TelaAutenticacao::TelaAutenticacao(ServicoAutenticacao* srv) 
    : servico(srv), painelLogin(nullptr) {
    layout.camposCentralX = 0;
    layout.camposY = 0;
}

TelaAutenticacao::~TelaAutenticacao() {
    if (painelLogin != nullptr) {
        delwin(painelLogin);
        painelLogin = nullptr;
    }
}

void TelaAutenticacao::desenharLogo() {
    const char* logo[] = {
        "@@@@@@@@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@@@@@@@@",
        " =@@@@@@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@@@@@@- ",
        "*-  #@@@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@@@#  -*",
        "***+  -@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@:  +***",
        "******-  =@@@@@@@@@@@@@% %@@@@@@@@@@@@@=  -******",
        "********+:  =%@@@@@@@@@% %@@@@@@@@@%=  :+********",
        "************-   -%@@@@@% %@@@@@%-   -************",
        "***************=.               .=***************",
        "***********************= =***********************",
        "***********************= =***********************",
        "***********************= =***********************",
        "***********************= =***********************",
        "***********************= =***********************"
    };

    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Centralizar logo
    int logoX = (largura - std::strlen(logo[0])) / 2;
    
    for (int i = 0; i < 13; i++) {
        mvwprintw(janela, layout.logoY + i, logoX, "%s", logo[i]);
    }
    
    // Desenhar título
    std::string titulo = "Sistema de Planejamento de Viagens";
    mvwprintw(janela, layout.logoY + 14, (largura - titulo.length()) / 2, "%s", titulo.c_str());



    wrefresh(janela);
}

void TelaAutenticacao::desenharCamposLogin() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Calcular posições
    layout.camposY = altura - layout.altura - 2;
    layout.camposCentralX = (largura - layout.largura) / 2;
    
    // Desenhar instruções ANTES do painel de login
    std::string instrucao = "F1 = Nova Conta | ESC = Sair";
    mvwprintw(janela, layout.camposY - 2, (largura - instrucao.length()) / 2, "%s", instrucao.c_str());
    
    // Criar painel de login
    if (painelLogin != nullptr) {
        delwin(painelLogin);
    }
    
    painelLogin = subwin(janela, layout.altura, layout.largura,
                        layout.camposY + getbegy(janela),
                        layout.camposCentralX + getbegx(janela));
    
    // Configurar cores e borda
    wbkgd(painelLogin, COLOR_PAIR(COR_INVERSA));
    box(painelLogin, 0, 0);
    
    mvwprintw(painelLogin, 1, 2, "Codigo: ");
    mvwaddch(painelLogin, 1, 10, '[');
    mvwhline(painelLogin, 1, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(painelLogin, 1, 11 + TAM_MAX_CODIGO, ']');
    
    mvwprintw(painelLogin, 3, 2, "Senha:  ");
    mvwaddch(painelLogin, 3, 10, '[');
    mvwhline(painelLogin, 3, 11, ' ', TAM_MAX_SENHA);
    mvwaddch(painelLogin, 3, 11 + TAM_MAX_SENHA, ']');
    
    wrefresh(painelLogin);
    wrefresh(janela);
}

void TelaAutenticacao::mostrarModalCadastro() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Dimensões do modal
    int modalAltura = 12;  // Aumentado para acomodar mais campos
    int modalLargura = 60; // Aumentado para melhor visualização
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;
    
    // Criar janela do modal
    WINDOW* modalCadastro = newwin(modalAltura, modalLargura,
                                  modalY + getbegy(janela),
                                  modalX + getbegx(janela));
                                  
    // Configurar cores e borda
    wbkgd(modalCadastro, COLOR_PAIR(COR_INVERSA));
    box(modalCadastro, 0, 0);
    
    // Título
    std::string titulo = "Criar Nova Conta";
    mvwprintw(modalCadastro, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());
    
    // Campos
    mvwprintw(modalCadastro, 3, 2, "Nome:   ");
    mvwaddch(modalCadastro, 3, 10, '[');
    mvwhline(modalCadastro, 3, 11, ' ', 20);
    mvwaddch(modalCadastro, 3, 31, ']');
    
    mvwprintw(modalCadastro, 5, 2, "Codigo: ");
    mvwaddch(modalCadastro, 5, 10, '[');
    mvwhline(modalCadastro, 5, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(modalCadastro, 5, 11 + TAM_MAX_CODIGO, ']');
    
    mvwprintw(modalCadastro, 7, 2, "Senha:  ");
    mvwaddch(modalCadastro, 7, 10, '[');
    mvwhline(modalCadastro, 7, 11, ' ', TAM_MAX_SENHA);
    mvwaddch(modalCadastro, 7, 11 + TAM_MAX_SENHA, ']');
    
    // Instruções
    mvwprintw(modalCadastro, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");
    
    wrefresh(modalCadastro);
    
    // Ler dados
    std::string nomeStr = campoTexto(modalCadastro, 3, 11, 20);
    if (nomeStr.empty()) {
        delwin(modalCadastro);
        mostrar();
        return;
    }
    
    std::string codigoStr = campoTexto(modalCadastro, 5, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty()) {
        delwin(modalCadastro);
        mostrar();
        return;
    }
    
    std::string senhaStr = campoTexto(modalCadastro, 7, 11, TAM_MAX_SENHA, true);
    if (senhaStr.empty()) {
        delwin(modalCadastro);
        mostrar();
        return;
    }
    
    try {
        Nome nome(nomeStr);
        Codigo codigo(codigoStr);
        Senha senha(senhaStr);
        
        Conta conta(codigo, senha);
        Viajante viajante(nome, conta);
        
        if (servico->cadastrar(viajante)) {
            mostrarAlerta("Conta criada com sucesso!");
        } else {
            mostrarAlerta("Erro ao criar conta!");
        }
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
    
    delwin(modalCadastro);
    mostrar();
}

void TelaAutenticacao::mostrar() {
    limparTela();
    desenharLogo();
    desenharCamposLogin();
}
Viajante* TelaAutenticacao::fazerLogin() {
    mostrar();
    keypad(janela, TRUE);
    
    while (true) {
        wmove(painelLogin, 1, 11);
        wrefresh(painelLogin);
        
        int ch = wgetch(janela);
        
        if (ch == KEY_F(1)) {
            TelaCadastro telaCadastro(servico);
            telaCadastro.executar();
            mostrar();
            continue;
        }
        
        if (ch == 27) { // ESC
            return nullptr;
        }
        
        if (isprint(ch)) {
            // Limpar e ler código
            wmove(painelLogin, 1, 11);
            whline(painelLogin, ' ', TAM_MAX_CODIGO);
            mvwaddch(painelLogin, 1, 11, ch);
            wrefresh(painelLogin);
            
            std::string codigo = (char)ch + campoTexto(painelLogin, 1, 12, TAM_MAX_CODIGO - 1);
            if (codigo.empty()) continue;
            
            // Limpar e ler senha
            wmove(painelLogin, 3, 11);
            whline(painelLogin, ' ', TAM_MAX_SENHA);
            wrefresh(painelLogin);
            
            std::string senha = campoTexto(painelLogin, 3, 11, TAM_MAX_SENHA, true);
            if (senha.empty()) continue;
            
            try {
                Codigo codigoObj(codigo);
                Senha senhaObj(senha);
                
                try {
                    Viajante* viajante = servico->autenticar(codigoObj, senhaObj);
                    if (viajante) {
                        return viajante;
                    }
                }
                catch (const std::runtime_error& e) {
                    mostrarAlerta(e.what());
                    mostrar();
                    continue;  // Continua o loop após mostrar o erro
                }
            }
            catch (const std::exception& e) {
                mostrarAlerta(e.what());
                mostrar();
                continue;  // Continua o loop após mostrar o erro
            }
        }
    }
}