#include "well.hpp"

Well::Well() : data{ {false} } {}

// Fun��o para desenhar o campo de jogo no renderizador
void Well::draw(SDL_Renderer* renderer) {
    // Configura a cor de desenho para branco
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    // Loop para percorrer cada c�lula do campo de jogo
    for (auto x = 0; x < Width; ++x)
        for (auto y = 0; y < Height; ++y) {
            // Verifica se a c�lula est� ocupada
            if (data[x][y]) {
                // Se estiver ocupada, desenha um ret�ngulo preenchido na posi��o correspondente
                SDL_Rect rect{ x * 720 / 2 / 10 + 1, y * 720 / 2 / 10 + 1, 720 / 2 / 10 - 2, 720 / 2 / 10 - 2 };
                SDL_RenderFillRect(renderer, &rect);
            }
            else {
                // Se n�o estiver ocupada, desenha um ponto no centro da c�lula
                SDL_RenderDrawPoint(renderer, x * 720 / 2 / 10 + 720 / 2 / 10 / 2,
                    y * 720 / 2 / 10 + 720 / 2 / 10 / 2);
            }
        }
}

// Fun��o para verificar colis�es entre uma pe�a e o campo de jogo
bool Well::isCollision(const Tetromino& t) const {
    // Loop para percorrer cada c�lula da pe�a
    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 4; ++y)
            // Verifica se a c�lula da pe�a est� ocupada
            if (t.isBlock(x, y)) {
                // Calcula as coordenadas absolutas no campo de jogo para a c�lula da pe�a
                auto wx = t.x() + x;
                auto wy = t.y() + y;

                // Verifica se as coordenadas est�o fora dos limites do campo de jogo
                if (wx < 0 || wx >= Width || wy < 0 || wy >= Height)
                    return true;

                // Verifica se a c�lula do campo de jogo est� ocupada
                if (data[wx][wy])
                    return true;
            }
    return false;
}

// Fun��o para unir uma pe�a ao campo de jogo quando ela atinge o fundo
void Well::unite(const Tetromino& t) {
    // Loop para percorrer cada c�lula da pe�a
    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 4; ++y)
            // Verifica se a c�lula da pe�a est� ocupada
            if (t.isBlock(x, y))
                // Marca a c�lula correspondente no campo de jogo como ocupada
                data[t.x() + x][t.y() + y] = true;

    // Loop para percorrer cada linha do campo de jogo, come�ando do fundo
    for (int y = Height - 1; y >= 0; --y) {
        // Flag para indicar se a linha � s�lida (todas as c�lulas ocupadas)
        bool solida = true;

        // Loop para percorrer cada c�lula na linha
        for (int x = 0; x < Width; ++x)
            // Verifica se a c�lula est� vazia
            if (!data[x][y]) {
                // Se encontrar uma c�lula vazia, a linha n�o � s�lida
                solida = false;
                break;
            }

        // Se a linha for s�lida, move as linhas acima para baixo
        if (solida) {
            for (int yy = y - 1; yy >= 0; --yy)
                for (int x = 0; x < Width; ++x)
                    data[x][yy + 1] = data[x][yy];

            // Limpa a linha superior ap�s mover as linhas para baixo
            for (int x = 0; x < Width; ++x)
                data[x][0] = false;
        }
    }
}