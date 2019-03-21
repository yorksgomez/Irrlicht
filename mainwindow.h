#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <irrlicht.h>
#include <driverChoice.h>
#include <iostream>
#include <stdio.h>

#include "base.h"

namespace base {

class MainWindow {
public:
	IrrlichtDevice* Device;
	gui::IGUIEnvironment* env;
	video::SColor Background;

	Grid<gui::IGUIButton*> grid;

	gui::IGUIEditBox* calc;
	static const int BUTTONS_LEN = 4;

	void init() {
		const wchar_t* button_text[4][4] = {
			{L"1", L"2", L"3", L"+"},
			{L"4", L"5", L"6", L"-"},
			{L"7", L"8", L"9", L"*"},
			{L"0", L".", L"=", L"/"}
		};

		int space = 10;
		calc = env->addEditBox(L"0", core::recti(0, 0, width, 50));
		calc->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_CENTER);

		int button_w = grid.getWidth() / grid.getCols(),
			button_h = grid.getHeight() / grid.getRows();

		for(int i = 0; i < BUTTONS_LEN; i++) 

			for(int j = 0; j < BUTTONS_LEN; j++)
				grid.add(env->addButton(
					core::recti(button_w*j, button_h*i + 50, button_w*j + button_w, button_h*i + button_h + 50), 
					0, BUTTONS_LEN*i + j + BUTTON_1, button_text[i][j]));

	}
	
public:
	static const int width = 250, height = 300;

	MainWindow(IrrlichtDevice*& device, const wchar_t* title, 
			   core::dimension2d<u32> bounds, IEventReceiver* receiver) :
			   Background(video::SColor(255, 255, 255, 250)),
			   grid(BUTTONS_LEN, BUTTONS_LEN, width, height - 50) {

		video::E_DRIVER_TYPE driverType = driverChoiceConsole();

		if(driverType == video::EDT_COUNT){
			std::cout << "Error getting driver";
			return;
		}

		device = createDevice(driverType, bounds, 16, false, false, false, receiver);
		if(!device){
			std::cout << "Error creating device";
			return;
		}

		device->setWindowCaption(title);

		Device = device;
		env = Device->getGUIEnvironment();
		env->getSkin()->setFont(env->getFont("media/calcsans.xml"));

		init();
	}

	void setBackground(video::SColor bg) {
		Background = bg;
	}

	void start() {
		video::IVideoDriver* driver = Device->getVideoDriver();

		while(Device->run()) {
			
			if(Device->isWindowActive()) {
				driver->beginScene(true, true, Background);
				env->drawAll();
				driver->endScene();
			} else {
				Device->yield();
			}

		}

		Device->drop();
	}

	gui::IGUIEditBox*& getCalc() {
		return calc;
	}

};

struct Context {
	MainWindow* mainwindow;
};

}

#endif