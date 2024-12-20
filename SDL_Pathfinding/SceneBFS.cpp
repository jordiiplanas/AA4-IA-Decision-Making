#include "SceneBFS.h"

#include "BFS.h"
#include "PathFollowing.h"
using namespace std;

SceneBFS::SceneBFS() : Scene()
{
	agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setPosition(maze->cell2pix(maze->getRandomValidPosition()));
	agent->setPathAlgorithm(new BFS());
	
	SetRandomCoinPosition(agent->getPosition());
	agent->SetPathFindingTarget(*maze->getNode(coinPosition));
	agent->ApplyPathFinding(maze);
}

SceneBFS::~SceneBFS()
{
	Scene::~Scene();
	delete agent;
}

void SceneBFS::Update(float dtime, SDL_Event* event)
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

void SceneBFS::Draw()
{
	DrawMaze();
	DrawCoin();

	agent->getPathAlgorithm()->Draw(maze);
	agent->Draw();
}

const char* SceneBFS::GetTitle()
{
	return "SDL Path Finding :: BFS";
}

void SceneBFS::DrawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void SceneBFS::SetRandomCoinPosition(Vector2D characterPosition)
{
	coinPosition = maze->getRandomValidPosition();
	while (Vector2D::Distance(characterPosition, coinPosition) < 3)
		coinPosition = maze->getRandomValidPosition();
}
