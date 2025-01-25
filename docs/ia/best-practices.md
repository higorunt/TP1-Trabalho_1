# **Documentação das Práticas de Laboratório**

## **LABORATÓRIO 9**

### **Atividades:**

1. **Criar o arquivo `interfaces.hpp`:**
   - Navegue para: `File ? New ? File...`.
   - Selecione: `C/C++ header` e informe o nome do arquivo como `interfaces.hpp`.
   - Marque a opção: `Add file to active project in build target(s)`.
   - Escolha: `All` e clique em `Finish`.

2. **Projetar e construir declarações de interfaces compostas por métodos abstratos:**
   - Declarações de interfaces:
     ```cpp
     class IExemplo {
     public:
         virtual void metodoExemplo() = 0;  // Método abstrato
         virtual ~IExemplo() {}  // Destrutor virtual
     };
     ```

3. **Documentar as interfaces usando a ferramenta Doxygen:**
   - Exemplo de documentação:
     ```cpp
     /**
      * @brief Interface para demonstração de métodos abstratos.
      */
     class IExemplo {
     public:
         /**
          * @brief Método abstrato de exemplo.
          */
         virtual void metodoExemplo() = 0;
         virtual ~IExemplo() {}
     };
     ```

---

## **LABORATÓRIO 10**

### **Atividades:**

1. **Criar os arquivos `stubs.hpp`, `stubs.cpp`, `controladoras.hpp` e `controladoras.cpp`:**
   - Para `controladoras.hpp`:
     - Navegue para: `File ? New ? File...`, selecione `C/C++ header` e informe o nome do arquivo.
   - Para `controladoras.cpp`:
     - Navegue para: `File ? New ? File...`, selecione `C/C++ source` e informe o nome do arquivo.
   - Marque a opção: `Add file to active project in build target(s)`, selecione `All` e clique em `Finish`.

2. **Classe Stub:**
   - Código em `stubs.hpp`:
     ```cpp
     class StubLNAutenticacao : public ILNAutenticacao {
     private:
         const static int TRIGGER_FALHA = 67890;
         const static int TRIGGER_ERRO_SISTEMA = 78901;
     public:
         bool autenticar(const Matricula&, const Senha&);
     };
     ```
   - Código em `stubs.cpp`:
     ```cpp
     const int StubLNAutenticacao::TRIGGER_FALHA;
     const int StubLNAutenticacao::TRIGGER_ERRO_SISTEMA;

     bool StubLNAutenticacao::autenticar(const Matricula &matricula, const Senha &senha) {
         std::cout << "\nStubLNAutenticacao::autenticar" << std::endl;
         std::cout << "Matricula = " << matricula.getValor() << std::endl;
         std::cout << "Senha = " << senha.getValor() << std::endl;

         switch (matricula.getValor()) {
             case TRIGGER_FALHA:
                 return false;
             case TRIGGER_ERRO_SISTEMA:
                 throw std::runtime_error("Erro de sistema");
         }
         return true;
     }
     ```

3. **Classe Controladora:**
   - Código em `controladoras.hpp`:
     ```cpp
     class CntrIUAutenticacao : public IUAutenticacao {
     private:
         ILNAutenticacao *cntrLNAutenticacao;
     public:
         bool autenticar(Matricula*);
         void setCntrLNAutenticacao(ILNAutenticacao*);
     };

     void inline CntrIUAutenticacao::setCntrLNAutenticacao(ILNAutenticacao *cntrLNAutenticacao) {
         this->cntrLNAutenticacao = cntrLNAutenticacao;
     }
     ```
   - Código em `controladoras.cpp`:
     ```cpp
     bool CntrIUAutenticacao::autenticar(Matricula *matricula) {
         Senha senha;
         int entrada;

         while (true) {
             std::cout << "\nAutenticacao de usuario." << std::endl;
             try {
                 std::cout << "Digite a matricula: ";
                 std::cin >> entrada;
                 matricula->setValor(entrada);

                 std::cout << "Digite a senha: ";
                 std::cin >> entrada;
                 senha.setValor(entrada);
                 break;
             } catch (const std::invalid_argument &exp) {
                 std::cout << "\nDado em formato incorreto." << std::endl;
             }
         }

         return cntrLNAutenticacao->autenticar(*matricula, senha);
     }
     ```

4. **Código em `main.cpp`:**
   ```cpp
   int main() {
       IUAutenticacao *cntrIUAutenticacao = new CntrIUAutenticacao();
       ILNAutenticacao *stubLNAutenticacao = new StubLNAutenticacao();

       cntrIUAutenticacao->setCntrLNAutenticacao(stubLNAutenticacao);

       bool resultado;
       Matricula matricula;

       while (true) {
           std::cout << "\nTela inicial de sistema." << std::endl;
           try {
               resultado = cntrIUAutenticacao->autenticar(&matricula);
           } catch (const std::runtime_error &exp) {
               std::cout << "Erro de sistema." << std::endl;
               break;
           }

           if (resultado) {
               std::cout << "\nSucesso na autenticacao." << std::endl;
               std::cout << "Matricula = " << matricula.getValor() << std::endl;
               break;
           } else {
               std::cout << "\nErro na autenticacao." << std::endl;
               break;
           }
       }

       delete cntrIUAutenticacao;
       delete stubLNAutenticacao;
       return 0;
   }
   ```

---

## **LABORATÓRIO 11**

### **Atividades:**

1. **Criar os arquivos `containers.hpp` e `containers.cpp`:**
   - Para `containers.hpp`: 
     - Navegue para: `File ? New ? File...`, selecione `C/C++ header` e informe o nome do arquivo.
   - Para `containers.cpp`: 
     - Navegue para: `File ? New ? File...`, selecione `C/C++ source` e informe o nome do arquivo.
   - Marque a opção: `Add file to active project in build target(s)`, selecione `All` e clique em `Finish`.

2. **Classe Container:**
   - Código em `containers.hpp`:
     ```cpp
     class ContainerUsuario {
     private:
         std::list<Usuario> container;
     public:
         bool incluir(Usuario);
         bool remover(Matricula);
         bool pesquisar(Usuario*);
         bool atualizar(Usuario);
     };
     ```
   - Código em `containers.cpp`:
     ```cpp
     bool ContainerUsuario::incluir(Usuario usuario) {
         for (auto &elemento : container) {
             if (elemento.getMatricula().getValor() == usuario.getMatricula().getValor()) {
                 return false;
             }
         }
         container.push_back(usuario);
         return true;
     }

     bool ContainerUsuario::remover(Matricula matricula) {
         for (auto it = container.begin(); it != container.end(); ++it) {
             if (it->getMatricula().getValor() == matricula.getValor()) {
                 container.erase(it);
                 return true;
             }
         }
         return false;
     }

     bool ContainerUsuario::pesquisar(Usuario *usuario) {
         for (auto &elemento : container) {
             if (elemento.getMatricula().getValor() == usuario->getMatricula().getValor()) {
                 *usuario = elemento;
                 return true;
             }
         }
         return false;
     }

     bool ContainerUsuario::atualizar(Usuario usuario) {
         for (auto &elemento : container) {
             if (elemento.getMatricula().getValor() == usuario.getMatricula().getValor()) {
                 elemento = usuario;
                 return true;
             }
         }
         return false;
     }
     ```

3. **Instanciar e interagir com o container na `main`:**
   ```cpp
   ContainerUsuario container;
   bool resultado = container.incluir(usuario_1);
   if (!resultado) {
       std::cout << "Erro na inclusao" << std::endl;
   } else {
       std::cout << "Sucesso na inclusao" << std::endl;
   }
   ```

---

## **LABORATÓRIO 12**

### **Atividades:**

1. **Classe Container com SQLite:**
   - Código adaptado:
     ```cpp
     void Container::conectar() {
         rc = sqlite3_open(nomeBancoDados, &bd);
         if (rc != SQLITE_OK) {
             throw EErroPersistencia("Erro na conexao ao banco de dados");
         }
     }

     void Container::desconectar() {
         rc = sqlite3_close(bd);
         if (rc != SQLITE_OK) {
             throw EErroPersistencia("Erro na desconexao ao banco de dados");
         }
     }

     void Container::executar() {
         conectar();
         rc = sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem);
         if (rc != SQLITE_OK) {
             sqlite3_free(mensagem);
             desconectar();
             throw EErroPersistencia("Erro na execucao do comando SQL");
         }
         desconectar();
     }
     ```

---
