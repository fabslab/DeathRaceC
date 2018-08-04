#include "raylib.h"
#include "Constants.h"
#include "Scene.h"

Rectangle GetDestinationRectangle(float screenWidth, float screenHeight, float preferredAspectRatio);

int main(int argc, char* argv[])
{
	const float PREFERRED_ASPECT_RATIO = (float)VIRTUAL_WIDTH / VIRTUAL_HEIGHT;

	// TODO: Use device's resolution instead of hardcoded screen width/height
	int screenWidth = 480;
	int screenHeight = 360;

	InitWindow(screenWidth, screenHeight, "Death Race");
	SetWindowMinSize(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
	//ToggleFullscreen();

	SetTargetFPS(60);

	Rectangle virtualSizeRectangle = { 0, 0, VIRTUAL_WIDTH, -VIRTUAL_HEIGHT };
	Rectangle destinationRectangle = GetDestinationRectangle(screenWidth, screenHeight, PREFERRED_ASPECT_RATIO);
	RenderTexture2D virtualRenderTexture = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
	SetTextureFilter(virtualRenderTexture.texture, FILTER_POINT);
	Vector2 screenOrigin = { 0, 0 };
	Scene scene = Scene();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		BeginTextureMode(virtualRenderTexture);
		scene.Update();
		scene.Draw();
		DrawFPS(2, 2);
		EndTextureMode();

		DrawTexturePro(
			virtualRenderTexture.texture,
			virtualSizeRectangle,
			destinationRectangle,
			screenOrigin,
			0,
			WHITE
		);

		EndDrawing();
	}

	UnloadRenderTexture(virtualRenderTexture);

	// Close window and OpenGL context
	CloseWindow();

	return 0;
}

Rectangle GetDestinationRectangle(float screenWidth, float screenHeight, float preferredAspectRatio)
{
	float outputAspectRatio = screenWidth / screenHeight;
	Rectangle destinationRectangle;

	if (outputAspectRatio <= preferredAspectRatio)
	{
		// letterbox - bars on top and bottom
		float gameHeight = (int)(screenWidth / preferredAspectRatio + 0.5f);
		float barHeight = (screenHeight - gameHeight) / 2;
		destinationRectangle = { 0, barHeight, screenWidth, gameHeight };
	}
	else
	{
		// pillarbox - bars on left and right
		float gameWidth = (int)(screenHeight * preferredAspectRatio + 0.5f);
		float barWidth = (screenWidth - gameWidth) / 2;
		destinationRectangle = { barWidth, 0, gameWidth, screenHeight };
	}

	return destinationRectangle;
}
