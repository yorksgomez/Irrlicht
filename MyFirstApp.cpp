/*input
a
*/
//g++ -Iirr/include -I/usr/X11R6/include  -O3 -ffast-math MyFirstApp.cpp -o ./MyFirstApp -Lirr/lib/Linux -lIrrlicht -L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor


#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

struct SAppContext {
  IrrlichtDevice* device;
  s32 counter;
  IGUIListBox* listbox;
};

enum {
  GUI_ID_QUIT_BUTTON = 101,
  GUI_ID_NEW_WINDOW_BUTTON,
  GUI_ID_FILE_OPEN_BUTTON,
  GUI_ID_TRANSPARENCY_SCROLL_BAR

};

void setSkinTransparency(s32 alpha, IGUISkin* skin) {

  for(s32 i = 0; i < EGDC_COUNT; ++i) {
    SColor col = skin->getColor((EGUI_DEFAULT_COLOR) i);
    col.setAlpha(alpha);
    skin->setColor((EGUI_DEFAULT_COLOR)i, col);
  }

}

class MyEventReceiver : public IEventReceiver {
private:
  SAppContext& Context;

public:
  MyEventReceiver(SAppContext& context) : Context(context) {}

  virtual bool OnEvent(const SEvent& event) {

    if(event.EventType == EET_GUI_EVENT) {
      s32 id = event.GUIEvent.Caller->getID();
      IGUIEnvironment* env = Context.device->getGUIEnvironment();

      switch(event.GUIEvent.EventType) {
      case EGET_ID_TRANSPARENCY_SCROLL_BAR:

	if(id == GUI_ID_TRANSPARENCY_SCROLL_BAR) {
	  s32 pos = ((IGUIScrollBar*)event.GUIEventCaller)->getPos();
	  setSkinTransparency(pos, env->getSkin());
	}
	
	break;
      case EGET_BUTTON_CLICKED:

	switch(id) {
	case GUI_ID_QUIT_BUTTON:
	  Context.device->closeDevice();
	  return true;
	case GUI_ID_NEW_WINDOW_BUTTON:
	  Context.listbox->addItem(L"Window created");
	  Context.counter += 30;
	  if(Context.counter > 200)
	    Context.counter = 0;

	  IGUIWindow* window = env->addWindow(rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter), false, L"Test Window");
	  env->addStaticText(L"Please close me", rect<s32>(35, 35, 140, 50), true, false, window);
	  
	  return true;
	case GUI_ID_FILE_OPEN_BUTTON:
	  Context.listbox->addItem(L"File open");

	  env->addFileOpenDialog(L"Please, choose a file", true, 0, -1, true);
	  return true;
	default:
	  return true;
	}
	
	break;
      }

    case EGET_FILE_SELECTED:
      {
	IGUIFileOpenDialog* dialog = (IGUIFileOpenDialog*) event.GUIEvent.Caller;
	Content.listbox->addItem(dialog->getFileName());
      }
      break;
    default:
      break;
    }

    return false;
  }

};

int main() {
  return 0;
}
