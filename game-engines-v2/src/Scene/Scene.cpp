#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <print.h>

#include "Scene.h"

#include "ECS/Entity.h"
#include "ECS/Components.h"
#include "ECS/System.h"


Scene::Scene(const std::string& name)
  : name(name)
{
  // print("Scene ", name, "constructed!");

  world = new Entity(r.create(), this);
  world->addComponent<TilemapComponent>();
  world->addComponent<WorldComponent>(800 * 5, 600 * 5);

  mainCamera = new Entity(r.create(), this);
  mainCamera->addComponent<TransformComponent>(0, 0);
  mainCamera->addComponent<CameraComponent>(5, 800, 600);

  player = new Entity(r.create(), this);
  /* player->addComponent<TransformComponent>((800 * 5)/2 - 48/2, (600 * 5)/2 - 48/2); */
  player->addComponent<TransformComponent>(500, 500);
  player->addComponent<BoxColliderComponent>(16, 16, 16, 16);
  player->addComponent<SpeedComponent>(0, 0);
}

Scene::~Scene()
{
  // print("Scene Destroyed!");
}

Entity Scene::createEntity(const std::string& name, int x, int y)
{
  Entity entity = { r.create(), this };
  entity.addComponent<NameComponent>(name);
  entity.addComponent<TransformComponent>(x, y);

  return entity;
}

void Scene::setup()
{
  // print("Scene Setup");
  
  for (auto sys: setupSystems)
  {
    sys->run();
  }
}

void Scene::update(double dT)
{
  // print("Scene Update");
  
  for (auto sys: updateSystems)
  {
    sys->run(dT);
  }
}

void Scene::render(SDL_Renderer* renderer)
{
  // print("Scene Render");
  
  for (auto sys: renderSystems)
  {
    sys->run(renderer);
  }
}

void Scene::processEvents(SDL_Event event)
{
  // print("Scene Events");
  
  for (auto sys: eventSystems)
  {
    sys->run(event);
  }
}
