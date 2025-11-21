# Pac-Man (Terminal) - Projeto em C

## Como compilar

mkdir -p build
gcc src/*.c cli-lib/*.c main.c -Iinclude -o build/pacman -Wall -Wextra -std=c11

## Como executar

./build/pacman

## Controles
- W / setas cima: mover para cima
- S / setas baixo: mover para baixo
- A / setas esquerda: mover para esquerda
- D / setas direita: mover para direita
- Q: sair
