typedef enum GameScreen { LOGO = 0, TITLE, LOADING, GAMEPLAY, ENDING } GameScreen;

int screenWidth = 800;
int screenHeight = 450;

Camera camera;
float mapNumber;

extern GameScreen currentScreen;

//------------------------------------------------------------------------------------
// Module Functions Declarations
//------------------------------------------------------------------------------------
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);

void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);

void InitLoadingScreen(void);
void UpdateLoadingScreen(void);
void DrawLoadingScreen(void);
void UnloadLoadingScreen(void);
int FinishLoadingScreen(void);

void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void UnloadGameplayScreen(void);
int FinishGameplayScreen(void);

void InitEndingScreen(void);
void UpdateEndingScreen(void);
void DrawEndingScreen(void);
void UnloadEndingScreen(void);
int FinishEndingScreen(void);