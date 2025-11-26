# 🎮 **Hungry Maze**

### **Projeto da disciplina Programação Imperativa e Funcional — 2025.2**

**CESAR School**

---

## 👨‍💻 **Integrantes do Projeto**

| Nome                | Usuário GitHub   |
| ------------------- | ---------------- |
| **Deyvison Guerra** | `dgabrielguerra` |
| **Fábio Reis**      | `fabiogreis15`   |

---

## 🧩 **Descrição do Jogo — Hungry Maze**

**Hungry Maze** é um jogo inspirado em Pac-Man, desenvolvido inteiramente em C.
O objetivo é percorrer o labirinto, coletar todos os itens e sobreviver aos inimigos.

### 🎯 **Objetivo**

* Coletar todos os pontos (`.`) do mapa.
* Evitar morrer ao colidir com fantasmas.
* Marcar a maior pontuação possível.

### 🕹️ **Como jogar**

* Use as setas do teclado (**↑ ↓ ← →**) para mover o personagem.
* Colete itens para aumentar a pontuação.
* Fuja!
* O jogo termina quando você é incurralado por um fantasma ou conclui o mapa.

---

## 🛠️ **Como Compilar e Executar**

### 📌 **Pré-requisitos**

Antes de compilar, é necessário ter instalado:

#### **Linux (Ubuntu/Debian)**

```bash
sudo apt update
sudo apt install build-essential libncurses5-dev libncursesw5-dev libsdl2-mixer-dev
```

#### **Arch Linux**

```bash
sudo pacman -S base-devel ncurses sdl2_mixer
```

---

## 🏗️ **Compilando o Jogo**

O projeto já possui um arquivo **Makefile**, então basta executar:

```bash
make
```

Se tudo estiver correto, o binário será gerado em:

```
./build/game/hungry_maze
```

---

## ▶️ **Executando o Jogo**

Após compilar:

```bash
./build/game/hungry_maze
```

Ou diretamente:

```bash
make run
```
---

## 📁 **Estrutura do Projeto**

```
PAC-MAN/
│
├── build/
│   └── game/
│
├── cli-lib/
│   ├── cli.c
│   └── cli.h
│
├── include/
│   ├── enemy.h
│   ├── game.h
│   ├── keyboard.h
│   ├── map.h
│   ├── player.h
│   ├── ranking.h
│   ├── screen.h
│   └── timer.h
│
├── src/
│   ├── enemy.c
│   ├── game.c
│   ├── keyboard.c
│   ├── main.c
│   ├── map.c
│   ├── player.c
│   ├── ranking.c
│   ├── screen.c
│   └── timer.c
│
├── game/
│   └── gorillaz.mp3
│
├── LICENSE
├── Makefile
└── README.md
```

---

## 📝 **Regras do Jogo**

* **#** = parede (não atravessa).
* **.** = item de pontuação.
* **P** = jogador.
---
