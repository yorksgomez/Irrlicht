/*input
a
*/
//g++ -Iirr/include -I/usr/X11R6/include  -O3 -ffast-math MyFirstApp.cpp -o ./MyFirstApp -Lirr/lib/Linux -lIrrlicht -L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor

#include <irrlicht.h>
#include <driverChoice.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

#include "mainwindow.h"
#include "events.h"
#include <string>

using namespace std;

using namespace base;

int main() {
	Context c;
	Events receiver(&c);

	IrrlichtDevice* device;
	MainWindow main(device, L"Wyxes", core::dimension2d<u32>(MainWindow::width, MainWindow::height), &receiver);
	c.mainwindow = &main;
	main.setBackground(video::SColor(235, 235, 235, 220));
	main.start();
	return 0;
}