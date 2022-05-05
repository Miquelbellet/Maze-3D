static int finishScreen;
static int selectedExitOption = 0;
static int maxExitOptions = 0;

Texture2D texture_exit_option1;
Model modelExitOption1;

Texture2D texture_exit_option2;
Model modelExitOption2;

Texture2D texture_exit_option3;
Model modelExitOption3;

void InitEndingScreen(void) {
    finishScreen = 0;
    mapNumber = 0;
    selectedExitOption = 1;
    maxExitOptions = 3;

    camera.position = Vector3One();
    camera.target = Vector3Zero();
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;

    matProjection = MatrixPerspective(camera.fovy * DEG2RAD, (double)screenWidth / (double)screenHeight, 0.01, 1000.0);
    matModelview = MatrixLookAt(camera.position, camera.target, camera.up);

    Mesh meshRect1 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect1);

    Image exit_option1_image = LoadImage("resources/exit_option1.png");
    texture_exit_option1 = LoadTexture(exit_option1_image.data, exit_option1_image.width, exit_option1_image.height, exit_option1_image.format);
    UnloadImage(exit_option1_image);
    modelExitOption1 = LoadModel(meshRect1, texture_exit_option1);

    Mesh meshRect2 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect2);

    Image exit_option2_image = LoadImage("resources/exit_option2.png");
    texture_exit_option2 = LoadTexture(exit_option2_image.data, exit_option2_image.width, exit_option2_image.height, exit_option2_image.format);
    UnloadImage(exit_option2_image);
    modelExitOption2 = LoadModel(meshRect2, texture_exit_option2);

    Mesh meshRect3 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect3);

    Image exit_option3_image = LoadImage("resources/exit_option3.png");
    texture_exit_option3 = LoadTexture(exit_option3_image.data, exit_option3_image.width, exit_option3_image.height, exit_option3_image.format);
    UnloadImage(exit_option3_image);
    modelExitOption3 = LoadModel(meshRect3, texture_exit_option3);
}

void UpdateEndingScreen(void) {
    if (IsKeyPressed(GLFW_KEY_ENTER)) {
        finishScreen = selectedExitOption;
    }
    if (IsKeyPressed(GLFW_KEY_DOWN)) {
        selectedExitOption++;
        if (selectedExitOption > maxExitOptions) selectedExitOption = 1;
    }
    else if (IsKeyPressed(GLFW_KEY_UP)) {
        selectedExitOption--;
        if (selectedExitOption == 0) selectedExitOption = maxExitOptions;
    }
}

void DrawEndingScreen(void) {
    switch (selectedExitOption) {
        case 1: {
            DrawModel(modelExitOption1, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 2: {
            DrawModel(modelExitOption2, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 3: {
            DrawModel(modelExitOption3, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        default: break;
    }
}

void UnloadEndingScreen(void) {
    UnloadModel(modelExitOption1);
    UnloadModel(modelExitOption2);
    UnloadModel(modelExitOption3);
}

int FinishEndingScreen(void) {
    return finishScreen;
}