
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
- O plano que a IA apresentou, resumido:
- Mudei algo no plano antes de liberar?
- Resultado de `testar.sh missao1` e de `testar.sh parte1`:
- Precisei refazer? O que mudou no pedido:

## Missão 2: SALVAR e CARREGAR

- Primeira mensagem:
- O plano, resumido:
- O formato do arquivo (cole cinco linhas do `dados_teste.txt`):
- Resultado de `testar.sh missao2` e de `testar.sh parte1`:
- Precisei refazer? O que mudou no pedido:

## Missão 3: RELATORIO

- Primeira mensagem:
- O plano, resumido:
- Resultado de `testar.sh missao3` e de `testar.sh parte1`:
- Precisei refazer? O que mudou no pedido:

## Missão 4: livre

- O que escolhi e por quê:
- O comando novo, a saída que eu esperava e o nome do meu arquivo de comandos
  (escritos antes de pedir):
- Primeira mensagem:
- O que veio, comparado com o que eu esperava:
- `testar.sh parte1` continuou passando?
- Aceitei, ajustei ou descartei? Por quê:

## Fechamento

- O que a IA fez que eu não conseguiria fazer sozinho nesse prazo:
- Onde ela errou ou fez algo que eu não pedi:
- O que eu faria diferente da próxima vez:
>>>>>>> 06660cd (Parte 1 inicial)
