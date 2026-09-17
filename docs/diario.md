
<<<<<<< HEAD

=======
# Diário da atividade

Escreva com as suas palavras. Frases curtas bastam. Não cole a conversa inteira
com a IA. Cole só os pedidos que você enviou.

## Ambiente

- Versão do OpenCode (`opencode --version`):
- Modelo usado:

## Parte 1: antes de programar

- O que cada classe guarda:

Astronauta: guarda nome, CPF, idade, se está disponível e se está vivo.

Voo: guarda o código do voo, o estado do voo e os CPFs dos astronautas que estão nele.

Agencia: guarda os astronautas e os voos cadastrados.

- O que acontece em `LANCAR_VOO`, em palavras:
O voo passa de planejado para em curso, depois de verificar as condições do voo e dos astronautas.

- Uma dúvida que eu tinha antes de começar:
Eu tinha dúvidas sobre a sintaxe das classes, como declarar os atributos e métodos e como fazer a comunicação entre as classes.
## Parte 1: uso de IA para entender algo

- O que perguntei (ou "não usei"):
Usei a IA para organizar minhas ideias e resolver problemas com arquivos que estavam dando erro e prejudicando a funcionalidade do programa, principalmente através de comandos no terminal.

- O que aprendi:
Aprendi a organizar melhor minhas ideias para resolver os problemas e a usar comandos no terminal para verificar e corrigir os arquivos do projeto.

## Primeiro contato: revisão sem editar

- As três melhorias que a IA sugeriu, em uma linha cada:
1)Trocar string estado por enum (evita erros de digitação); 2) criar o auxiliar buscarVooPlanejado  3) separar o código em arquivos

- A que escolhi e por quê: 
2) criar o auxiliar de buscarvooplanejado e o motivo foi por que ela cria uma função auxiliar que junta duas checagens repetidas: "o voo existe?" e "está planejado?". Antes, `adicionarAstronauta`, `removerAstronauta` e `lancarVoo` repetiam as mesmas linhas de erro três vezes. Agora o código fica menor, mais fácil de ler, e qualquer correção nessa regra é feita em um só lugar.

- O que mudou no código, e se os seis testes continuaram passando: O código mudou só em um ponto: criei `buscarVooPlanejado`, uma função que verifica se o voo existe e se está planejado. Três funções que repetiam esse check (`adicionarAstronauta`, `removerAstronauta`, `lancarVoo`) agora chama só ela. Comportamento e saída continuam iguais. e os seis testes continuaram passando 

- O que entendi que não sabia antes:
Descobri que repetir o mesmo código em várias funções dá para evitar: se três funções fazem a mesma pergunta ("o voo existe?" e "está planejado?"), eu posso criar uma função auxiliar que cuida disso para mim. Aí o código fica mais curto, mais fácil de ler, e se a regra mudar, eu corrijo em um lugar só.

## Missão 1: LISTAR_ASTRONAUTAS e HISTORICO

- Primeira mensagem (o pedido do plano):
Pedi dois comandos novos, sem deixar a IA editar ainda.
LISTAR_ASTRONAUTAS: mostra os astronautas em três grupos, na ordem de
cadastro — "disponiveis" (vivos fora de voo), "em voo" (vivos em voo em
curso, com o código do voo) e "mortos". Grupo vazio mostra (nenhum). Passei
o formato exato:
LISTA DE ASTRONAUTAS
== disponiveis ==
333 Carla Souza (28 anos)
== em voo ==
111 Ana Maria (30 anos) - voo 20
== mortos ==
222 Bruno Costa (35 anos)
HISTORICO cpf: mostra os voos em que o astronauta participou (voo lançado
com ele a bordo; só planejado não conta), com o estado atual de cada um, na
ordem de cadastro dos voos. Sem voos: (nenhum voo). CPF desconhecido: ERRO:
astronauta 999 nao cadastrado. Formato exato:
HISTORICO DE 111 Ana Maria
voo 10: finalizado com sucesso
voo 20: em curso
Pedi para não mudar nenhum comando existente nem usar nada fora da
biblioteca padrão, e que ela me dissesse o plano (arquivos e métodos que ia
criar ou alterar, e por quê) antes de editar qualquer coisa.

- O plano que a IA apresentou, resumido:

1. Astronauta ganha um campo novo vector<int> voos (histórico) e métodos
registrarVoo(codigo), getQuantidadeVoos() e getVoo(posicao). Motivo: "participou"
só conta se o voo foi lançado, então precisa gravar no momento do lançamento
(não dá pra calcular depois, senão o voo 30 do teste 02, que ficou só
planejado, apareceria errado).
2. Em Agencia::lancarVoo, no laço que chama embarcar() de cada astronauta,
adiciona também astronautas[pos].registrarVoo(codigo).
3. Novo método Agencia::listarAstronautas(): separa em disponiveis (vivo,
fora de voo em curso), em voo (vivo, achando o voo em curso dele) e mortos.
Grupo vazio mostra (nenhum).
4. Novo método Agencia::listarHistorico(cpf): CPF desconhecido dá erro;
senão lista os voos gravados no astronauta com o estado atual de cada um;
sem voos mostra (nenhum voo).
5. Em main(), liga os comandos LISTAR_ASTRONAUTAS e HISTORICO aos métodos
novos.
Nenhum comando existente muda.

- Mudei algo no plano antes de liberar? não 
- Resultado de `testar.sh missao1` e de `testar.sh parte1`: 
@glimaoliveira2006-cyber ➜ /workspaces/atividade-astronautas (main) $ bash testes/testar.sh missao1
bash testes/testar.sh parte1
compilando...
PASSOU - 01_listar_astronautas
PASSOU - 02_historico

2 de 2 testes passaram
compilando...
PASSOU - 01_cadastros
PASSOU - 02_passageiros_planejados
PASSOU - 03_lancamento_finalizacao
PASSOU - 04_explosao_e_mortes
PASSOU - 05_operacoes_invalidas
PASSOU - 06_cenario_completo

6 de 6 testes passaram

- Precisei refazer? O que mudou no pedido: Precisei refazer? O que mudou no pedido:
Não precisei pedir de novo pra IA, o códigoestava certo desde a
primeira vez. O problema foi na organização dos testes, a IA criou a pasta
como "missão1" (com acento) e ainda colocou "parte1", "missão2" e "missão3"
aninhadas dentro dela, em vez de soltas em testes/. Além disso, os arquivos
.out vieram com fim de linha do Windows (\r\n), então os testes falhavam
mesmo com a saída aparentemente igual. Descobri isso comparando os bytes
com xxd. Corrigi na mão e movi as pastas pro lugar certo, ajustei os
caminhos no testar.sh e limpei o \r com sed. Depois disso, tudo passou sem
tocar no código.

## Missão 2: SALVAR e CARREGAR

- Primeira mensagem:
Este programa em C++11 controla astronautas e voos de uma agência espacial.
Ele lê comandos da entrada padrão. As classes Astronauta, Voo e Agencia estão
em src/main.cpp. Os testes em testes/parte1 e testes/missao1 passam.
Quero dois comandos novos: SALVAR nome_do_arquivo e CARREGAR nome_do_arquivo.
SALVAR nome_do_arquivo grava todos os dados atuais (astronautas e voos) em um
arquivo de texto e imprime OK: dados salvos em nome_do_arquivo. Se não
conseguir abrir o arquivo para escrita: ERRO: nao foi possivel salvar em
nome_do_arquivo.
CARREGAR nome_do_arquivo substitui todos os dados atuais pelos do arquivo e
imprime OK: dados carregados de nome_do_arquivo. Se o arquivo não existir:
ERRO: nao foi possivel carregar de nome_do_arquivo, e os dados atuais
continuam como estavam.
O formato do arquivo é livre, desde que carregar depois de salvar reconstrua
tudo corretamente: astronautas com nome, idade, se está vivo e se está
disponível, e também o histórico de voos que registrei na Missão 1; voos com
código, estado e lista de CPFs a bordo.
Antes de editar, me mostre o formato do arquivo com um exemplo, explique como
o programa reconstrói os objetos ao ler, e me diga quais arquivos e métodos
você vai criar ou alterar, e por quê.
Não mude nenhum comando que já existe nem a saída deles. Não use nada fora da
biblioteca padrão.
Vou conferir com bash testes/testar.sh missao2 e depois com
bash testes/testar.sh parte1.

- O plano, resumido:
1. Astronauta ganha restaurarEstado(vivo, disponivel) — sobrescreve esses
dois campos ao carregar, já que o construtor sempre cria vivo/disponível
como true.
2. Voo ganha definirEstado(estado) — restaura estados diferentes de
"planejado" (o construtor sempre começa como "planejado").
3. Agencia::salvar(arquivo) grava astronautas (cpf, nome, idade, vivo,
disponível e histórico de voos) e voos (código, estado como número, CPFs a
bordo) num arquivo texto; imprime erro se não conseguir abrir o arquivo
para escrita.
4. Agencia::carregar(arquivo) lê esse arquivo e reconstrói tudo; só limpa
os dados atuais depois de confirmar que o arquivo abriu com sucesso — se
não existir, mantém os dados como estavam. Usa dois métodos auxiliares
para converter estado texto ↔ número, e getters novos para acessar os
vetores de astronautas e voos
5. main() ganha dois comandos novos, SALVAR e CARREGAR, ligados aos
métodos da Agencia.
Nenhum comando existente foi alterado.
- O formato do arquivo (cole cinco linhas do `dados_teste.txt`): 
OK: astronauta 111 cadastrado
OK: astronauta 222 cadastrado
OK: astronauta 333 cadastrado
OK: voo 10 cadastrado
OK: voo 20 cadastrado

- Resultado de `testar.sh missao2` e de `testar.sh parte1`:  
@glimaoliveira2006-cyber ➜ /workspaces/atividade-astronautas (main) $ bash testes/testar.sh missao2
bash testes/testar.sh parte1
compilando...
PASSOU - 01_salvar
PASSOU - 02_carregar
PASSOU - 03_arquivo_inexistente

3 de 3 testes passaram
compilando...
PASSOU - 01_cadastros
PASSOU - 02_passageiros_planejados
PASSOU - 03_lancamento_finalizacao
PASSOU - 04_explosao_e_mortes
PASSOU - 05_operacoes_invalidas
PASSOU - 06_cenario_completo

6 de 6 testes passaram

- Precisei refazer? O que mudou no pedido: sim, eu estava usando o open code baixado no pc e ele estava dando varios erros por não ter acesso diretamente ao projeto, então baixei diretamente aqui no Vs code do git o open code e deu certo 

## Missão 3: RELATORIO

- Primeira mensagem: Este programa em C++11 controla astronautas e voos de uma agência espacial.
Ele lê comandos da entrada padrão. As classes Astronauta, Voo e Agencia estão
em src/main.cpp. Os testes em testes/parte1, testes/missao1 e testes/missao2
passam.
Quero um comando novo: RELATORIO. Ele imprime a linha RELATORIO seguida de
nove linhas sobre o estado atual, neste formato exato:
RELATORIO
voos planejados: 0
voos em curso: 0
voos finalizados com sucesso: 1
voos finalizados com explosao: 2
astronautas cadastrados: 4
astronautas vivos: 2
astronautas mortos: 2
astronauta mais experiente: 111 Ana Maria (voos lancados: 1)
taxa de sucesso: 33%
Regras:
- A experiência de um astronauta é o número de voos já lançados em que ele
estava a bordo. Voo ainda planejado não conta. Astronauta morto continua
contando. Em caso de empate, vale o cadastrado primeiro. Se ninguém voou:
astronauta mais experiente: (nenhum).
- Taxa de sucesso é a parte inteira de sucessos * 100 / finalizados, onde
finalizados são os com sucesso mais os com explosão. Sem voos finalizados:
taxa de sucesso: (nenhum voo finalizado).
Isso precisa funcionar corretamente também depois de um CARREGAR (ou seja,
os dados usados no relatório devem vir do estado real dos astronautas e
voos, não de contadores separados que poderiam ficar desatualizados)
Antes de editar, me diga quais arquivos e métodos você vai criar ou alterar,
e por quê, e como vai calcular a experiência de cada astronauta (guardando
um contador, ou contando os voos lançados a cada chamada do relatório).
Não mude nenhum comando que já existe nem a saída deles. Não use nada fora
da biblioteca padrão.
Vou conferir com bash testes/testar.sh missao3 e depois com
bash testes/testar.sh parte1.

- O plano, resumido:
- Criou o método `Agencia::relatorio()` em `src/main.cpp`, posicionado entre `listarHistorico` e `salvar`
- Conta voos por estado (planejado, em curso, finalizado com sucesso, finalizado com explosao) varrendo o vetor `voos`
- Conta vivos/mortos varrendo `astronautas`
- Calcula experiência de cada astronauta usando `getQuantidadeVoos()` (já existente): mortos continuam contando, empate mantém o primeiro cadastrado, ninguém voou → `(nenhum)`
- Calcula taxa de sucesso = parte inteira de `sucesso*100/(sucesso+explosao)`; sem finalizados → `(nenhum voo finalizado)`
- No `main()`, o comando `RELATORIO` passou a chamar `agencia.relatorio()`
- Nenhum comando existente foi alterado, e só usou biblioteca padrão


- Resultado de `testar.sh missao3` e de `testar.sh parte1`:
@glimaoliveira2006-cyber ➜ /workspaces/atividade-astronautas (main) $ bash testes/testar.sh missao3 && bash testes/testar.sh parte1
compilando...
PASSOU - 01_relatorio_vazio
PASSOU - 02_relatorio_cenario
PASSOU - 03_relatorio_empate
PASSOU - 04_salvar_para_relatorio
PASSOU - 05_relatorio_apos_carregar

5 de 5 testes passaram
compilando...
PASSOU - 01_cadastros
PASSOU - 02_passageiros_planejados
PASSOU - 03_lancamento_finalizacao
PASSOU - 04_explosao_e_mortes
PASSOU - 05_operacoes_invalidas
PASSOU - 06_cenario_completo

6 de 6 testes passaram

- Precisei refazer? O que mudou no pedido: não 

## Missão 4: livre

- O que escolhi e por quê: Escolhi criar um catálogo de planetas como destino dos voos, porque adiciona uma classe nova (Planeta) e conecta com o restante do sistema (Voo e Agencia)

- O comando novo, a saída que eu esperava e o nome do meu arquivo de comandos
  (escritos antes de pedir): Comandos novos= CADASTRAR_PLANETA nome distancia_km, DEFINIR_DESTINO codigo nome_planeta e LISTAR_PLANETAS.

- Primeira mensagem:
Este programa em C++11 controla astronautas e voos de uma agência espacial.
Ele lê comandos da entrada padrão. As classes Astronauta, Voo e Agencia estão
em src/main.cpp. Os testes em testes/parte1, testes/missao1, testes/missao2
e testes/missao3 passam.
Quero adicionar uma nova classe Planeta e três comandos novos, sem alterar
nenhum comando existente. Segue a especificação exata.
Classe Planeta (nova):
- Atributos privados: nome (string), distanciaKm (double), voosLancados (int).
- Construtor recebe nome e distanciaKm; voosLancados comeca em 0.
- Getters: getNome(), getDistancia(), getVoosLancados().
- Metodo registrarLancamento() incrementa voosLancados.
Na classe Voo, adicionar um atributo destino (string, vazio por padrao) e um
getter getDestino(). O construtor de Voo NAO muda de assinatura; destino
comeca vazio e so e definido pelo comando DEFINIR_DESTINO.
Comandos novos na Agencia:
CADASTRAR_PLANETA nome distancia_km
- ERRO: planeta ja cadastrado
- OK: planeta cadastrado
DEFINIR_DESTINO codigo nome_planeta
- ERRO: voo 10 nao cadastrado
- ERRO: planeta X nao cadastrado
- ERRO: voo 10 nao esta planejado
- OK: destino de 10 definido para X
LSTAR_PLANETAS
- Mostra todos os planetas na ordem de cadastro, com nome, distancia e
  quantidade de voos ja lancados para la. Sem planetas: (nenhum).
  Formato sugerido:
  LISTA DE PLANETAS
  Marte - 225000000 km - voos lancados: 2
Regra adicional em LANCAR_VOO: se o voo tiver destino definido, chame
planeta.registrarLancamento() no planeta correspondente quando o voo for
lancado com sucesso pelas validacoes que ja existem. Se o voo NAO tiver
destino definido, o lancamento continua funcionando normalmente, sem erro
novo algum.
O que nao pode mudar: nenhum comando existente (CADASTRAR_VOO, LANCAR_VOO,
LISTAR_VOOS, etc.) pode mudar de assinatura ou de saida para os casos que
ja existiam antes. Um voo sem destino definido tem que continuar sendo
lancado exatamente como hoje.
Nao use nada fora da biblioteca padrao.
Vou conferir rodando um arquivo de comandos que eu mesmo vou criar, e depois
bash testes/testar.sh parte1, bash testes/testar.sh missao1,
bash testes/testar.sh missao2 e bash testes/testar.sh missao3, pra garantir
que nada quebrou.
Antes de editar, me diga quais arquivos e quais metodos voce vai criar ou
alterar, e por que.

- O que veio, comparado com o que eu esperava: O código veio exatamente como eu esperava: os três comandos novos (CADASTRAR_PLANETA, DEFINIR_DESTINO, LISTAR_PLANETAS) funcionaram com a saída certinha, o contador de voos lançados incrementou corretamente ao lançar um voo com destino, e o erro de planeta não cadastrado apareceu na mensagem esperada. Nenhum comando antigo quebrou (parte1, missao1, missao2 e missao3 continuaram passando).

- `testar.sh parte1` continuou passando? sim 

- Aceitei, ajustei ou descartei? Por quê: aceitei, está cumprindo tudo que eu esperava

## Fechamento

- O que a IA fez que eu não conseguiria fazer sozinho nesse prazo: trabalhar com terminal, ela facilitou muito me dando os comandos que me evitaram fazer tudo manualmente 

- Onde ela errou ou fez algo que eu não pedi: ela errou quando eu estava usando o opencode fora do vs code do git, pela falta de integração com o arquivo completo do projeto, sempre vinha com erros no local ou pasta do arquivo 

- O que eu faria diferente da próxima vez: iniciaria desdo inicio com uma IA instalada aqui no espaço de codigo
>>>>>>> 06660cd (Parte 1 inicial)
