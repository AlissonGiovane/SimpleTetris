#include "game.hpp"
#include <iostream>

int main(int /*argc*/, char*/*argv*/[])
{
	// Cria uma instância do jogo
	Game game;

	// Executa o loop principal do jogo enquanto a função tick() retorna true
	while (game.tick());

	return 0;
}