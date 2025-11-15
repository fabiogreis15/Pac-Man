Pac-Man
Jogo Pac-Man em linguagem C desenvolvido para a disciplina Programação Imperativa e Funcional - CESAR School.
 🟡 Hungry Maze — Pac-Man em C

 👥 Membros do Projeto
- Fábio Gomes dos Reis — [fabiogreis15](https://github.com/fabiogreis15]
- Deyvison Gabriel Guerra Lucas - [d.gabrielguerra] (https://github.com/dgabrielguerra]
---

 📘 Disciplina
Programação Imperativa e Funcional - 2025.2

 🏫 Instituição
CESAR School

---

 🎮 Nome do Jogo
Hungry Maze

Um jogo inspirado no clássico **Pac-Man**, desenvolvido em linguagem **C**, com foco em conceitos de lógica de programação, modularização e manipulação de matrizes.

---

 🧩 Descrição do Jogo

Hungry Maze é um jogo em modo texto (terminal) onde o jogador controla o personagem Pac, que deve comer todos os pontos (`.`) espalhados pelo labirinto enquanto evita ser capturado pelos fantasmas.


Bibliotecas: 
PAC-MAN/
│
├── include/               # Cabeçalhos (.h) do projeto
│   ├── cli_lib.h          # Biblioteca de interface de terminal
│   ├── enemy.h            # Lógica e estrutura dos inimigos (fantasmas)
│   ├── game.h             # Estruturas centrais do jogo
│   ├── map.h              # Manipulação do mapa e carregamento
│   └── player.h           # Estrutura e ações do Pac-Man
│
├── src/                   # Código-fonte principal (.c)
│   ├── cli_lib.c          # Implementação da interface CLI
│   ├── enemy.c            # Implementação dos fantasmas
│   ├── game.c             # Loop principal e lógica do jogo
│   ├── main.c             # Arquivo principal (ponto de entrada)
│   ├── map.c              # Carregamento e renderização do mapa
│   └── player.c           # Movimentação e ações do Pac-Man
│
├── LICENSE                # Licença do projeto
├── Makefile               # Script para compilar o jogo com 'make'
└── README.md              # Documentação


## Mecanismo do Jogo (“Game Mechanism”)

Este jogo é uma implementação do clássico **Pac-Man**, com uma mecânica simples mas eficaz inspirada no original:

- O jogador controla o Pac-Man através de um labirinto.  
- No mapa existem “pellets” (pontinhos) que o Pac-Man deve comer para pontuar.  
- Existem fantasmas que se movem pelo labirinto: se o Pac-Man encostar neles, o jogo termina.  
- Quando o Pac-Man come uma “super pastilha” (ou algo equivalente, se implementado), os fantasmas se tornam vulneráveis e podem ser “comidos” para ganhar pontos extras (se você implementar esse mecanismo).  
- O objetivo principal é comer todos os pellets no mapa para vencer ou “passar de fase” (dependendo de sua implementação).  
- Há pontuação baseada nos pellets coletados (e, se aplicável, fantasmas comidos).

### IA dos Fantasmas (se houver)

- Inspirada no Pac-Man clássico: os fantasmas têm diferentes “personalidades” ou estratégias (por exemplo, perseguir diretamente, flanquear, alternar entre modos).  
- Você pode ter modos como “caça” (chase), “dispersão” (scatter) ou “fuga”, dependendo da implementação do seu código.

### Controle do Jogador

- As teclas **W / A / S / D** (ou outras que você definiu) controlam para cima, esquerda, baixo e direita, respectivamente.  
- Pode haver uma tecla para sair (“Q”) ou reiniciar, se você implementou.

### Loop de Jogo

1. Ler entrada do usuário (tecla).  
2. Atualizar posição do Pac-Man conforme entrada.  
3. Atualizar posições dos fantasmas de acordo com a IA.  
4. Verificar colisões (Pac-Man com fantasmas, Pac-Man com pellets).  
5. Se todos os pellets forem comidos → vitória; se fantasma pegar Pac-Man → game over.  
6. Desenhar o estado atual no terminal usando `cli-lib`.  
7. Repetir até o fim do jogo.

