static int finishScreen;

Vector3 position;
Image imMap;
Color* mapPixels;
Model modelMap;

Model model1;
Model model2;
Model model3;

void InitGameplayScreen(void) {
    finishScreen = 0;

    camera.position = Vector3One();
    camera.target = Vector3Zero();
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;

    matProjection = MatrixPerspective(camera.fovy * DEG2RAD, (double)screenWidth / (double)screenHeight, 0.01, 1000.0);
    matModelview = MatrixLookAt(camera.position, camera.target, camera.up);

    // Load models of props
    Mesh meshObj1 = LoadOBJ("resources/rock.obj");
    UploadMeshData(&meshObj1);
    Image img1 = LoadImage("resources/rock.png");
    Texture2D texObj1 = LoadTexture(img1.data, img1.width, img1.height, img1.format);
    UnloadImage(img1);
    model1 = LoadModel(meshObj1, texObj1);

    Mesh meshObj2 = LoadOBJ("resources/tower.obj");
    UploadMeshData(&meshObj2);
    Image img2 = LoadImage("resources/tower.png");
    Texture2D texObj2 = LoadTexture(img2.data, img2.width, img2.height, img2.format);
    UnloadImage(img2);
    model2 = LoadModel(meshObj2, texObj2);

    Mesh meshObj3 = LoadOBJ("resources/chest.obj");
    UploadMeshData(&meshObj3);
    Image img3 = LoadImage("resources/chest.png");
    Texture2D texObj3 = LoadTexture(img3.data, img3.width, img3.height, img3.format);
    UnloadImage(img3);
    model3 = LoadModel(meshObj3, texObj3);

    // Load full atlas image and map
    Image imMapAtlas = LoadImage("resources/cubemap_atlas_full.png");
    Texture2D texMapAtlas = LoadTexture(imMapAtlas.data, imMapAtlas.width, imMapAtlas.height, imMapAtlas.format);
    UnloadImage(imMapAtlas);

    if (mapNumber == 0) {
        imMap = LoadImage("resources/map01_custom.png");
    }
    else if (mapNumber == 1) {
        imMap = LoadImage("resources/map02_custom.png");
    }
    else if (mapNumber == 2) {
        imMap = LoadImage("resources/map03_custom.png");
    }
    
    modelMap = GenMeshCubicmap(imMap, texMapAtlas, 1.0f);
    mapPixels = GetImageData(imMap);
    UnloadImage(imMap);

    position = Vector3Zero();   // Model position on screen
}

void UpdateGameplayScreen(void) {
    Vector3 oldCamPos = camera.position;

    // LESSON 06: Camera update and modelview matrix update
    UpdateCamera(&camera);
    matModelview = MatrixLookAt(camera.position, camera.target, camera.up);

    // LESSON 07: Collisions detection and resolution
    // Check player collision (we simplify to 2D collision detection)
    Vector2 playerPos = { camera.position.x, camera.position.z };
    float playerRadius = 0.1f;  // Collision radius (player is modelled as a cilinder for collision)

    int playerCellX = (int)(playerPos.x - position.x + 0.5f);
    int playerCellY = (int)(playerPos.y - position.z + 0.5f);

    // Out-of-limits security check
    if (playerCellX < 0) playerCellX = 0;
    else if (playerCellX >= imMap.width) playerCellX = imMap.width - 1;

    if (playerCellY < 0) playerCellY = 0;
    else if (playerCellY >= imMap.height) playerCellY = imMap.height - 1;

    //Check player complete maze, is outside map
    if (playerPos.x < 0 || playerPos.x > (float)imMap.width || playerPos.y < 0 || playerPos.y > (float)imMap.height) {
        if (mapNumber >= 2) {
            finishScreen = 1;
            return;
        }
        else {
            mapNumber++;
            finishScreen = 2;
            return;
        }
    }

    // Check map collisions using image data and player position
    for (int y = 0; y < imMap.height; y++)
    {
        for (int x = 0; x < imMap.width; x++)
        {
            if ((mapPixels[y * imMap.width + x].r == 255 || mapPixels[y * imMap.width + x].r == 128) &&
                (CheckCollisionCircleRec(playerPos, playerRadius,(Rectangle) {(int)(position.x + 0.5f + x * 1.0f), (int)(position.y + 0.5f + y * 1.0f), 1, 1})))
            {
                // Collision detected, reset camera position
                camera.position = oldCamPos;
            }
        }
    }
}

void DrawGameplayScreen(void) {
    // LESSON 04: Draw loaded 3d models
    DrawModel(modelMap, position, 1.0f, (Color) { 255, 255, 255, 255 });
    for (int y = 0; y < imMap.height; y++)
    {
        for (int x = 0; x < imMap.width; x++)
        {
            if (mapPixels[y * imMap.width + x].g == 0) { }
            else if (mapPixels[y * imMap.width + x].g == 1) DrawModel(model1, (Vector3) { x, 0, y }, 0.1f, (Color) { 255, 255, 255, 255 });
            else if (mapPixels[y * imMap.width + x].g == 2) DrawModel(model2, (Vector3) { x, 0, y }, 0.1f, (Color) { 255, 255, 255, 255 });
            else if (mapPixels[y * imMap.width + x].g == 3) DrawModel(model3, (Vector3) { x, 0, y }, 0.1f, (Color) { 255, 255, 255, 255 });
        }
    }
}

void UnloadGameplayScreen(void) {
    UnloadModel(modelMap);
    UnloadModel(model1);
    UnloadModel(model2);
    UnloadModel(model3);
}

int FinishGameplayScreen(void) {
    return finishScreen;
}