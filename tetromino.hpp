#pragma once
#include <SDL.h>

class Tetromino
{
public:
	// Enumera��o para os tipos de tetrominos
	enum Type { I = 0, J, L, O, S, T, Z };

	// Construtor da classe Tetromino
	Tetromino(Type);

	// M�todo para desenhar o tetromino no renderer
	void draw(SDL_Renderer*);

	// M�todo para mover o tetromino nas coordenadas (dx, dy)
	void move(int dx, int dy);

	// M�todo para rotacionar o tetromino
	void rotate();

	// Verifica se h� um bloco nas coordenadas (x, y) do tetromino
	bool isBlock(int x, int y) const;

	// Obt�m a coordenada x atual do tetromino
	int x() const;

	// Obt�m a coordenada y atual do tetromino
	int y() const;

private:
	// Tipo do tetromino
	Type type_;

	// Coordenadas x e y do tetromino
	int x_;
	int y_;

	// �ngulo de rota��o do tetromino (0 - 0�, 1 - 90�, 2 - 180�, 3 - 270�)
	int angle_;
};