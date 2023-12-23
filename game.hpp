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

	// Fun��o principal do jogo, chamada a cada frame
	bool tick();

private:
	// Construtor de c�pia (desativado)
	Game(const Game&);

	// Operador de atribui��o (desativado)
	Game& operator=(const Game&);

	// Ponteiro para a janela SDL
	SDL_Window* window_;

	// Ponteiro para o renderizador SDL
	SDL_Renderer* renderer_;

	// Inst�ncia da classe Well (po�o)
	Well well_;

	// Inst�ncia da classe Tetromino
	Tetromino tetromino_;

	// Tempo para controle do movimento autom�tico
	uint32_t moveTime_;

	// Fun��o para verificar colis�es e atualizar o estado do jogo
	void check(const Tetromino&);
};