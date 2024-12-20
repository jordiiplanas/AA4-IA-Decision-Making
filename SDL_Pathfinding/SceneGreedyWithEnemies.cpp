#include "SceneGreedyWithEnemies.h"

#include "PathFollowing.h"

#define DISTANCE_FROM_PLAYER_TO_ENEMIES 6


SceneGreedyWithEnemies::SceneGreedyWithEnemies() : Scene()
{
    agent = new Agent;
    agent->loadSpriteTexture("../res/soldier.png", 4);
    agent->setBehavior(new PathFollowing);
    agent->setPosition(maze->cell2pix(maze->getRandomValidPosition()));

    // Set Paths
    paths[0].push_back(Vector2D(24, 4));
    paths[0].push_back(Vector2D(24, 2));
    paths[0].push_back(Vector2D(4, 2));
    paths[0].push_back(Vector2D(4, 4));

    paths[1].push_back(Vector2D(36, 20));
    paths[1].push_back(Vector2D(36, 13));
    paths[1].push_back(Vector2D(20, 13));
    paths[1].push_back(Vector2D(20, 20));

    Agent* enemy = new Agent;
    enemy->loadSpriteTexture("../res/zombie1.png", 8);
    enemy->setBehavior(new PathFollowing);
    enemy->setPosition(maze->cell2pix(Vector2D(24, 4)));
    enemies.push_back(new GreedyWithEnemies::Enemy(enemy, 0));

    enemy = new Agent;
    enemy->loadSpriteTexture("../res/zombie1.png", 8);
    enemy->setBehavior(new PathFollowing);
    enemy->setPosition(maze->cell2pix(Vector2D(36, 20)));

    enemies.push_back(new GreedyWithEnemies::Enemy(enemy, 1));

    GreedyWithEnemies* greedy = new GreedyWithEnemies();
    greedy->SetEnemies(enemies);

    agent->setPathAlgorithm(greedy);
    
    SetRandomCoinPosition(agent->getPosition());
    agent->SetPathFindingTarget(*maze->getNode(coinPosition));
    agent->ApplyPathFinding(maze);
}

SceneGreedyWithEnemies::~SceneGreedyWithEnemies()
{
    Scene::~Scene();
    delete agent;
    for (auto enemy : enemies)
    {
        delete enemy;
    }
}

void SceneGreedyWithEnemies::Update(float dtime, SDL_Event* event)
{
    Scene::Update(dtime, event);
    agent->Update(dtime, event, *maze);
    for (auto enemy : enemies)
    {
        enemy->agent->Update(dtime, event, *maze);
        if (enemy->agent->getPathSize() == 0)
        {
            for (Vector2D pos : paths[enemy->path])
            {
                enemy->agent->addPathPoint(maze->cell2pix(pos));
            }
        }
    }

    bool isNearAnyEnemy = false;
    for (auto enemy : enemies)
    {
        float distance = Vector2D::Distance(
            maze->pix2cell(agent->getPosition()),
            maze->pix2cell(enemy->agent->getPosition()));
        if (distance <= DISTANCE_FROM_PLAYER_TO_ENEMIES)
        {
            isNearAnyEnemy = true;
        }
    }

    if (isNearAnyEnemy)
    {
        agent->clearPath();
        agent->SetPathFindingTarget(*maze->getNode(coinPosition));
        agent->ApplyPathFinding(maze);
    }
    
    // if the agent arrived to the coin, replace it in a random cell!
    if ((agent->getCurrentTargetIndex() == -1)
        && (maze->pix2cell(agent->getPosition()) == coinPosition))
    {
        SetRandomCoinPosition(agent->getPosition());
        agent->SetPathFindingTarget(*maze->getNode(coinPosition));
        agent->ApplyPathFinding(maze);
    }
}
void SceneGreedyWithEnemies::Draw()
{
    DrawMaze();
    DrawCoin();

    agent->getPathAlgorithm()->Draw(maze);
    agent->Draw();
    for (auto enemy : enemies)
    {
        enemy->agent->Draw();
    }
}

const char* SceneGreedyWithEnemies::GetTitle()
{
    return "SDL Path Finding :: Greedy with Enemies";
}


void SceneGreedyWithEnemies::DrawCoin()
{
    Vector2D coinPositionOnMaze = maze->cell2pix(coinPosition);
    int offset = CELL_SIZE / 2;
	
    SDL_Rect rect = {
        (int)coinPositionOnMaze.x - offset,
        (int)coinPositionOnMaze.y - offset,
        CELL_SIZE,
        CELL_SIZE };
	
    SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &rect);
}


void SceneGreedyWithEnemies::SetRandomCoinPosition(Vector2D characterPosition)
{
    coinPosition = maze->getRandomValidPosition();
    while (Vector2D::Distance(characterPosition, coinPosition) < 3)
        coinPosition = maze->getRandomValidPosition();
}
