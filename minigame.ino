#include "cubiko.h"
#include "minigame.h"

#define GRAVITY 0.1
const int LEVEL_UP_INCREMENT = 10;

// ******* Map ******* //

gameMap::gameMap() {
  this->x = 0;
  this->y = 0;
  this->h = 0;
  this->sprite_index = 0;
}

int gameMap::get_x() const {
  return this->x;
}

int gameMap::get_y() const {
  return this->y;
}

int gameMap::get_h() const {
  return this->h;
}

void gameMap::update(int speed) {
  this->x -= speed;
}

// ******* Obstacle ******* //

obstacle::obstacle() {
  this->x = 0;
  this->y = 0;
  this->sprite_index = random(0, 3);
  this->w = 0;
  this->h = 0;
}

int obstacle::get_x() const {
  return this->x;
}

int obstacle::get_y() const {
  return this->y;
}

int obstacle::get_w() const {
  return this->w;
}

int obstacle::get_h() const {
  return this->h;
}

void obstacle::update(int speed) {
  this->x -= speed;
}

// ******* Player ******* //

player::player() {
  this->y = 100;
  this->w = 20;
  this->h = 20;
  this->y_speed = 0;
  this->sprite_index = 0;
}

int player::get_y() const {
  return this->y;
}

int player::get_y_speed() const {
  return this->y_speed;
}

void player::update() {
    // Update player
    if (this->jumped) {
        this->y += this->y_speed;
        this->y_speed += GRAVITY;
        this->sprite_index = 2;
    }
    if (this->y > this->baseline_y) {
        this->y = this->baseline_y;
        this->y_speed = 0;
        this->jumped = false;
        this->sprite_index = 0? 1: 0;
    }
}

void player::jump() {
    this->y_speed = -10;
    this->jumped = true;
}

// ******* Game ******* //

Minigame::Minigame() {
  randomSeed(analogRead(0));
  this->obstacle_count = 0;
  this->baseline_speed = 10;
  this->current_speed = 10;
  this->score = 0;
  this->level = 1;
  this->highscore = 0;
  this->game_over = false;
}

void Minigame::setup() {
  // Nothing to do
}


void Minigame::update() {
    bool button_pressed = false;
    for (int i = 0; i < obstacle_count; i++) {   
        if (obstacles[i].collided(this->current_player)) {
            game_over = true;
            break;
        }
        else if (obstacles[i].get_x() + obstacles[i].get_h() < 0) {
            dequeue_obstacle(i);
            this->score++;
            if (this->score % LEVEL_UP_INCREMENT == 0) {
                this->level++;
                this->current_speed = this->baseline_speed * (1 + this->level/10);
            }
        }
        else {
            obstacles[i].update(current_speed);
        }
    }
    if (button_pressed) {
        this->current_player.jump();
    }
    this->current_player.update();
    this->current_map.update(this->current_speed);
}

void Minigame::draw() {
    // Nothing to do
}

void Minigame::loop() {
    while (!game_over) {
        this->update();
        this->draw();
    }
}

mainState minigameFunc() {
    bool in_game = true;
    while (in_game) {
        Minigame game;
        game.setup();
        game.loop();
    }
    in_game = false;
    pageBack();
}