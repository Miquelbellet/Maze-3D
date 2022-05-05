static int finishScreen;
static int framesLoadingCounter = 0;
static int framesCount = 0;

Model modelLoading0;
Model modelLoading1;
Model modelLoading2;
Model modelLoading3;
Model modelLoading4;
Model modelLoading5;
Model modelLoading6;
Model modelLoading7;
Model modelLoading8;
Model modelLoading9;
Model modelLoading10;
Model modelLoading11;

void InitLoadingScreen(void) {
    finishScreen = 0;

    camera.position = Vector3One();
    camera.target = Vector3Zero();
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;

    matProjection = MatrixPerspective(camera.fovy * DEG2RAD, (double)screenWidth / (double)screenHeight, 0.01, 1000.0);
    matModelview = MatrixLookAt(camera.position, camera.target, camera.up);

    Mesh meshRect0 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect0);
    Image logo_image0 = LoadImage("resources/loading_frames/frame_0.png");
    Texture2D texture_image0 = LoadTexture(logo_image0.data, logo_image0.width, logo_image0.height, logo_image0.format);
    UnloadImage(logo_image0);
    modelLoading0 = LoadModel(meshRect0, texture_image0);

    Mesh meshRect1 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect1);
    Image logo_image1 = LoadImage("resources/loading_frames/frame_1.png");
    Texture2D texture_image1 = LoadTexture(logo_image1.data, logo_image1.width, logo_image1.height, logo_image1.format);
    UnloadImage(logo_image1);
    modelLoading1 = LoadModel(meshRect1, texture_image1);

    Mesh meshRect2 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect2);
    Image logo_image2 = LoadImage("resources/loading_frames/frame_2.png");
    Texture2D texture_image2 = LoadTexture(logo_image2.data, logo_image2.width, logo_image2.height, logo_image2.format);
    UnloadImage(logo_image2);
    modelLoading2 = LoadModel(meshRect2, texture_image2);

    Mesh meshRect3 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect3);
    Image logo_image3 = LoadImage("resources/loading_frames/frame_3.png");
    Texture2D texture_image3 = LoadTexture(logo_image3.data, logo_image3.width, logo_image3.height, logo_image3.format);
    UnloadImage(logo_image3);
    modelLoading3 = LoadModel(meshRect3, texture_image3);

    Mesh meshRect4 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect4);
    Image logo_image4 = LoadImage("resources/loading_frames/frame_4.png");
    Texture2D texture_image4 = LoadTexture(logo_image4.data, logo_image4.width, logo_image4.height, logo_image4.format);
    UnloadImage(logo_image4);
    modelLoading4 = LoadModel(meshRect4, texture_image4);

    Mesh meshRect5 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect5);
    Image logo_image5 = LoadImage("resources/loading_frames/frame_5.png");
    Texture2D texture_image5 = LoadTexture(logo_image5.data, logo_image5.width, logo_image5.height, logo_image5.format);
    UnloadImage(logo_image5);
    modelLoading5 = LoadModel(meshRect5, texture_image5);

    Mesh meshRect6 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect6);
    Image logo_image6 = LoadImage("resources/loading_frames/frame_6.png");
    Texture2D texture_image6 = LoadTexture(logo_image6.data, logo_image6.width, logo_image6.height, logo_image6.format);
    UnloadImage(logo_image6);
    modelLoading6 = LoadModel(meshRect6, texture_image6);

    Mesh meshRect7 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect7);
    Image logo_image7 = LoadImage("resources/loading_frames/frame_7.png");
    Texture2D texture_image7 = LoadTexture(logo_image7.data, logo_image7.width, logo_image7.height, logo_image7.format);
    UnloadImage(logo_image7);
    modelLoading7 = LoadModel(meshRect7, texture_image7);

    Mesh meshRect8 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect8);
    Image logo_image8 = LoadImage("resources/loading_frames/frame_8.png");
    Texture2D texture_image8 = LoadTexture(logo_image8.data, logo_image8.width, logo_image8.height, logo_image8.format);
    UnloadImage(logo_image8);
    modelLoading8 = LoadModel(meshRect8, texture_image8);

    Mesh meshRect9 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect9);
    Image logo_image9 = LoadImage("resources/loading_frames/frame_9.png");
    Texture2D texture_image9 = LoadTexture(logo_image9.data, logo_image9.width, logo_image9.height, logo_image9.format);
    UnloadImage(logo_image9);
    modelLoading9 = LoadModel(meshRect9, texture_image9);

    Mesh meshRect10 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect10);
    Image logo_image10 = LoadImage("resources/loading_frames/frame_10.png");
    Texture2D texture_image10 = LoadTexture(logo_image10.data, logo_image10.width, logo_image10.height, logo_image10.format);
    UnloadImage(logo_image10);
    modelLoading10 = LoadModel(meshRect10, texture_image10);

    Mesh meshRect11 = LoadOBJ("resources/rectangle.obj");
    UploadMeshData(&meshRect11);
    Image logo_image11 = LoadImage("resources/loading_frames/frame_11.png");
    Texture2D texture_image11 = LoadTexture(logo_image11.data, logo_image11.width, logo_image11.height, logo_image11.format);
    UnloadImage(logo_image11);
    modelLoading11 = LoadModel(meshRect11, texture_image11);
}

void UpdateLoadingScreen(void) {
    framesLoadingCounter++;
    if (framesLoadingCounter > 180) {
        finishScreen = 1;
    }
    
    framesCount++;
    if (framesCount == 12) framesCount = 0;
}

void DrawLoadingScreen(void) {
    switch (framesCount) {
        case 0: {
            DrawModel(modelLoading0, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 1: {
            DrawModel(modelLoading1, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 2: {
            DrawModel(modelLoading2, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 3: {
            DrawModel(modelLoading3, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 4: {
            DrawModel(modelLoading4, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 5: {
            DrawModel(modelLoading5, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 6: {
            DrawModel(modelLoading6, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 7: {
            DrawModel(modelLoading7, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 8: {
            DrawModel(modelLoading8, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 9: {
            DrawModel(modelLoading9, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 10: {
            DrawModel(modelLoading10, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        case 11: {
            DrawModel(modelLoading11, (Vector3) { 0.0f, 0.0f, 0.0f }, 0.8f, (Color) { 255, 255, 255, 255 });
        } break;
        default: break;
    }
}

void UnloadLoadingScreen(void) {
    UnloadModel(modelLoading0);
    UnloadModel(modelLoading1);
    UnloadModel(modelLoading2);
    UnloadModel(modelLoading3);
    UnloadModel(modelLoading4);
    UnloadModel(modelLoading5);
    UnloadModel(modelLoading6);
    UnloadModel(modelLoading7);
    UnloadModel(modelLoading8);
    UnloadModel(modelLoading9);
    UnloadModel(modelLoading10);
    UnloadModel(modelLoading11);
}

int FinishLoadingScreen(void) {
    return finishScreen;
}