#include "SceneAStar.h"
#include "AStar.h"
#include "PathFollowing.h"

using namespace std;

SceneAStar::SceneAStar()
{
	agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setPosition(maze->cell2pix(maze->getRandomValidPosition()));
	agent->setPathAlgorithm(new AStar());
	
	SetRandomCoinPosition(agent->getPosition());
	agent->SetPathFindingTarget(*maze->getNode(coinPosition));
	agent->ApplyPathFinding(maze);
}

SceneAStar::~SceneAStar()
{
	Scene::~Scene();
	delete agent;
}

void SceneAStar::Update(float dtime, SDL_Event* event)
{
	Scene::Update(dtime, event);
	agent->Update(dtime, event, *maze);
	
	// if the agent arrived to the coin, replace it in a random cell!
	if ((agent->getCurrentTargetIndex() == -1)
		&& (maze->pix2cell(agent->getPosition()) == coinPosition))
	{
		SetRandomCoinPosition(agent->getPosition());
		agent->SetPathFindingTarget(*maze->getNode(coinPosition));
		agent->ApplyPathFinding(maze);
	}
}

void SceneAStar::Draw()
{
	DrawMaze();
	DrawCoin();

	agent->getPathAlgorithm()->Draw(maze);
	agent->Draw();
}

const char* SceneAStar::GetTitle()
{
	return "SDL Path Finding :: AStar";
}

void SceneAStar::DrawCoin()
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

void SceneAStar::SetRandomCoinPosition(Vector2D characterPosition)
{
	coinPosition = maze->getRandomValidPosition();
	while (Vector2D::Distance(characterPosition, coinPosition) < 3)
		coinPosition = maze->getRandomValidPosition();
}
