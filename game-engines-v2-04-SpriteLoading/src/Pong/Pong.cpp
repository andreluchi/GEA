#include </home/vboxuser/Desktop/juegos/game-engines-v2-04-SpriteLoading/include/print.h>
#include "Pong.h"
#include "Systems.h"
#include "Components.h"

#include "../ECS/Entity.h"

Pong::Pong() : Game("Sprites", SCREEN_WIDTH, SCREEN_HEIGHT) {
 Scene* gameplayScene = createGameplayScene();
 setScene(gameplayScene);
}

Pong::~Pong() {
 // destructor implementation
}

Scene* Pong::createGameplayScene()
{
 Scene* scene = new Scene("GAMEPLAY SCENE");

 Entity white = scene->createEntity("player1", 0, 20);
 auto& s1 = white.addComponent<SpriteComponent>(
 "Sprites/Cat/SpriteSheetP1.png",
 0, 0,
 220,
 8,
 0,
 SDL_Color{255, 255, 255, 255}, // Set the initial color to white
 PixelShader{
  [](Uint32 color) -> Uint32 {
    Uint8 r = (color >> 24) & 0xFF;
    Uint8 g = (color >> 16) & 0xFF;
    Uint8 b = (color >> 8) & 0xFF;
    Uint8 a = color & 0xFF;
    Uint8 originalR = 181;
    Uint8 originalG = 181;
    Uint8 originalB = 181;
    Uint8 range = 100;
    Uint8 newR = 210;
    Uint8 newG = 180;
    Uint8 newB = 140;
    return (r >= originalR - range && r <= originalR + range &&
            g >= originalG - range && g <= originalG + range &&
            b >= originalB - range && b <= originalB + range)
           ? (newR << 24) | (newG << 16) | (newB << 8) | a
           : color;
  },
  "red"
 }
 );
 s1.lastUpdate = SDL_GetTicks();

 Entity black = scene->createEntity("enemy", 60, 28);
 auto& s2 = black.addComponent<SpriteComponent>(
 "Sprites/Cat/SpriteSheetP2.png",
 0, 0,
 100,
 8,
 0,
 SDL_Color{255, 255, 255, 255}, // Set the initial color to white
 PixelShader{
  [](Uint32 color) -> Uint32 {
    Uint8 r = (color >> 24) & 0xFF;
    Uint8 g = (color >> 16) & 0xFF;
    Uint8 b = (color >> 8) & 0xFF;
    Uint8 a = color & 0xFF;
    Uint8 originalR = 254;
    Uint8 originalG = 0;
    Uint8 originalB = 0;
    Uint8 range = 100;
    Uint8 newR = 0;
    Uint8 newG = 255;
    Uint8 newB = 0;
    return (r >= originalR - range && r <= originalR + range &&
            g >= originalG - range && g <= originalG + range &&
            b >= originalB - range && b <= originalB + range)
           ? (newR << 24) | (newG << 16) | (newB << 8) | a
           : color;
  },
  "green"
 }
 );
 s2.lastUpdate = SDL_GetTicks();

 scene->addSetupSystem<SpriteSetupSystem>(renderer);
 scene->addRenderSystem<SpriteRenderSystem>();
 scene->addUpdateSystem<SpriteUpdateSystem>();

 return scene;
}
