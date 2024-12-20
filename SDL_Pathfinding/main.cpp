#include <iostream>
#include <SDL.h>

#include "SceneGreedy.h"
#include "SDL_SimpleApp.h"
#include "SceneBFS.h"
#include "SceneDijkstra.h"
#include "SceneAStar.h"
#include "SceneGreedyWithEnemies.h"
#include "SceneHeuristicAStar.h"
#include "AutomaticTableScene.h"


using namespace std;


/*******************************************************************************
 * Main function of the SDL_Pathfinding project.
 *
 * @param  argc An integer argument count of the command line arguments
 * @param  argv An argument array of the command line arguments
 * @return an integer 0 upon exit success
 ******************************************************************************/

int main(int argc, char ** argv)
{
	std::srand(std::time(0));
	bool quit = false;
	SDL_Event event;
	
	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SceneBFS();
	app->setWindowTitle(curr_scene->GetTitle());

	
	if (argc > 1) {
		cout << argv[1] << endl; 
		exit(0);
	}

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1)
			{
				delete(curr_scene);
				curr_scene = new SceneBFS;
				app->setWindowTitle(curr_scene->GetTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2)
			{
				delete(curr_scene);
				curr_scene = new SceneDijkstra;
				app->setWindowTitle(curr_scene->GetTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3)
			{
				delete(curr_scene);
				curr_scene = new SceneGreedy;
				app->setWindowTitle(curr_scene->GetTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_4)
			{
				delete(curr_scene);
				curr_scene = new SceneAStar;
				app->setWindowTitle(curr_scene->GetTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_5)
			{
				delete(curr_scene);
				curr_scene = new SceneGreedyWithEnemies;
				app->setWindowTitle(curr_scene->GetTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_6)
			{
				delete(curr_scene);
				curr_scene = new SceneHeuristicAStar;
				app->setWindowTitle(curr_scene->GetTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_7)
			{
				delete(curr_scene);
				curr_scene = new AutomaticTableScene;
				app->setWindowTitle(curr_scene->GetTitle());
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}