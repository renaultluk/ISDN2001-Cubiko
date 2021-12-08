#include "cubiko.h"
#include "minigame.h"

#define GRAVITY 0.5
const int LEVEL_UP_INCREMENT = 10;

// ******* Map ******* //

gameMap::gameMap() {
  this->x = 0;
  this->y = SCREEN_HEIGHT;
  this->h = 70;
  this->sprite_index = 0;
  this->ground_index = 0;
  for (int i = 0; i < 4; i++) {
    this->ground[i] = sprites[random(0, 3)];
  }
}

float gameMap::get_x() const {
  return this->x;
}

float gameMap::get_y() const {
  return this->y;
}

float gameMap::get_h() const {
  return this->h;
}

void gameMap::update(float speed) {
  this->x -= speed;
  if (this->x + this->w < 0) {
    for (int i = 0; i < 4; i++) {
      ground[i] = ground[i + 1];
    }
    ground[3] = sprites[random(0, 3)];
  }
}

// ******* Background ******* //

background::background(): gameMap() {
  this->x = 0;
  this->y = 0;
  this->w = SCREEN_WIDTH;
  this->h = SCREEN_HEIGHT;
}

// ******* Obstacle ******* //

obstacle::obstacle() {
  this->x = SCREEN_WIDTH;
  this->y = 250;
  this->sprite_index = random(0, 3);
  this->w = 0;
  this->h = 0;
}

float obstacle::get_x() const {
  return this->x;
}

float obstacle::get_y() const {
  return this->y;
}

float obstacle::get_w() const {
  return this->w;
}

float obstacle::get_h() const {
  return this->h;
}

void obstacle::update(int speed) {
  this->x -= speed;
}

bool obstacle::collided(player p) {
  return (this->x < p.get_x() + p.get_w() &&
          this->x + this->w > p.get_x() &&
          this->y < p.get_y() + p.get_h() &&
          this->y + this->h > p.get_y());
}

// ******* Player ******* //

player::player() {
  this->x = 20;
  this->y = 70;
  this->w = 20;
  this->h = 20;
  this->y_speed = 0;
  this->sprite_index = 0;
}

float player::get_x() const {
  return this->x;
}

float player::get_y() const {
  return this->y;
}

float player::get_y_speed() const {
  return this->y_speed;
}

float player::get_w() const {
  return this->w;
}

float player::get_h() const {
  return this->h;
}

int player::get_sprite_index() const {
  return this->sprite_index;
}

void player::set_sprite_index(int index) {
  this->sprite_index = index;
}

void player::update() {
    // Update player
    if (this->y > this->baseline_y) {
        this->y = this->baseline_y;
        this->y_speed = 0;
        this->jumped = false;
        this->sprite_index = (this->sprite_index + 1) % 2;
    }
    if (this->jumped) {
        this->y += this->y_speed;
        this->y_speed += GRAVITY;
        this->sprite_index = 2;
    } else {
      this->sprite_index = (this->sprite_index + 1) % 2;
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
  this->baseline_speed = 20;
  this->current_speed = 20;
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
        else if (obstacles[i].get_x() + obstacles[i].get_w() < 0) {
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
    this->current_background.update(0.6 * this->current_speed);
    this->generate_obstacle();
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

void Minigame::gameOverScreen() {
    this->current_player.set_sprite_index(3);
    if (this->score > this->highscore) {
        this->highscore = this->score;
    }
}

void Minigame::generate_obstacle() {
  int random_num = random(0, 20);
  if (random_num == 0) {
    obstacle new_obstacle;
    obstacles[obstacle_count] = new_obstacle;
    obstacle_count++;
  }
}

void Minigame::dequeue_obstacle(int index) {
    for (int i = index; i < obstacle_count - 1; i++) {
        obstacles[i] = obstacles[i + 1];
    }
    obstacle_count--;
}

mainState minigameFunc() {
    bool in_game = true;
    while (in_game) {
        Minigame game;
        game.setup();
        game.loop();
        game.gameOverScreen();
    }
    in_game = false;
    pageBack();
}