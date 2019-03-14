/*input
a
*/

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

using namespace video;
using namespace scene;
using namespace core;

#ifdef _MSC_VER
	#pragma comment(lib, "irrlicht.lib")
#endif

class MyEventReceiver : public IEventReceiver
{
	public:
		virtual bool OnEvent(const SEvent& event) {

			if(event.EventType == irr::EET_KEY_INPUT_EVENT)
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

			return false;
		}

		virtual bool IsKeyDown(EKEY_CODE keyCode) const {
			return KeyIsDown[keyCode];
		}

		MyEventReceiver() {

			for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
				KeyIsDown[i] = false;

		}

	private:
		bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main() {
	E_DRIVER_TYPE driverType = driverChoiceConsole();
	if(driverType == EDT_COUNT)
		return 1;

	MyEventReceiver receiver;

	IrrlichtDevice* device = createDevice(driverType, dimension2d<u32>(600, 480), 16, false, false, false, &receiver);
	if(!device)
		return 2;

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	ISceneNode* node = smgr->addSphereSceneNode();
	if(node) {
		node->setPosition(vector3df(0, 0, 30));
		node->setMaterialTexture(0, driver->getTexture("media/wall.bmp"));
		node->setMaterialFlag(EMF_LIGHTING, false);
	}

	ISceneNode* n = smgr->addCubeSceneNode();
	if(n) {
		n->setMaterialTexture(0, driver->getTexture("media/t351sml.jpg"));
		n->setMaterialFlag(EMF_LIGHTING, false);
		ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(vector3df(0, 0, 30), 20.0f);

		if(anim) {
			n->addAnimator(anim);
			anim->drop();
		}

	}

	while(device->run()) {
		driver->beginScene(true, true, SColor(255, 113, 113, 133));
		smgr->drawAll();
		driver->endScene();
	}

	return 0;
}