static int finishScreen;
static int framesCounter = 0;
static float alpha = 0.0f;
static bool fade_in = false;

Model modelLogo;

void InitLogoScreen(void) {
    finishScreen = 0;
    framesCounter = 0;
    alpha = 1.0f;
    fade_in = true;

    camera.position = Vector3One();
    camera.target = Vector3Zero();
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;

    matProjection = MatrixPerspective(camera.fovy * DEG2RAD, (double)screenWidth / (double)screenHeight, 0.01, 1000.0);
    matModelview = MatrixLookAt(camera.position, camera.target, camera.up);

    Mesh meshRect = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect);

    Image logo_image = LoadImage("resources/logo_uoc.png");
    Texture2D texture_image = LoadTexture(logo_image.data, logo_image.width, logo_image.height, logo_image.format);
    UnloadImage(logo_image);

    modelLogo = LoadModel(meshRect, texture_image);
}

void UpdateLogoScreen(void) {
    framesCounter++;
    if (fade_in && alpha > 0.0f) {
        alpha -= 0.02f;
        if (alpha < 0.0f) {
            fade_in = false;
            framesCounter = 0;
            alpha = 0.0f;
        }
    }
    else if (!fade_in && framesCounter > 120) {
        alpha += 0.02f;
        if (alpha >= 1.0f) {
            alpha = 1.0f;
            finishScreen = 1;
        }
    }
}

void DrawLogoScreen(void) {
    DrawModel(modelLogo, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 - (alpha * 255) });
}

void UnloadLogoScreen(void) {
    UnloadModel(modelLogo);
}

int FinishLogoScreen(void) {
    return finishScreen;
}