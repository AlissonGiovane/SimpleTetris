#pragma once
#include <SDL.h>
#include "well.hpp"
#include "tetromino.hpp"

class Game
{
public:
	// Construtor da classe Game
	Game();

	// Destrutor da classe Game
	~Game();

	// Função principal do jogo, chamada a cada frame
	bool tick();

private:
	// Construtor de cópia (desativado)
	Game(const Game&);

	// Operador de atribuição (desativado)
	Game& operator=(const Game&);

	// Ponteiro para a janela SDL
	SDL_Window* window_;

	// Ponteiro para o renderizador SDL
	SDL_Renderer* renderer_;

	// Instância da classe Well (poço)
	Well well_;

	// Instância da classe Tetromino
	Tetromino tetromino_;

	// Tempo para controle do movimento automático
	uint32_t moveTime_;

	// Função para verificar colisões e atualizar o estado do jogo
	void check(const Tetromino&);
};