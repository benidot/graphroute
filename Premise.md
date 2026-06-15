# **Analisador de Rotas de Rede com Grafos**

A análise de topologia e diagnóstico de rotas são essenciais no gerenciamento de redes. Ferramentas como o **traceroute** mapeiam sequencialmente os roteadores  (saltos) pelos quais um pacote trafega até alcançar um destino final. Esse conjunto de dados pode ser modelado e interpretado através de um Grafo, onde cada roteador com um endereço IP válido é tratado como um vértice e cada enlace de comunicação direta atua como uma aresta direcionada. Este projeto visa desenvolver uma aplicação que, a partir de logs de rede, construa essa topologia dinamicamente em memória e aplique algoritmos para responder a consultas, consolidando conceitos fundamentais da disciplina.

## **Funcionalidades Obrigatórias:**

### **Carregamento Inicial:**

* Ao iniciar, o programa deve receber o caminho de um arquivo de log de *traceroute* como argumento de linha de comando (`argc`/`argv`).  
* Exibir mensagem de erro caso não seja fornecido o nome do arquivo ou o mesmo não possa ser aberto para leitura com sucesso.  
* O programa deve realizar a leitura do arquivo para construir um **Grafo Direcionado Não Ponderado** em memória, utilizando a estrutura de **Lista de Adjacência**.  
* Sanitização dos dados:   
  * Os vértices do grafo são os endereços IPs encontrados nas colunas `hop_from` e `hop_to`. Se o valor de `hop_to` for um asterisco (`*`), a linha representa um *timeout* de rede e deve ser descartada (nenhuma aresta deve ser criada para este salto).   
  * Também deve-se desconsiderar as linhas onde `hop_from` ou `hop_to` estiverem em branco.  
  * É possível existirem múltiplas ocorrências do mesmo salto em um arquivo de log. A estrutura de dados implementada deve lidar com essa situação, não gerando repetições do mesmo link no grafo.  
* Ao finalizar a carga, o programa deve exibir uma mensagem de sucesso informando o número total de vértices únicos e arestas inseridas.

### **Formato e Estrutura do Arquivo de Entrada (.log)**

O programa receberá como entrada um arquivo de texto textualmente estruturado contendo seis valores separados por vírgula em cada linha, com o histórico de medições de rotas. A primeira linha do arquivo é o cabeçalho (*header*), especificando as colunas de dados. Cada linha subsequente representa uma única conexão ou enlace lido de uma medição de *traceroute*. O formato exato de cada registro é o seguinte:

**`prb_id,probe_src,dst_addr,hop,hop_from,hop_to,rtt`**

#### **Descrição dos Campos:**

* **`prb_id`**: Identificador numérico único da sonda ou da medição de teste atual.  
* **`probe_src`**: Endereço IP da sonda de origem de onde o teste foi disparado.  
* **`dst_addr`**: Endereço IP de destino final que o teste tentou alcançar.  
* **`hop`**: O número sequencial do salto na rota (iniciando em 1).  
* **`hop_from`**: Endereço IP do roteador que enviou o pacote neste trecho. **Representa o vértice de origem da aresta.**  
* **`hop_to`**: Endereço IP do roteador que recebeu o pacote neste trecho. **Representa o vértice de destino da aresta.**  
* **`rtt`**: *Round-Trip Time* acumulado em milissegundos, que mede o tempo que uma solicitação de rede leva para ir de um ponto de partida a um destino e voltar.

#### **Arquivos de Entrada para Testes:**

* [input\_1.log](https://drive.google.com/uc?export=download&id=1Tu9IgBEau_TMD_bPb4GyTAimIUlBOGbX)  
* [input\_2.log](https://drive.google.com/uc?export=download&id=1n35VqpYMT6IejdcgHQm3twbwgUtVGVrT)  
* [input\_3.log](https://drive.google.com/uc?export=download&id=1Xl-zBK_lObl0ADVP268WqvNAxvprM4oL)

### **Menu Interativo:**

Após o carregamento inicial bem-sucedido, exibir um menu interativo com as seguintes opções:

#### **1\. Exibir Grafo Completo:**

* Gerar dinamicamente um arquivo de texto no formato `.dot` (compatível com o Graphviz) representando a topologia completa do grafo em memória.  
* O programa deve apresentar um submenu para o usuário escolher o formato da saída:  
  * **Tela**: Abre a janela do sistema exibindo o grafo.  
  * **Imagem (PNG)**: Exporta e gera o arquivo *NOMEDOARQUIVODEENTRADA*.png na pasta atual.  
  * **Documento (PDF)**: Exporta e gera o arquivo *NOMEDOARQUIVODEENTRADA*.pdf na pasta atual.  
    * [Exemplo de PDF gerado para input\_1.log](https://drive.google.com/file/d/1roQzDz_QBPz64nYQOGexntJrJR5OUDxF/view?usp=drive_link)

#### **2\. Encontrar Menor Caminho:**

* Solicitar que o usuário informe dois endereços IP: um de **Origem** e um de **Destino**.  
* O programa deve executar um algoritmo para determinar o caminho com o **menor número de saltos** entre os dois nós. Caso existam mais de um caminho com comprimento mínimo, usar o primeiro encontrado.   
* **Saída no Console:** Exibir a sequência ordenada de IPs que compõem o caminho e a quantidade total de saltos. Caso não haja conectividade entre os nós, exibir uma mensagem de alerta.  
* **Saída Visual:** Gerar dinamicamente um arquivo .dot e exibir. Este arquivo conterá todo o grafo original, mas os nós e as arestas que pertencem ao caminho localizado devem ser destacados com atributos visuais diferenciados dos demais para facilitar a visualização.  
  * A saída deve apresentar o mesmo submenu de formatos disponível na opção 1, acima.  
  * [Exemplo de PDF gerado para input\_1.log](https://drive.google.com/file/d/1rKCO8uyJ6ck5TEVNk_7joHiatjYSpyHu/view?usp=drive_link) com Origem: `62.115.43.72` e Destino: `104.44.16.196`

#### **3\. Calcular o Diâmetro do Grafo:**

* Calcular e exibir o diâmetro do grafo.

#### **4\. Identificar Roteadores Críticos:**

* Analisar a estrutura do grafo e exibir o `Top 5` endereços IP com o maior **Grau de Entrada (In-degree)**.  
* Esta funcionalidade mapeia os principais *hubs* ou nós centrais de infraestrutura de rede contidos no log.

---

## **Exemplo de Uso:**

Plaintext

```
$ ./graphroute input_1.log
Grafo de roteamento inicializado!
Vértices únicos (IPs): 342 | Arestas: 812

======================================================
1. Exibir Grafo Completo
2. Encontrar Menor Caminho
3. Calcular o Diâmetro do Grafo
4. Identificar Roteadores Críticos
0. Sair
======================================================
Escolha uma opção: 2

Digite o IP de Origem: 82.66.191.65
Digite o IP de Destino: 194.149.162.250

Caminho encontrado (3 saltos):
82.66.191.65 -> 192.168.3.1 -> 194.149.162.248 -> 194.149.162.250

Selecione o formato de saída do Graphviz: 
1. Tela 
2. Imagem (PNG) 
3. Documento (PDF) 
Opção: 2 
Arquivo input_1.log.png gerado com sucesso
```

---

## **Entrega e Grupos:**

* O projeto deve ser desenvolvido de forma colaborativa por um time de três aluno/as e com gerenciamento de versões do código por meio de **Git**.  
* Anotar os integrantes na planilha oficial até a [data estipulada](#calendário:) pelo professor.  
* Criar um repositório compartilhado (público ou privado) com o professor no GitHub: \<[mjbrusso@gmail.com](mailto:mjbrusso@gmail.com)\> ou \<[leo.costella@upf.br](mailto:leo.costella@upf.br)\>.  
* O README do projeto deve incluir instruções claras de compilação/execução no terminal Linux.

## **Apresentação:**

* Cada time deverá apresentar presencialmente a sua implementação. Será verificado o correto funcionamento de todas as opções do menu, a consistência do arquivo de visualização gerado e o entendimento do grupo sobre os algoritmos e código entregue.

## **Avaliação**

* Execução correta, atendimento dos requisitos e eficiência sob volumetria real (35%)  
  * O programa deve processar um grande log sem travamentos ou estouro de memória.  
* Domínio da implementação pelo grupo na apresentação presencial e alteração ao vivo (35%)  
  * Além de questionamento sobre pontos específicos do código submetido, o time será testado com modificações lógicas simples feitas na hora para provar a autoria.  
* Evolução constante e incremental do projeto no repositório Git por todo o time (20%)  
  * Commits maciços de última hora ou concentrados em apenas um integrante serão penalizados. O que se espera da evolução de um projeto no git é o commit incremental por funcionalidade  
* Organização do código, boas práticas e relatório de justificativa das escolhas no README (10%)  
  * Uso de soluções coerentes com o que foi trabalhado na disciplina

## **Calendário:** {#calendário:}

* Turma da terça-feira (prof. Leonardo Costella):  
  * Datas limite para definição dos grupos: **29/05/2026**  
    * [Link para planilha](https://docs.google.com/spreadsheets/d/1VaVMGVjjU7KAIY1YfHAHg4hdlF_ccaTMbaP0mXR9RLw/edit?usp=sharing)  
  * Data limite para commit no repositório: **20/06/2026**   
  * Data de apresentação do trabalho: **23/06/2026**  
* Turma da quarta-feira (prof. Marcos Brusso):  
  * Datas limite para definição dos grupos: **27/05/2026**  
    * [Link para planilha](https://docs.google.com/spreadsheets/d/137SDKRw88pfEcaLgReAZR8eYSOmAI0gHxFxsAdGhDYg/edit?gid=0#gid=0)  
  * Data limite para commit no repositório: **21/06/2026**   
  * Data de apresentação do trabalho: **24/06/2026**

