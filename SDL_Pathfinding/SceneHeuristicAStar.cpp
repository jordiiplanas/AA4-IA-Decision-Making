#include "SceneHeuristicAStar.h"
#include "AStar.h"
#include "PathFollowing.h"

using namespace std;

SceneHeuristicAStar::SceneHeuristicAStar()
{
    agent = new Agent;
    agent->loadSpriteTexture("../res/soldier.png", 4);
    agent->setBehavior(new PathFollowing);
    agent->setPosition(maze->cell2pix(maze->getRandomValidPosition()));
    agent->setPathAlgorithm(new AStar());
	
    SetRandomCoinsPosition(agent->getPosition());
    currentCoin = GetNearestCoinIndex(agent->getPosition());
    agent->SetPathFindingTarget(*maze->getNode(coinPositions[currentCoin]));
    agent->ApplyPathFinding(maze);
}

SceneHeuristicAStar::~SceneHeuristicAStar()
{
    Scene::~Scene();
    delete agent;
}

void SceneHeuristicAStar::Update(float dtime, SDL_Event* event)
{
    Scene::Update(dtime, event);
    agent->Update(dtime, event, *maze);
	
    // if the agent arrived to the coin, replace it in a random cell!
    if ((agent->getCurrentTargetIndex() == -1)
        && (maze->pix2cell(agent->getPosition()) == coinPositions[currentCoin]))
    {
        SetRandomCoinPosition(agent->getPosition(), currentCoin);
        currentCoin = GetNearestCoinIndex(agent->getPosition());
        agent->SetPathFindingTarget(*maze->getNode(coinPositions[currentCoin]));
        agent->ApplyPathFinding(maze);
    }
}

void SceneHeuristicAStar::Draw()
{
    DrawMaze();
    DrawCoin();

    agent->getPathAlgorithm()->Draw(maze);
    agent->Draw();
}

const char* SceneHeuristicAStar::GetTitle()
{
    return "SDL Path Finding :: AStar With Multiple Coins";
}

void SceneHeuristicAStar::DrawCoin()
{
    for (int i = 0 ; i < coinPositions.size(); i++)
    {
        Vector2D coinPositionOnMaze = maze->cell2pix(coinPositions[i]);
        int offset = CELL_SIZE / 2;
	
        SDL_Rect rect = {
            (int)coinPositionOnMaze.x - offset,
            (int)coinPositionOnMaze.y - offset,
            CELL_SIZE,
            CELL_SIZE };
	
        SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &rect);
    }
}

void SceneHeuristicAStar::SetRandomCoinsPosition(Vector2D characterPosition)
{
    Vector2D position;
    for (int i = 0; i < coinsAmount; i++)
    {
        position = maze->getRandomValidPosition();
        while (Vector2D::Distance(characterPosition, position) < 3)
            position = maze->getRandomValidPosition();
        coinPositions.push_back(position);
    }
    
}

int SceneHeuristicAStar::GetNearestCoinIndex(Vector2D characterPosition) const
{
    float minDistance = 9999;
    int index = -1;
    for (int i = 0; i < coinsAmount; i++)
    {
        float distance = Vector2D::Distance(maze->pix2cell(characterPosition), coinPositions[i]);
        if (distance < minDistance)
        {
            minDistance = distance;
            index = i;
        }
    }
    return index;
}

void SceneHeuristicAStar::SetRandomCoinPosition(Vector2D characterPosition, int coin)
{
    Vector2D position;
    position = maze->getRandomValidPosition();
    while (Vector2D::Distance(maze->pix2cell(characterPosition), position) < 3)
        position = maze->getRandomValidPosition();
    
    coinPositions[coin] = position;
    
}
