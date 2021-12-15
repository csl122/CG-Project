/**
* Entry file to framework. Should not edit this file, though to change window size, adjust parameters in creastion of new scene
* <p>
* {@code new MyScene(argc, argv, "title", (const int)width, (const int)height)}
* @author wil
* @date 09/02/16
*/
#include "MyScene.h"

//#include <irrKlang.h>
//#include <conio.h>
//using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
/**
 * Entry method, takes command line arguments and creates new Scene engine to render your G53GRA Coursework
 *
 * @see MyScene
 */
int main(int argc, char* argv[])
{
	//// Create new instance of MyScene - the OpenGL context on which your coursework is built
	//MyScene* scene = NULL;
	//scene = new MyScene(argc, argv, "G53GRA", static_cast<const int>(1200), static_cast<const int>(675));

	//// Begin the main GL loop
	//scene->Run();

	//// On exit, clean up and return success (0x0)
	//delete scene;
	//return 0;


	// start the sound engine with default parameters
	//ISoundEngine* engine = createIrrKlangDevice();

	//if (!engine)
	//{
	//	printf("Could not startup engine\n");
	//	return 0; // error starting up the engine
	//}

	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.

	// play some sound stream, looped
	
	

	// In a loop, wait until user presses 'q' to exit or another key to
	// play another sound.

	printf("\nBGM playing!\n");

	//do
	//{
	//	printf("Press any key to play some sound, press 'q' to quit.\n");

	//	// play a single sound
	//	engine->play2D("./Media/bell.wav");
	//} while (_getch() != 'q');

	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().

	// Create new instance of MyScene - the OpenGL context on which your coursework is built
	MyScene* scene = NULL;
	scene = new MyScene(argc, argv, "G53GRA", static_cast<const int>(1200), static_cast<const int>(675));

	ISoundEngine* musicEngine = scene->GetMusicEngine();
	musicEngine->play2D("./Media/back1.wav", true);

	// Begin the main GL loop
	scene->Run();


	// On exit, clean up and return success (0x0)
	delete scene;

	// delete engine
	musicEngine->drop();

	return 0;

}
