#include "rough_minigame.h"

#define GRAVITY 0.5
TFT_eSPI tft = TFT_eSPI();

// ******* Obstacle ******* //

obstacle::obstacle() {
  this->x = SCREEN_WIDTH;
  this->y = 250;
  this->w = 20;
  this->h = 20;
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
  this->y = 250;
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

char* player::get_current_sprite() const {
  return this->sprites[this->sprite_index];
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
        this->sprite_index = 0;
    }
    if (this->jumped) {
        this->y += this->y_speed;
        this->y_speed += GRAVITY;
    } else {
      if (button_pressed) {
        this->jump();
        button_pressed = false;
      }
    }
}

void player::jump() {
    this->y_speed = -10;
    this->jumped = true;
    this->sprite_index = 1;
}

// ******* Game ******* //

Minigame::Minigame() {
  randomSeed(analogRead(0));
  this->obstacle_count = 0;
  this->baseline_speed = 20;
  this->current_speed = 20;
  this->score = 0;
  this->level = 1;
  this->game_over = false;
}

void Minigame::setup() {
    this->draw();
    while (!button_pressed);
}

void Minigame::update() {
    for (int i = 0; i < this->obstacle_count; i++) {   
        if (this->obstacles[i].collided(this->current_player)) {
            this->game_over = true;
            break;
        }
        else if (this->obstacles[i].get_x() + this->obstacles[i].get_w() < 0) {
            this->dequeue_obstacle(i);
            this->score++;
//            lv_label_set_text(scoreLabel, "Highscore " + String(highscore) + " \t Score: " + String(this->score));
            if (this->score % LEVEL_UP_INCREMENT == 0) {
                this->level++;
                this->current_speed = this->baseline_speed * (1 + this->level/10);
            }
        }
        else {
            this->obstacles[i].update(this->current_speed);
        }
    }
    this->current_player.update();
    this->generate_obstacle();
}

void Minigame::draw() {
    tft.fillScreen(TFT_BLACK);
    tft.fillCircle(this->current_player.get_x(), this->current_player.get_y(), this->current_player.get_w(), TFT_GREEN);
    for (int i = 0; i < this->obstacle_count; i++) {
        tft.fillRect(this->obstacles[i].get_x(), this->obstacles[i].get_y(), this->obstacles[i].get_w(), this->obstacles[i].get_h(), TFT_RED);
    }
}

void Minigame::loop() {
    while (!game_over) {
        this->update();
        this->draw();
    }
}

void Minigame::gameOverScreen() {
    this->current_player.set_sprite_index(2);
    if (this->score > highscore) {
        highscore = this->score;
    }
    delay(5000);
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

void setup() {
    randomSeed(analogRead(0));
    attachInterrupt(BUTTON_PIN, buttonRoutine, RISING);
}

void loop() {
    Minigame game;
    game.setup();
    game.loop();
    game.gameOverScreen();
}