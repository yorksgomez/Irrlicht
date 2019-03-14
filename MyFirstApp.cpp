/*input
a
*/
//g++ -Iirr/include -I/usr/X11R6/include  -O3 -ffast-math MyFirstApp.cpp -o ./MyFirstApp -Lirr/lib/Linux -lIrrlicht -L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor


#include <irrlicht.h>
#include "driverChoice.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma commet(lib, "Irrlicht.lib")
#endif

using namespace irr;

class MyEventReceiver : public IEventReceiver {
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];

public:
  MyEventReceiver() {

    for(u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
    
  }
  
  virtual bool OnEvent(const SEvent& event) {

    if(event.EventType == EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
  }

   virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
  
};

int main() {
  video::E_DRIVER_TYPE driverType = driverChoiceConsole();
  if(driverType == video::EDT_COUNT)
    return 1;

  MyEventReceiver receiver;

  IrrlichtDevice* device = createDevice(driverType, core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
  if(!device)
    return 2;

  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  scene::ISceneNode* node = smgr->addSphereSceneNode();
  if(node) {
    node->setPosition(core::vector3df(0, 0, 30));
    node->setMaterialTexture(0, driver->getTexture("media/wall.bmp"));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
  }

  scene::ISceneNode* n = smgr->addCubeSceneNode();

  if(n) {
    n->setMaterialTexture(0, driver->getTexture("media/t351sml.jpg"));
    n->setMaterialFlag(video::EMF_LIGHTING, false);

    scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(core::vector3df(0, 0, 30), 20.0f);
    if(anim) {
      n->addAnimator(anim);
      anim->drop();
    }
  
  }

  scene::IAnimatedMeshSceneNode* anms = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/ninja.b3d"));
  if(anms) {
    scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(core::vector3df(100, 0, 60), core::vector3df(-100, 0, 60), 3500, true);

    if(anim) {
      anms->addAnimator(anim);
      anim->drop();
    }

    anms->setMaterialFlag(video::EMF_LIGHTING, false);

    anms->setFrameLoop(0, 13);
    anms->setAnimationSpeed(15);

    anms->setScale(core::vector3df(2.f, 2.f, 2.f));
    anms->setRotation(core::vector3df(0, -90, 0));    
  }

  smgr->addCameraSceneNodeFPS();
  device->getCursorControl()->setVisible(false);

  device->getGUIEnvironment()->addImage(driver->getTexture("media/irrlichtlogoalpha2.tga"), core::position2d<s32>(10, 20));

  gui::IGUIStaticText* diagnostics = device->getGUIEnvironment()->addStaticText(L"", core::rect<s32>(10, 10, 400, 20));
  diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));

  int lastFPS = -1;
  u32 then = device->getTimer()->getTime();
  const f32 MOVEMENT_SPEED = 5.f;

  while(device->run()) {
    const u32 now = device->getTimer()->getTime();
    const f32 frameDeltaTime = (f32)(now - then) / 1000.f;
    then = now;

    core::vector3df nodePosition = node->getPosition();

    if(receiver.IsKeyDown(KEY_KEY_W))
      nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
    else if(receiver.IsKeyDown(KEY_KEY_S))
      nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

    if(receiver.IsKeyDown(KEY_KEY_A))
      nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
    else if(receiver.IsKeyDown(KEY_KEY_D))
      nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

    node->setPosition(nodePosition);

    driver->beginScene(true, true, video::SColor(255, 113, 113, 133));

    smgr->drawAll();
    device->getGUIEnvironment()->drawAll();

    driver->endScene();

    int fps = driver->getFPS();

    if(lastFPS != fps) {
      core::stringw tmp(L"Movement example [");
      tmp += driver->getName();
      tmp += L"] FPS: [";
      tmp += fps;
      tmp += L"]";
    }	    
      
  }

  device->drop();
  return 0;
}
