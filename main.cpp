#include "game.hpp"
#include <iostream>

int main(int /*argc*/, char*/*argv*/[])
{
	// Cria uma inst�ncia do jogo
	Game game;

	// Executa o loop principal do jogo enquanto a fun��o tick() retorna true
	while (game.tick());

	return 0;
}