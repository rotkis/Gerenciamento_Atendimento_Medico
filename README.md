# Gerenciador de Atendimento Médico

Este projeto implementa um sistema de gerenciamento de atendimento médico com diversas funcionalidades para o cadastro, atendimento e pesquisa de pacientes, além de persistência de dados e um recurso para desfazer ações.

## Estrutura do Projeto e Explicação dos Códigos

O projeto é estruturado em módulos, cada um responsável por uma parte específica da funcionalidade do sistema.

### 1. `arquivo.c` e `arquivo.h`

-   **`arquivo.c`**: Contém as implementações das funções para carregar os dados dos pacientes de um arquivo texto para a lista de pacientes (`carregar_pacientes`) e para salvar os dados da lista de pacientes em um arquivo texto (`salvar_pacientes`). As funções manipulam arquivos utilizando as funções da biblioteca `stdio.h` (`fopen`, `fgets`, `sscanf`, `fprintf`, `fclose`). A leitura do arquivo assume um formato específico para os dados de cada paciente (nome;idade;rg;dia;mes;ano), que é interpretado pela função `sscanf`.
-   **`arquivo.h`**: Declara os protótipos das funções implementadas em `arquivo.c` (`carregar_pacientes` e `salvar_pacientes`). A inclusão deste arquivo em outros módulos permite que eles utilizem essas funções sem conhecer os detalhes de sua implementação. Ele também inclui o arquivo `cadastro.h`, pois as funções de arquivo interagem com a estrutura de dados `Lista` definida lá.

### 2. `atendimento_prioritario.c` e `atendimento_prioritario.h`

-   **`atendimento_prioritario.c`**: Implementa uma fila de atendimento prioritário utilizando a estrutura de dados Heap (especificamente um heap máximo). As funções incluem `inicializar_heap` para preparar a estrutura, funções auxiliares para navegar no heap (`indice_pai`, `indice_filho_esq`, `indice_filho_dir`), `heapify` para manter a propriedade do heap, `inserir_heap` para adicionar um paciente à fila prioritária (com base na idade), `remover_heap` para obter o paciente mais prioritário (mais idoso) e `mostrar_heap` para exibir os pacientes na fila prioritária.
-   **`atendimento_prioritario.h`**: Define a estrutura `Heap` (um array de ponteiros para `Registro` e um inteiro para a quantidade de elementos) e declara os protótipos das funções implementadas em `atendimento_prioritario.c`. Define também uma constante `CAPACIDADE_MAX` para limitar o tamanho do heap. Inclui `cadastro.h` para ter acesso à definição da estrutura `Registro`.

### 3. `atendimento.c` e `atendimento.h`

-   **`atendimento.c`**: Implementa uma fila duplamente encadeada para o atendimento comum. Define as estruturas `EFila` (nó da fila com um `Registro` e ponteiros para o próximo e anterior) e `Fila` (cabeça, cauda e quantidade de elementos). As funções incluem `cria_Efila` para criar um novo nó, `cria_fila` para criar uma nova fila, `enfileirar` para adicionar um paciente ao final da fila, `desenfileirar` para remover e retornar o paciente do início da fila, e `mostrar_fila` para exibir os pacientes na fila.
-   **`atendimento.h`**: Define as estruturas `EFila` e `Fila` e declara os protótipos das funções implementadas em `atendimento.c`. Inclui `cadastro.h` para ter acesso à definição da estrutura `Registro`.

### 4. `cadastro.c` e `cadastro.h`

-   **`cadastro.c`**: Implementa as funcionalidades de cadastro de pacientes utilizando uma lista encadeada. Define as estruturas `Elista` (nó da lista com um `Registro` e um ponteiro para o próximo nó) e `Lista` (ponteiro para o início da lista e quantidade de elementos). As funções incluem `criar_lista` para inicializar uma lista vazia, `criar_Elista` para criar um novo nó, `cadastrar_paciente` para adicionar um paciente à lista mantendo-a ordenada por RG, `remover_paciente` para remover um paciente da lista pelo RG, `buscar_paciente` para encontrar um paciente pelo RG, `editar_paciente` para modificar os dados de um paciente, `mostrar_paciente` para exibir todos os pacientes na lista e `liberar_lista` para desalocar toda a memória utilizada pela lista e seus elementos.
-   **`cadastro.h`**: Define as estruturas `Data` (dia, mês, ano) e `Registro` (nome, RG, idade, um ponteiro para `Data`), além das estruturas `Elista` e `Lista`. Declara os protótipos das funções implementadas em `cadastro.c`.

### 5. `desfazer.c` e `desfazer.h`

-   **`desfazer.c`**: Implementa uma pilha para armazenar as operações realizadas no atendimento comum, permitindo a funcionalidade de desfazer. Define as estruturas `Operacao` (tipo da operação e um ponteiro para o `Registro` envolvido) e `EPilha` (nó da pilha com uma `Operacao` e um ponteiro para o próximo nó), além da estrutura `Pilha` (ponteiro para o topo e quantidade de elementos). As funções incluem `criar_pilha` para criar uma nova pilha, `empilhar` para adicionar uma operação ao topo da pilha, `desempilhar` para remover e retornar a operação do topo, `mostrar_operacoes` para exibir o histórico de operações e `liberar_pilha` para desalocar a memória da pilha.
-   **`desfazer.h`**: Define a enumeração `TipoOperacao` (para enfileirar e desenfileirar) e as estruturas `Operacao`, `EPilha` e `Pilha`. Declara os protótipos das funções implementadas em `desfazer.c`. Inclui `cadastro.h` para ter acesso à definição da estrutura `Registro`.

### 6. `gerenciador.c` e `gerenciador.h`

-   **`gerenciador.c`**: Coordena as estruturas de dados principais do sistema. A função `inicializar_gerenciador` cria a lista de pacientes, inicializa a fila comum e o heap prioritário. As funções `mover_para_fila_prioritaria` e `mover_para_fila_comum` permitem transferir pacientes entre a fila comum e a fila prioritária, buscando o paciente pelo RG e removendo de uma fila para adicionar na outra.
-   **`gerenciador.h`**: Define a estrutura `Gerenciador`, que contém uma `Fila` para o atendimento comum, um `Heap` para o atendimento prioritário e uma `Lista` para o cadastro de pacientes. Declara o protótipo da função `inicializar_gerenciador` e as funções para mover pacientes entre as filas. Inclui os headers `cadastro.h`, `atendimento.h` e `atendimento_prioritario.h` para ter acesso às definições das estruturas utilizadas.

### 7. `pesquisa.c` e `pesquisa.h`

-   **`pesquisa.c`**: Implementa funcionalidades de pesquisa utilizando uma Árvore de Busca Binária (ABB). Define as estruturas `EABB` (nó da árvore com um `Registro` e ponteiros para os filhos esquerdo e direito) e `ABB` (ponteiro para a raiz e quantidade de nós). Inclui funções auxiliares como `comparar_registros` para comparar pacientes com base em diferentes critérios (ano, mês, dia de entrada, idade) e `destruir_no` e `liberar_nos` para desalocar a memória da árvore. As funções principais incluem `criar_arvore` para criar uma nova ABB, `destruir_arvore` para liberar a memória da árvore, `inserir_abb` para inserir um paciente na ABB com base em um critério de ordenação, funções de percurso em ordem (`em_ordem_ano`, `em_ordem_mes`, `em_ordem_dia`, `em_ordem_idade`) para exibir os pacientes ordenados por critério, e `buscar_paciente_abb` para buscar um paciente na ABB pelo RG.
-   **`pesquisa.h`**: Define as estruturas `EABB` e `ABB` e declara os protótipos das funções implementadas em `pesquisa.c`. Inclui `cadastro.h` para ter acesso à definição da estrutura `Registro`.

### 8. `main.c`

-   **`main.c`**: É o ponto de entrada do programa. Inicializa as estruturas de dados principais (`Lista` de pacientes, `Fila` de atendimento comum, `Heap` prioritário, `ABB` de pesquisa e `Pilha` de operações). Apresenta um menu principal ao usuário com opções para acessar as diferentes funcionalidades do sistema. Utiliza um loop `do-while` para manter o menu ativo até que o usuário escolha a opção de sair. Cada opção do menu chama uma função de menu específica (`menu_cadastrar`, `menu_atendimento`, `menu_atendimento_prioritario`, `menu_pesquisa`, `menu_desfazer`, `menu_carregar`, `menu_salvar`, `menu_sobre`). Ao final do programa, libera a memória alocada para a lista de pacientes e a pilha de operações. As funções de menu auxiliam na interação com o usuário para realizar as operações desejadas, utilizando as funções implementadas nos outros módulos.
