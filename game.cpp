#include "game.hpp"
#include <stdexcept>
#include <iostream>

Game::Game() :
    tetromino_{ static_cast<Tetromino::Type>(rand() % 7) },
    moveTime_(SDL_GetTicks())
{
    // Inicializa a biblioteca SDL para vídeo
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO)");

    // Cria uma janela e um renderizador com dimensões específicas
    SDL_CreateWindowAndRenderer(720 / 2, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window_, &renderer_);
    // Define a posição da janela
    SDL_SetWindowPosition(window_, 65, 126);
}

Game::~Game()
{
    // Libera recursos da janela e do renderizador
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    // Finaliza a biblioteca SDL
    SDL_Quit();
}

bool Game::tick()
{
    SDL_Event e;
    // Aguarda eventos com um timeout de 250 milissegundos
    if (SDL_WaitEventTimeout(&e, 250))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_DOWN:
            {
                // Cria um tetromino temporário movido para baixo
                Tetromino t = tetromino_;
                t.move(0, 1);
                // Verifica se há colisão antes de mover
                if (!well_.isCollision(t))
                    tetromino_ = t;
            }
            break;
            case SDLK_RIGHT:
            {
                // Cria um tetromino temporário movido para a direita
                Tetromino t = tetromino_;
                t.move(1, 0);
                // Verifica se há colisão antes de mover
                if (!well_.isCollision(t))
                    tetromino_ = t;
            }
            break;
            case SDLK_LEFT:
            {
                // Cria um tetromino temporário movido para a esquerda
                Tetromino t = tetromino_;
                t.move(-1, 0);
                // Verifica se há colisão antes de mover
                if (!well_.isCollision(t))
                    tetromino_ = t;
            }
            break;
            case SDLK_UP:
            {
                // Cria um tetromino temporário rotacionado
                Tetromino t = tetromino_;
                t.rotate();
                // Verifica se há colisão antes de rotacionar
                if (!well_.isCollision(t))
                    tetromino_ = t;
            }
            break;
            }
        }
        break;
        case SDL_QUIT:
            return false;
        }
    }
    // Configura a cor de desenho para preto
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xff);
    // Limpa o renderizador
    SDL_RenderClear(renderer_);
    // Desenha o poço e o tetromino
    well_.draw(renderer_);
    tetromino_.draw(renderer_);
    if (SDL_GetTicks() > moveTime_)
    {
        moveTime_ += 1000;
        // Cria um tetromino temporário movido para baixo
        Tetromino t = tetromino_;
        t.move(0, 1);
        check(t);
    }
    // Apresenta o renderizador
    SDL_RenderPresent(renderer_);
    return true;
};

void Game::check(const Tetromino& t)
{
    if (well_.isCollision(t))
    {
        // Unifica o tetromino atual com o poço
        well_.unite(tetromino_);
        // Gera um novo tetromino aleatório
        tetromino_ = Tetromino{ static_cast<Tetromino::Type>(rand() % 7) };
        if (well_.isCollision(tetromino_))
        {
            // Reinicia o poço se houver colisão com o novo tetromino
            well_ = Well();
        }
    }
    else
    {
        // Atualiza o tetromino atual
        tetromino_ = t;
    }
}