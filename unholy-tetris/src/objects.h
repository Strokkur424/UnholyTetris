#pragma once

typedef unsigned int* SingleBlock;

typedef struct
{
	// Position on grid from top-left
	char x = 0;
	char y = 0;

	SingleBlock* blocks[9] = {};

	char width = 3;
	char height = 3;

} BlockGroup;

typedef struct
{
	BlockGroup* nextGroup = 0;
	SingleBlock* placedBlocks[400] = {};

	char width = 10;
	char height = 40;

} PlaySceneInformation;

// The current game state information
typedef enum
{
	GAME_START,
	GAME_PLAYING,
	GAME_STOP,
	GAME_LOSING,
	GAME_OVER

} Gamestate;