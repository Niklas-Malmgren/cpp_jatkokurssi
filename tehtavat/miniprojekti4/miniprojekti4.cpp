#include <iostream>
#include <cmath>
#include <stdio.h>
#include "box2d/box2d.h"
#include "SDL2/SDL.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);

int main(int argc, char** argv) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow(
		"BouncyBall",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	float ground_width = 300.0f;
	float ground_height = 10.0f;

	float ground_posx = SCREEN_WIDTH / 2;
	float ground_posy = SCREEN_HEIGHT - 50;

	float box_width = 30.0f;
	float box_height = 30.0f;

	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(ground_posx, ground_posy);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(ground_width / 2, ground_height / 2);
	groundBody->CreateFixture(&groundBox, 0.0f);


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(SCREEN_WIDTH / 2, -1000);
	b2Body* body = world.CreateBody(&bodyDef);

	b2BodyDef circleDef;
	circleDef.type = b2_dynamicBody;
	circleDef.position.Set(SCREEN_WIDTH / 2, 0);
	b2Body* circleBody = world.CreateBody(&circleDef);

	b2BodyDef circleDef2;
	circleDef2.type = b2_dynamicBody;
	circleDef2.position.Set(SCREEN_WIDTH / 2 - 150, 0);
	b2Body* circleBody2 = world.CreateBody(&circleDef2);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(box_width, box_height / 2);

	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = 20.0f;
	b2CircleShape dynamicCircle2;
	dynamicCircle2.m_radius = 20.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	b2FixtureDef circleFixture;
	circleFixture.shape = &dynamicCircle;
	circleFixture.restitution = 0.8f;
	b2FixtureDef circleFixture2;
	circleFixture2.shape = &dynamicCircle2;
	circleFixture2.restitution = 0.6f;

	fixtureDef.density = 1.0f;
	circleFixture.density = 1.0f;
	circleFixture2.density = 1.0f;

	fixtureDef.friction = 0.3f;
	circleFixture.friction = 0.1f;
	circleFixture2.friction = 0.1f;

	body->CreateFixture(&fixtureDef);
	circleBody->CreateFixture(&circleFixture);
	circleBody2->CreateFixture(&circleFixture2);
	
	circleBody2->ApplyLinearImpulseToCenter(b2Vec2(50000, 50000), false);

	screenSurface = SDL_GetWindowSurface(window);
	SDL_SetRenderDrawColor(renderer, 0, 100, 150, 0);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 100, 150));
	SDL_UpdateWindowSurface(window);
	SDL_RenderClear(renderer);

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 6;

	SDL_Event event;
	bool exit_game = false;

	while (!exit_game)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit_game = true;
		}

		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();	

		SDL_Rect ground;
		ground.w = ground_width;
		ground.h = ground_height;
		ground.x = groundBody->GetPosition().x - ground_width / 2;
		ground.y = groundBody->GetPosition().y - ground_height / 2;
		SDL_SetRenderDrawColor(renderer, 155, 0, 100, 0);
		SDL_RenderFillRect(renderer, &ground);

		SDL_Rect box;
		box.w = box_width;
		box.h = box_height;
		box.x = body->GetPosition().x - box_width / 2;
		box.y = body->GetPosition().y - box_height / 2;
		SDL_SetRenderDrawColor(renderer, 155, 155, 0, 0);
		SDL_RenderFillRect(renderer, &box);
		
		SDL_RenderFillCircle(renderer, circleBody->GetPosition().x, circleBody->GetPosition().y, dynamicCircle.m_radius);
		SDL_RenderFillCircle(renderer, circleBody2->GetPosition().x, circleBody2->GetPosition().y, dynamicCircle2.m_radius);

		SDL_SetRenderDrawColor(renderer, 0, 100, 150, 0);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}


	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {

		status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
			x + offsety, y + offsetx);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
			x + offsetx, y + offsety);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
			x + offsetx, y - offsety);
		status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
			x + offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}