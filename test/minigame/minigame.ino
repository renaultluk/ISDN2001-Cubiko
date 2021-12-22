#include "minigame.h"

#define GRAVITY 0.5
const int LEVEL_UP_INCREMENT = 10;

// ******* Map ******* //

// gameMap::gameMap() {
//   this->x = 0;
//   this->y = 0;
//   this->h = 70;
//   this->sprite_index = 0;
//   this->ground_index = 0;
//   for (int i = 0; i < 4; i++) {
//     this->sprites[i] = lv_img_create(minigameScreen);
//   }
//   this->sprites[0] = "img/map.png";
//   this->sprites[1] = "img/map.png";
//   this->sprites[2] = "img/map.png";
//   for (int i = 0; i < 3; i++) {
//     this->ground[i] = lv_img_create(minigameScreen);
//     this->sprite_index = random(0, 3);
//     lv_img_set_src(this->ground[i], this->sprites[i]);
//   }
//   int ground_x = 0;
//   for (int i = 0; i < 4; i++) {
//     lv_obj_set_pos(this->ground[i], ground_x, SCREEN_HEIGHT - this->h);
//     ground_x += lv_obj_get_width(this->ground[i]);
//   }
// }

// * for wednesday

gameMap::gameMap() {
  this->x = 0;
  this->y = 0;
  this->h = 70;
  this->current_ground = lv_img_create(minigameScreen);
  lv_img_set_src(this->current_ground, "/minigame_sprites/Map.png");
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

// void gameMap::update(float speed) {
//   this->x -= speed;
//   for (int i = 0; i < 4; i++) {
//     lv_obj_offset_x(this->ground[i], -speed);
//   }
//   if (this->x + this->w < 0) {
//     for (int i = 0; i < 3; i++) {
//       this->ground[i] = this->ground[i + 1];
//     }
//     ground[3] = sprites[random(0, 3)];
//   }
// }

// ******* Background ******* //

// background::background(): gameMap() {
//   this->x = 0;
//   this->y = 0;
//   this->w = SCREEN_WIDTH;
//   this->h = SCREEN_HEIGHT;
//   for (int i = 0; i < 4; i++) {
//     this->sprites[i] = lv_img_create(minigameScreen);
//   }
//   this->sprites[0] = "img/map.png";
//   this->sprites[1] = "img/map.png";
//   this->sprites[2] = "img/map.png";
//   this->sprites[3] = "img/map.png";

//   int ground_x = 0;
//   for (int i = 0; i < 4; i++) {
//     this->ground[i] = lv_img_create(minigameScreen);
//     this->ground[i] = sprites[random(0, 3)];
//     lv_obj_set_pos(this->ground[i], ground_x, 0);
//     lv_obj_move_background(this->ground[i]);
//     ground_x += lv_obj_get_width(this->ground[i]);
//   }
// }

// ******* Obstacle ******* //

obstacle::obstacle() {
  this->x = SCREEN_WIDTH;
  this->y = 250;
  for (int i = 0; i < 4; i++) {
    this->sprites[i] = lv_img_create(minigameScreen);
  }
  this->sprites[0] = "/minigame_sprites/Large_Obstacle.png";
  this->sprites[1] = "/minigame_sprites/Small_Obstacle.png";
  this->sprite_index = random(0, 1);
  lv_img_set_src(this->current_sprite, sprites[sprite_index]);
  this->w = lv_img_get_width(this->current_sprite);
  this->h = lv_img_get_height(this->current_sprite);
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
  lv_img_offset_x(this->current_sprite, -speed);
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
  for (int i = 0; i < 4; i++) {
    this->sprites[i] = lv_img_create(minigameScreen);
  }
//   this->sprites[0] = "/minigame_sprites/Run.png";
//   this->sprites[1] = "/minigame_sprites/Jump.png";
//   this->sprites[2] = "/minigame_sprites/Dead.png";
  LV_IMG_DECLARE(cube_run_player_run);
  lv_img_set_src(this->sprites[0], &cube_run_player_run);
  this->sprite_index = 0;
  lv_img_set_src(this->current_sprite, sprites[sprite_index]);
  lv_obj_set_pos(this->current_sprite, this->x, this->y);
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
    }
    if (this->jumped) {
        this->y += this->y_speed;
        lv_img_offset_y(current_sprite, this->y_speed);
        this->y_speed += GRAVITY;
    } else {
      if (button_pressed) {
        this->jump();
        button_pressed = false;
      }
      this->sprite_index = 1;
      lv_img_set_src(this->current_sprite, this->sprites[this->sprite_index]);
    }
}

void player::jump() {
    this->y_speed = -10;
    this->jumped = true;
    this->sprite_index = 2;
    lv_img_set_src(this->current_sprite, this->sprites[this->sprite_index]);
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
  while(!button_pressed);
}


void Minigame::update() {
    for (int i = 0; i < obstacle_count; i++) {   
        if (obstacles[i].collided(this->current_player)) {
            game_over = true;
            break;
        }
        else if (obstacles[i].get_x() + obstacles[i].get_w() < 0) {
            dequeue_obstacle(i);
            this->score++;
            lv_label_set_text(scoreLabel, "Highscore " + String(highscore) + " \t Score: " + String(this->score));
            if (this->score % LEVEL_UP_INCREMENT == 0) {
                this->level++;
                this->current_speed = this->baseline_speed * (1 + this->level/10);
            }
        }
        else {
            obstacles[i].update(current_speed);
        }
    }
    this->current_player.update();
    // this->current_map.update(this->current_speed);
    // this->current_background.update(0.6 * this->current_speed);
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
    this->current_player.set_sprite_index(2);
    if (this->score > highscore) {
        highscore = this->score;
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

void loadMinigameScreen() {
  minigameScreen = lv_obj_create(NULL);
  lv_obj_set_size(minigameScreen, LV_HOR_RES, LV_VER_RES);
  lv_obj_set_style(minigameScreen, &lv_style_scr);
  lv_scr_load(minigameScreen);

  lv_obj_t * scoreLabel = lv_label_create(minigameScreen);
  lv_obj_align_to(scoreLabel, minigameScreen, LV_ALIGN_TOP_RIGHT, -10, 10);
  lv_label_set_text(scoreLabel, "Highscore " + String(highscore) + " \t Score: " + String(0));

  lv_obj_t * titleLabel = lv_label_create(minigameScreen);
  lv_obj_align_to(titleLabel, minigameScreen, LV_ALIGN_CENTER, 0, -20);
  lv_label_set_text(titleLabel, "DINO RUN!");

  lv_obj_t * descLabel = lv_label_create(minigameScreen);
  lv_obj_align_to(descLabel, minigameScreen, LV_ALIGN_CENTER, 0, 20);
  lv_label_set_text(descLabel, "Press the button to start");
}

void loop() {
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