#define GLAD_IMPLEMENTATION
#include "glad.h"               // GLAD extensions loading library
// NOTE: Includes required OpenGL headers

#include <GLFW/glfw3.h>         // Windows/Context and inputs management

#define RAYMATH_STANDALONE
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"            // Vector3 and Matrix math functions

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"          // Multiple image fileformats loading functions

#include <stdarg.h>             // Required for TraceLog()
#include <stdio.h>

#include "src/GLFW_func.c"
#include "src/globals.c"
#include "src/screen_logo.c"
#include "src/screen_title.c"
#include "src/screen_loading.c"
#include "src/screen_gameplay.c"
#include "src/screen_ending.c"


GameScreen currentScreen = 0;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static int transToScreen = -1;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void TransitionToScreen(int screen);
static void UpdateTransition(void);
static void DrawTransition(void);

static void UpdateFrame(void);
static void DrawFrame(void);

//----------------------------------------------------------------------------------
// Main Entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    // LESSON 02: Window and graphic device initialization and management
    InitWindow(screenWidth, screenHeight);          // Initialize Window using GLFW3
    InitGraphicsDevice(screenWidth, screenHeight);  // Initialize graphic device (OpenGL)
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide and locks mouse pointer

    // LESSON 03: Init default Shader (customized for GL 3.3 and ES2)
    shdrDefault = LoadShaderDefault();

    // Define our camera
    camera.position = Vector3One();
    camera.target = Vector3Zero();
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;

    //matProjection = MatrixOrtho(0.0, screenWidth, screenHeight, 0.0, 0.0, 1.0);
    //matModelview = MatrixIdentity();
    matProjection = MatrixPerspective(camera.fovy * DEG2RAD, (double)screenWidth / (double)screenHeight, 0.01, 1000.0);
    matModelview = MatrixLookAt(camera.position, camera.target, camera.up);

    currentScreen = LOGO;
    InitLogoScreen();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------    

    // Main game loop     
    while (!glfwWindowShouldClose(window))
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateFrame();
        
        // Draw
        //----------------------------------------------------------------------------------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear used buffers: Color and Depth (Depth is used for 3D)
        DrawFrame();
        
        glfwSwapBuffers(window);            // Swap buffers: show back buffer into front
        PollInputEvents();                  // Register input events (keyboard, mouse)
        SyncFrame();                        // Wait required time to target framerate
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case LOADING: UnloadLoadingScreen(); break;
        case GAMEPLAY: UnloadGameplayScreen(); break;
        case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}


void UpdateFrame(void) {
    if (!onTransition)
    {
        switch (currentScreen)
        {
        case LOGO:
        {
            UpdateLogoScreen();

            if (FinishLogoScreen()) TransitionToScreen(TITLE);

        } break;
        case TITLE:
        {
            UpdateTitleScreen();

            if (FinishTitleScreen() == 1) TransitionToScreen(LOADING);
            else if (FinishTitleScreen() == 2) CloseWindow();

        } break;
        case LOADING:
        {
            UpdateLoadingScreen();

            if (FinishLoadingScreen()) TransitionToScreen(GAMEPLAY);

        } break;
        case GAMEPLAY:
        {
            UpdateGameplayScreen();

            if (FinishGameplayScreen() == 1) TransitionToScreen(ENDING);
            else if (FinishGameplayScreen() == 2) TransitionToScreen(LOADING);

        } break;
        case ENDING:
        {
            UpdateEndingScreen();

            if (FinishEndingScreen() == 1) TransitionToScreen(GAMEPLAY);
            else if (FinishEndingScreen() == 2) TransitionToScreen(TITLE);
            else if (FinishEndingScreen() == 3) CloseWindow();

        } break;
        default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
}

void DrawFrame(void) {
    switch (currentScreen)
    {
    case LOGO: DrawLogoScreen(); break;
    case TITLE: DrawTitleScreen(); break;
    case LOADING: DrawLoadingScreen(); break;
    case GAMEPLAY: DrawGameplayScreen(); break;
    case ENDING: DrawEndingScreen(); break;
    default: break;
    }

    // Draw full screen rectangle in front of everything
    if (onTransition) DrawTransition();
}

static void TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
            case LOGO: UnloadLogoScreen(); break;
            case TITLE: UnloadTitleScreen(); break;
            case LOADING: UnloadLoadingScreen(); break;
            case GAMEPLAY: UnloadGameplayScreen(); break;
            case ENDING: UnloadEndingScreen(); break;
            default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
            case LOGO: InitLogoScreen(); break;
            case TITLE: InitTitleScreen(); break;
            case LOADING: InitLoadingScreen(); break;
            case GAMEPLAY: InitGameplayScreen(); break;
            case ENDING: InitEndingScreen(); break;
            default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

static void DrawTransition(void)
{
    //DrawRectangle(0, 0, screenWidth, screenHeight, (Color) {0, 0, 0, transAlpha*255});
}