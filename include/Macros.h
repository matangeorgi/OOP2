#pragma once

// ------------------- Texture Holder Consts ----------------
const int I_PLAYER = 0;
const int I_ENEMY = 1;
const int I_WALL = 2;
const int I_COIN = 3;
const int I_GOAL_FLAG = 4;
const int I_MENU = 5;
const int I_LEVELS = 6;
const int I_OBSTACLES = 7;
const int I_STATIC = 8;
const int I_GOOD_OBJ = 9;
const int I_FIREWORKS = 10;

const int I_FLOOR = 0;
const int I_BRICK = 1;
const int I_BLOCK = 2;
const int I_QUESTION = 3;

const int I_POLE = 0;
const int I_FLAG = 1;

const int LEVEL_ONE = 0;
const int LEVEL_TWO = 1;

const int I_FIREBALL = 0;
const int I_FIREPOLE = 1;

const int I_PIPE = 0;
const int I_PLATFORM = 1;

const int I_SUPER_MUSH = 0;
const int I_FIRE_FLOWER = 1;

const int I_MENU_SCREEN = 0;
const int I_QUIT_SCREEN = 1;
const int I_LEADERBOARD_SCREEN = 2;

const int I_MARIO = 0;
const int I_S_MARIO = 1;
const int I_F_MARIO = 2;
const int I_BADMUSHROOM = 0;
const int I_TORTOISE = 1;
const int I_F_TORTOISE = 2;
const int I_PIRANA = 3;

const int PIRANA_SIZE = 3;
const int BAD_MUSH_SIZE = 3;
const int F_TORTOISE_SIZE = 3;
const int TORTOISE_SIZE = 3;
const int MARIO_SIZE = 9;
const int S_MARIO_SIZE = 9;
const int F_MARIO_SIZE = 10;
const int QUESTION_SIZE = 4;
const int COIN_SIZE = 5;
const int FIRE_SIZE = 2;

const int PLAYER_STAND = 0;
const int PLAYER_WALK_FIRST = 1;
const int PLAYER_WALK_END = 3;
const int PLAYER_JUMP = 4;
const int PLAYER_SLIP = 5;
const int PULLING_PIC = 6;
const int PLAYER_D = 8;
const int PLAYER_FIRE = 9;

//---------------- Player Consts --------------------
const int START_LIFE = 3;
const int ERROR_SPACE = 1;
const int MARIO_END_POS = 130;
const int SUP_MARIO_END_POS = 120;

const int KILL_POINTS = 100;
const int COIN_POINTS = 50;
const int SUPER_POINTS = 500;

//---------------- SuperMushroom Consts --------------------
const bool FIREFLOWER = true;
const bool SUPERMUSH = false;

//------------------- Animation Consts -----------------
const float SWITCH = 0.2;
const float SWITCH_PIRANA = 0.4;
const float FIRE_POLE_SWITCH = 0.05;
const float COIN_SWITCH = 0.15;
const int PULING_TIME = 5;
const int FIREPOLE_SPEED = 120;
const float FIRE_DEATH_TIME = 0.5;

const int DEATH_TIME = 1;
const int PLAYER_DEATH_TIME = 5;
const int INVINCIBLE_TIME = 3;

const int MARIO_LOCATION = 5;

//------------------- Movements Consts -----------------
const bool RIGHT = true;
const bool LEFT = false;
const bool UP = true;
const bool DOWN = false;

const int PIRANA_SPEED = 10;
const float ENEMY_SPEED = 20;
const int FIREWORKS_SPEED = 100;
const float SHELL_SPEED = 120;
const int MIN_HEIGHT = 135;
const int MAX_HEIGHT = 50;
const int FIRE_BALL_HEIGHT = 100;
const int TORTOISE_GAP = 4;
const int MUSHROOM_GAP = 2;

const float MIN_VELOCITY_X = 0.01;
const float MIN_DEC = 0.0001;
const float CHANGE_DIR_TIME = 0.8;
const int STOP_POINT = 5;

const float START_VEL = 0.05;
const float BRICK_MOVE = 0.18;
const int FALLING_VEL = 2;
const float TOP_FALL_SPEED = 200;
const float BUMP = -0.4;
const float SQUARE_BUMP = -0.1;
const float PIRANA_MOV = 2.5;
const float ACCELERATION = 0.12;
const float JUMP_START = -0.55f;
const float JUMP_DEC = 0.5f;
const float DRAG = 0.25f;
const float VEL_MAX = 230.f;
const float VEL_MIN = 20.f;
const float HEIGHT_MAX = 56.f;
const int BRICK_BUMP = 25;
const int STATIC_GAP = 3;
const int GAP_BENEATH = 2;
const int FLIP = 180;

// ------------ Board Consts --------------
const int ROWS = 13;
const int ICON_SIZE = 14;

// ------------ Scale Consts --------------
const float POLE_SCALE = 0.25;
const float PIRANA_SCALE = 0.25;
const float BLOCK_SCALE = 0.4375;
const float BRICK_SCALE = 0.4375;
const float PIPE_SCALE = 0.4375;
const float FLOOR_SCALE = 0.875;
const float QUESTION_SCALE = 0.875;
const float PLAT_X_SCALE = 0.3;
const float PLAT_Y_SCALE = 0.4;
const float SCALE = 0.15; 

// ------------ Position Consts --------------
const int COIN_X_POS = 3;
const int COIN_Y_POS = 2;
const int FLAG_X_POS = 8;
const int FLAG_Y_POS = -6;
const int PIPE_X_POS = 5;
const int PIPE_Y_POS = -7.5;
const float POLE_Y_POS = -7.5;
const float TORTOISE_Y_POS = -10;
const int FIREWORK_Y_POS = 5;

const int FLAG_DISTANCE = 5;

const float BRICK_GAP = 0.09;

// ------------ Window options Consts --------------
const int WIDTH = 1800;
const int HEIGHT = 700;
const int WINDOW_GAP = 50;
const int VIEW_HEIGHT = 182;
const int VIEW_WIDTH = 468;
const int THICKNESS = 5;
const int FONT_SIZE = 60;
const int START_X = 590;
const int START_Y = 50;
const int SCORE_X = 670;
const int SCORE_Y = 150;
const int EXIT_X = 680;
const int EXIT_Y = 250;
const int SLEEP = 4;
const int EXIT_SLEEP = 2;
const int LEADERS = 6;
const int LEADER_X = 700;
const int LEADER_Y = 150;
const int LEADER_GAP = 50;


const int SCORE = 0;
const int COINS = 1;
const int WORLD = 2;
const int TIME = 3;
const int LIFE = 4;

const int STAGE_X = 134;
const int STAGE_Y = 70;
const int SCORES_X = 15;
const int COINS_X = 115;
const int WORLD_X = 210;
const int TIME_X = 310;
const int LIFE_X = 395;
const int GAME_Y = 2;
const int GAME_FONT_SIZE = 15;

const int MESSAGES = 5;

// ------------ Menu options Consts --------------
const int QUIT = 0;
const int START = 1;
const int LEADER_BOARD = 2;
const int MENU_MESSAGES = 3;

const int BACK = 3;

// ------------ Reading map Consts --------------
const char PLAYER = 'X';
const char TORTOISE = 'T';
const char PIRANA_PLANT = 'Y';
const char FLYING_TORTOISE = 'A';
const char BAD_MUSHROOM = 'M';
const char FLOOR = '#';
const char BLOCK = 'B';
const char QUESTION = '?';
const char BRICK = '&';
const char COIN = '$';
const char GOAL_FLAG = 'F';
const char GOAL_POLE = 'J';
const char SUPER_MUSH = 'S';
const char PLATFORM = 'L';
const char FIRE_BALL = 'O';
const char FIRE_POLE = 'I';
const char FIRE_FLOWER = 'K';
const char PIPE = 'P';
const char MENU = 'U';
const char AIR = ' ';
const char FIREWORKS = '*';

// ------------ Controller Consts --------------
const int STAGE_TIME = 200;

// ------------ Audio Holder Consts --------------
const int AUDIOS = 12;
const int AUDIO_KILL = 0;
const int AUDIO_JUMP = 1;
const int AUDIO_FIRE = 2;
const int AUDIO_COIN = 3;
const int AUDIO_FINISH_STAGE = 4;
const int AUDIO_LOST = 5;
const int AUDIO_BUMP = 6;
const int AUDIO_PAUSE = 7;
const int AUDIO_DEATH = 8;
const int AUDIO_BACKGROUND = 9;
const int AUDIO_SUPER =10;
const int AUDIO_WON = 11;

// ------------ General Consts --------------
const int NONE = -1;
