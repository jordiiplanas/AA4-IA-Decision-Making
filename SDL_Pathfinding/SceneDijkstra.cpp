#include "SceneDijkstra.h"

#include "Dijkstra.h"
#include "PathFollowing.h"

using namespace std;

SceneDijkstra::SceneDijkstra() : Scene()
{
	agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setPosition(maze->cell2pix(maze->getRandomValidPosition()));
	agent->setPathAlgorithm(new Dijkstra());
	
	SetRandomCoinPosition(agent->getPosition());
	agent->SetPathFindingTarget(*maze->getNode(coinPosition));
	agent->ApplyPathFinding(maze);
}

SceneDijkstra::~SceneDijkstra()
{
	Scene::~Scene();
	delete agent;
}

void SceneDijkstra::Update(float dtime, SDL_Event* event)
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

void SceneDijkstra::Draw()
{
	DrawMaze();
	DrawCoin();

	agent->getPathAlgorithm()->Draw(maze);
	agent->Draw();
}

const char* SceneDijkstra::GetTitle()
{
	return "SDL Path Finding :: Dijkstra";
}


void SceneDijkstra::DrawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void SceneDijkstra::SetRandomCoinPosition(Vector2D characterPosition)
{
	coinPosition = maze->getRandomValidPosition();
	while (Vector2D::Distance(characterPosition, coinPosition) < 3)
		coinPosition = maze->getRandomValidPosition();
}
