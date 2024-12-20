#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Grid.h"
#include "Vector2D.h"

class PathFindingAlgorithm;

class Grid;

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent* agent, float , const Grid& grid) {};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	// Pathfinding
	PathFindingAlgorithm* pathAlgorithm;
	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target) { this->target = target; }
	void SetPathFindingTarget(Node _target);
	void ApplyPathFinding(Grid* maze);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void Update(float dtime, SDL_Event* event, Grid grid);
	void Draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	inline void setPathAlgorithm(PathFindingAlgorithm* algorithm) { pathAlgorithm = algorithm; }
	inline PathFindingAlgorithm* getPathAlgorithm() { return pathAlgorithm; }
	
};
