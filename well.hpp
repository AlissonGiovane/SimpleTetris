#pragma once
#include "tetromino.hpp"
#include <SDL.h>

class Well
{
public:
	// Construtor da classe Well
	Well();

	// Método para desenhar o poço no renderer
	void draw(SDL_Renderer*);

	// Enumerações para largura e altura do poço
	enum { Width = 10, Height = 20 };

	// Verifica se há colisão com o tetromino fornecido
	bool isCollision(const Tetromino& t) const;

	// Unifica o poço com o tetromino fornecido
	void unite(const Tetromino&);

private:
	// Matriz de dados representando o estado do poço
	bool data[Width][Height];
};