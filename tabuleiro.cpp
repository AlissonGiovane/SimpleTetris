#include "well.hpp"

Well::Well() : data{ {false} } {}

// Função para desenhar o campo de jogo no renderizador
void Well::draw(SDL_Renderer* renderer) {
    // Configura a cor de desenho para branco
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    // Loop para percorrer cada célula do campo de jogo
    for (auto x = 0; x < Width; ++x)
        for (auto y = 0; y < Height; ++y) {
            // Verifica se a célula está ocupada
            if (data[x][y]) {
                // Se estiver ocupada, desenha um retângulo preenchido na posição correspondente
                SDL_Rect rect{ x * 720 / 2 / 10 + 1, y * 720 / 2 / 10 + 1, 720 / 2 / 10 - 2, 720 / 2 / 10 - 2 };
                SDL_RenderFillRect(renderer, &rect);
            }
            else {
                // Se não estiver ocupada, desenha um ponto no centro da célula
                SDL_RenderDrawPoint(renderer, x * 720 / 2 / 10 + 720 / 2 / 10 / 2,
                    y * 720 / 2 / 10 + 720 / 2 / 10 / 2);
            }
        }
}

// Função para verificar colisões entre uma peça e o campo de jogo
bool Well::isCollision(const Tetromino& t) const {
    // Loop para percorrer cada célula da peça
    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 4; ++y)
            // Verifica se a célula da peça está ocupada
            if (t.isBlock(x, y)) {
                // Calcula as coordenadas absolutas no campo de jogo para a célula da peça
                auto wx = t.x() + x;
                auto wy = t.y() + y;

                // Verifica se as coordenadas estão fora dos limites do campo de jogo
                if (wx < 0 || wx >= Width || wy < 0 || wy >= Height)
                    return true;

                // Verifica se a célula do campo de jogo está ocupada
                if (data[wx][wy])
                    return true;
            }
    return false;
}

// Função para unir uma peça ao campo de jogo quando ela atinge o fundo
void Well::unite(const Tetromino& t) {
    // Loop para percorrer cada célula da peça
    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 4; ++y)
            // Verifica se a célula da peça está ocupada
            if (t.isBlock(x, y))
                // Marca a célula correspondente no campo de jogo como ocupada
                data[t.x() + x][t.y() + y] = true;

    // Loop para percorrer cada linha do campo de jogo, começando do fundo
    for (int y = Height - 1; y >= 0; --y) {
        // Flag para indicar se a linha é sólida (todas as células ocupadas)
        bool solida = true;

        // Loop para percorrer cada célula na linha
        for (int x = 0; x < Width; ++x)
            // Verifica se a célula está vazia
            if (!data[x][y]) {
                // Se encontrar uma célula vazia, a linha não é sólida
                solida = false;
                break;
            }

        // Se a linha for sólida, move as linhas acima para baixo
        if (solida) {
            for (int yy = y - 1; yy >= 0; --yy)
                for (int x = 0; x < Width; ++x)
                    data[x][yy + 1] = data[x][yy];

            // Limpa a linha superior após mover as linhas para baixo
            for (int x = 0; x < Width; ++x)
                data[x][0] = false;
        }
    }
}