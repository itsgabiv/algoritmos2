# DESCRIÇÃO DO SISTEMA DE GESTÃO DE PNEUS

## Visão Geral

O programa, escrito em C, implementa um sistema completo para controle e gestão de pneus de veículos comerciais de diferentes portes. Ele utiliza structs para organizar os dados de forma estruturada: uma estrutura `Veiculo` armazena informações específicas do veículo (tipo, quantidade e números identificadores de pneus e estepes) e outra estrutura `Usuario` gerencia os dados de autenticação para controle de acesso ao sistema.

## Inicialização e Autenticação

Ao iniciar, a função `inicializar()` define os valores padrão para todas as variáveis globais e estabelece um usuário administrador com credenciais fixas (usuário: "admin", senha: "1234"). O sistema implementa um mecanismo de segurança através da função `fazerLogin()`, que permite até três tentativas de autenticação antes de encerrar o programa, garantindo controle de acesso básico.

## Seleção e Configuração de Veículos

Após a autenticação bem-sucedida, o programa solicita a escolha do tipo de veículo através da função `escolherTipo()`. Esta seleção é fundamental pois determina automaticamente a quantidade de pneus que serão gerenciados:
- **TOCO**: 4 pneus
- **TRUCK**: 6 pneus  
- **CARRETA SIMPLES**: 8 pneus
- **CARRETA 3 EIXOS**: 10 pneus

## Cadastro e Validação

No processo de cadastro executado pelas funções `cadastrarPneus()` e `cadastrarSteps()`, cada número informado pelo usuário passa por rigorosa validação através da função `existeNumero()`. Esta validação garante que todos os números sejam positivos e únicos em todo o sistema, evitando duplicações entre pneus e estepes. O sistema utiliza laços `do-while` para garantir que apenas dados válidos sejam aceitos.

## Funcionalidades do Menu Principal

O menu principal oferece quatro opções principais através de uma interface intuitiva:

1. **Listar pneus e steps**: A função `listarPneusESteps()` exibe de forma organizada todos os números cadastrados, separando visualmente pneus regulares de estepes.

2. **Sistema de rodízio**: A função `rodizio()` implementa um sistema sofisticado que permite trocar a posição de dois elementos quaisquer (pneus ou steps) escolhidos pelo usuário. O algoritmo traduz posições globais para índices internos e realiza a troca mantendo a integridade dos dados.

3. **Visualização gráfica**: A função `mostrarDesenho()` gera diagramas em ASCII que representam visualmente a distribuição dos pneus de acordo com o tipo de veículo, facilitando a compreensão espacial do arranjo dos pneus.

4. **Encerramento seguro**: Opção para finalizar o programa de forma controlada.

## Arquitetura e Estruturas de Dados

A lógica do código combina eficientemente:
- **Laços de repetição** para controle de fluxo e validação contínua
- **Estruturas condicionais** para tomada de decisões e validações
- **Manipulação de strings** para comparação de credenciais e formatação de saída
- **Arrays estáticos** para armazenamento organizado dos dados
- **Variáveis globais** para facilitar o compartilhamento de dados entre funções

## Características Técnicas

O sistema apresenta as seguintes características técnicas:
- **Controle de entrada robusto** com validação em tempo real
- **Interface de usuário interativa** com menus claros e feedback imediato
- **Representação visual** através de ASCII art para melhor compreensão
- **Arquitetura modular** com funções especializadas para cada funcionalidade
- **Tratamento de erros** com mensagens informativas para o usuário

## Aplicação Prática

Este sistema é ideal para oficinas mecânicas, frotas de transporte e empresas de logística que necessitam controlar e organizar o rodízio de pneus em veículos comerciais, proporcionando maior vida útil dos pneus e melhor gestão de manutenção.

---

**Desenvolvido por:** Jean Lucas, Gabriela, Jesse
