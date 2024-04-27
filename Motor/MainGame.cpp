#include "MainGame.h"

Sprite Sprites[4];
void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("GAAA", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,width,height, SDL_WINDOW_OPENGL);
	//ES VALIDAR SI HUBO ERROR
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();
}
void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShadersVert.txt",
		"Shaders/colorShadersFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.linkShader();
}
void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.0002;
	for (int i = 0; i < 4; i++) {
		if(i < time)
			Sprites[i].draw();
	}
	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << "Posicion en X " << event.motion.x
				<< "Posicion Y " << event.motion.y << endl;
			break;
		}
	}
}

MainGame::MainGame()
{
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	Sprite sp1,sp2, sp3, sp4;
	init();
	sp1.init(0, 0, 1, 1);
	sp2.init(-1, -1, 1, 1);
	sp3.init(-1, 0, 1, 1);
	sp4.init(0, -1, 1, 1);
	Sprites[0] = sp1;
	Sprites[1] = sp2;
	Sprites[2] = sp3;
	Sprites[3] = sp4;
	update();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}
