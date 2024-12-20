#include "SceneGreedy.h"
#include "Greedy.h"
#include "PathFollowing.h"

using namespace std;

SceneGreedy::SceneGreedy() : Scene()
{
	agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setPosition(maze->cell2pix(maze->getRandomValidPosition()));
	agent->setPathAlgorithm(new Greedy());
	
	SetRandomCoinPosition(agent->getPosition());
	agent->SetPathFindingTarget(*maze->getNode(coinPosition));
	agent->ApplyPathFinding(maze);
}

SceneGreedy::~SceneGreedy()
{
	Scene::~Scene();
	delete agent;
}

void SceneGreedy::Update(float dtime, SDL_Event* event)
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

void SceneGreedy::Draw()
{
	DrawMaze();
	DrawCoin();

	agent->getPathAlgorithm()->Draw(maze);
	agent->Draw();
}

const char* SceneGreedy::GetTitle()
{
	return "SDL Path Finding :: Greedy";
}


void SceneGreedy::DrawCoin()
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


void SceneGreedy::SetRandomCoinPosition(Vector2D characterPosition)
{
	coinPosition = maze->getRandomValidPosition();
	while (Vector2D::Distance(characterPosition, coinPosition) < 3)
		coinPosition = maze->getRandomValidPosition();
}
