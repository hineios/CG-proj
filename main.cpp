#include <iostream>
#include "MyApp.h"

using namespace game;
using namespace std;

namespace game {
	class Map;
	class MyApp;
}


void main(int argc, char** argv) {

	cout << "Loading... \n\n";

	MyApp *app = new MyApp(argc,argv);
	delete[] app;

}

