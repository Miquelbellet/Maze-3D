static int finishScreen;

static int selectedTitleOption = 0;
static int maxTitleOptions = 0;

Texture2D texture_option1;
Model modelOption1;
Texture2D texture_option2;
Model modelOption2;

void InitTitleScreen(void) {
    finishScreen = 0;
    mapNumber = 0;

    selectedTitleOption = 1;
    maxTitleOptions = 2;

    camera.position = Vector3One();
    camera.target = Vector3Zero();
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;

    matProjection = MatrixPerspective(camera.fovy * DEG2RAD, (double)screenWidth / (double)screenHeight, 0.01, 1000.0);
    matModelview = MatrixLookAt(camera.position, camera.target, camera.up);

    Mesh meshRect1 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect1);

    Image option1_image = LoadImage("resources/option1.png");
    texture_option1 = LoadTexture(option1_image.data, option1_image.width, option1_image.height, option1_image.format);
    UnloadImage(option1_image);
    modelOption1 = LoadModel(meshRect1, texture_option1);

    Mesh meshRect2 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect2);

    Image option2_image = LoadImage("resources/option2.png");
    texture_option2 = LoadTexture(option2_image.data, option2_image.width, option2_image.height, option2_image.format);
    UnloadImage(option2_image);
    modelOption2 = LoadModel(meshRect2, texture_option2);
}

void UpdateTitleScreen(void) {
    if (IsKeyPressed(GLFW_KEY_ENTER)) {
        finishScreen = selectedTitleOption;
    }
    if (IsKeyPressed(GLFW_KEY_DOWN)) {
        selectedTitleOption++;
        if (selectedTitleOption > maxTitleOptions) selectedTitleOption = 1;
    }
    else if (IsKeyPressed(GLFW_KEY_UP)) {
        selectedTitleOption--;
        if (selectedTitleOption == 0) selectedTitleOption = maxTitleOptions;
    }
}

void DrawTitleScreen(void) {
    switch (selectedTitleOption){
        case 1: {
            DrawModel(modelOption1, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 2: {
            DrawModel(modelOption2, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        default: break;
    }
}

void UnloadTitleScreen(void) {
    UnloadModel(modelOption1);
    UnloadModel(modelOption2);
}

int FinishTitleScreen(void) {
    return finishScreen;
}