/*input
a
*/
//g++ -Iirr/include -I/usr/X11R6/include  -O3 -ffast-math MyFirstApp.cpp -o ./MyFirstApp -Lirr/lib/Linux -lIrrlicht -L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor

#include <irrlicht.h>
#include <driverChoice.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;

#include "mainwindow.h"

int main() {
	IrrlichtDevice* device;
	MainWindow main(device, L"Mi primera ventana (bueno no)", core::dimension2d<u32>(480, 700));
	main.start();


	return 0;
}