#pragma once
#include "tetromino.hpp"
#include <SDL.h>

class Well
{
public:
	// Construtor da classe Well
	Well();

	// M�todo para desenhar o po�o no renderer
	void draw(SDL_Renderer*);

	// Enumera��es para largura e altura do po�o
	enum { Width = 10, Height = 20 };

	// Verifica se h� colis�o com o tetromino fornecido
	bool isCollision(const Tetromino& t) const;

	// Unifica o po�o com o tetromino fornecido
	void unite(const Tetromino&);

private:
	// Matriz de dados representando o estado do po�o
	bool data[Width][Height];
};