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

 🎯 Objetivo
- Comer todos os pontos do mapa para vencer.
- Fugir dos fantasmas — se um encostar em você, o jogo termina.

 ⚙️ Regras
1. O jogador começa com 3 vidas.
2. Cada ponto comido soma +10 pontos.
3. Ao ser capturado, perde uma vida.
4. Se todas as vidas acabarem → Game Over.
5. Se comer todos os pontos → Vitória!


Bibliotecas: 
PAC-MAN/
├── build/              # Saídas de compilação (.o e executável)
│
├── cli-lib/            # Biblioteca auxiliar para interação no terminal
│   ├── cli.c
│   └── cli.h
│
├── include/            # Arquivos de cabeçalho (.h)
│   ├── game.h
│   ├── map.h
│   └── player.h
│
├── src/                # Código-fonte principal (.c)
│   ├── game.c
│   ├── main.c
│   ├── map.c
│   └── player.c
│
├── LICENSE             # Licença do projeto
├── Makefile            # Script de build e execução
└── README.md           # Documentação do projeto

