#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

const char TITLE[] = "Tetris";
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 720;

const int WIDTH = 10;
const int HEIGHT = 22;
const int VISIBLE_HEIGHT = 20;
const int GRID_SIZE = 30;

const int MARGIN_X = 0;
const int MARGIN_Y = SCREEN_HEIGHT - HEIGHT * GRID_SIZE;

const int SOUND_FREQUENCY = 44100;
const int CHANNELS = 2;
const int CHUNKSIZE = 2048;

const char BGMUSIC[] = "sound/Korobeiniki.mp3";
const char CLEAR_SOUND[] = "sound/clear.wav";
const char FALL_SOUND[] = "sound/fall.wav";
const char GAMEOVER_SOUND[] = "sound/gameover.wav";
const char LINE_SOUND[] = "sound/line.wav";
const char SELECTION_SOUND[] = "sound/selection.wav";
const char SUCCESS_SOUND[] = "sound/success.wav";

const char FONT[] = "font/soviet-bold-expanded.ttf";

#endif // GAME_CONSTANTS_H
