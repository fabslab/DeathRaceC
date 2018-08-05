#pragma once

const int VIRTUAL_WIDTH = 480;
const int VIRTUAL_HEIGHT = 360;

const int SCOREBOARD_HEIGHT = 30;
const int SIDEWALK_WIDTH = 32;
const int BORDER_WIDTH = 2;

const Rectangle GAME_BOUNDS = { 0, static_cast<float>(SCOREBOARD_HEIGHT), VIRTUAL_WIDTH, static_cast<float>(VIRTUAL_HEIGHT - SCOREBOARD_HEIGHT) };
