#ifndef WINDOW_H
#define WINDOW_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>

using namespace std;


class MainWindow {
public:
	MainWindow(IrrlichtDevice*& device, const wchar_t* title, 
			   core::dimension2d<u32> bounds, IEventReceiver* receiver = 0) :
			   Background(video::SColor(245, 245, 245, 200)) {
		Device = device;

		video::E_DRIVER_TYPE driverType = driverChoiceConsole();

		if(driverType == video::EDT_COUNT)
			cout << "Error getting driver";

		Device = createDevice(driverType, bounds, 16, false, false, false, receiver);
		if(!Device)
			cout << "Error creating device";

		Device->setResizable(true);
		Device->setWindowCaption(title);
	}

	void setBackground(video::SColor bg) {
		Background = bg;
	}

	void start() {
		video::IVideoDriver* driver = Device->getVideoDriver();

		while(Device->run()) {
			driver->beginScene(true, true, Background);
			driver->endScene();
		}

		Device->drop();
	}

private:
	IrrlichtDevice* Device;
	video::SColor Background;
};

#endif