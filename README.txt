PEC3 - Maze 3D Game

- Screen Management:
For this PEC3 I implemented a game screen manager system to keep the screen code organized and in different files.
I added a LOGO screen to see a logo of the company or the game.
A TITLE screen where the user can select to play the game or to exit the game.
A LOADING screen to load the gameplay screen that lasts 3 seconds. This screen is also shown when the player completes a maze level and have to change to the next one.
A GAMEPLAY screen where the game logic and textures are implemented. I added 3 maze maps levels that are loaded depending on what level you complete. When you complete all 3 levels you complete the game.
And an ENDING screen, where a congratulation text is shown and you have 3 options. You can play again, you can go to the title screen or you can leave the game.

- Modification of GenMeshCubicmap() and map loading:
I have changed this function to load customable maps, textures and props with a single image.
In the .r color component of the image, you can decide if the player can go trowh this path or not.
In the .g color component, you can choose between 3 props to put in the maze level or to put none.
In the .b color component, you can choose the type of texture that will have.

- Maze levels:
I have created 3 different maze levels with the different types of textures and props.
This levels have a scalable difficulty where the last one is the most difficult.

I hope you enjoy this maze game.
Thanks!

Miquel Bellet