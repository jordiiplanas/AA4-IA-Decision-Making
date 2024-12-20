#include "Scene.h"

Scene::Scene()
{
    drawGrid = false;
    maze = new Grid("../res/maze.csv");
    LoadTextures("../res/maze.png", "../res/coin.png");
}

Scene::~Scene()
{
    if (background_texture)
        SDL_DestroyTexture(background_texture);
    if (coin_texture)
        SDL_DestroyTexture(coin_texture);
}

void Scene::Update(float dtime, SDL_Event* event)
{
    /* Keyboard & Mouse events */
    switch (event->type) {
    case SDL_KEYDOWN:
        if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
            drawGrid = !drawGrid;
        break;
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
        if (event->button.button == SDL_BUTTON_LEFT)
        {

        }
        break;
    default:
        break;
    }
}

void Scene::Draw()
{
    
}

void Scene::DrawMaze()
{
    SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
    SDL_Rect rect;
    Vector2D coords;
    for (int j = 0; j < maze->getNumCellY(); j++)
    {
        for (int i = 0; i < maze->getNumCellX(); i++)
        {
            if (!maze->isValidCell(Vector2D((float)i, (float)j)))
            {
                SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 90, 255, 255);
                coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
                rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
                SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
            }
            else {
                // Do not draw if it is not necessary (bg is already black)
                coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
                rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };

                Node* node = maze->getNode(Vector2D((float)i, (float)j));

                if (node != nullptr)
                {
                    int value = node->weight * 10;

                    SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, value, value, 255);
                }


                SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
            }
        }
    }
    if (drawGrid == true)
    {
        SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
        for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
        {
            SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
        }
        for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
        {
            SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
        }
    }
}

bool Scene::LoadTextures(char* filename_bg, char* filename_coin)
{
    SDL_Surface* image = IMG_Load(filename_bg);
    if (!image) {
        return false;
    }
    background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

    if (image)
        SDL_FreeSurface(image);

    image = IMG_Load(filename_coin);
    if (!image) {
        return false;
    }
    coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

    if (image)
        SDL_FreeSurface(image);

    return true;
}

void Scene::SetRandomCoinPosition()
{
}


