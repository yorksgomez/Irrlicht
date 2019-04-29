/*input
a
*/
//g++ -Iirr/include -I/usr/X11R6/include  -O3 -ffast-math MyFirstApp.cpp -o ./MyFirstApp -Lirr/lib/Linux -lIrrlicht -L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor

#include <irrlicht.h>
#include <iostream>
#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

int main()
{
    // ask if user would like shadows
    char i;
    printf("Please press 'y' if you want to use realtime shadows.\n");

    std::cin >> i;

    const bool shadows = (i == 'y');

    // ask user for driver
    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

     IrrlichtDevice *device =
        createDevice(driverType, core::dimension2d<u32>(640, 480),
        16, false, shadows);

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
 scene::IAnimatedMesh* mesh = smgr->getMesh("media/room.3ds");

    smgr->getMeshManipulator()->makePlanarTextureMapping(mesh->getMesh(0), 0.004f);

    scene::ISceneNode* node = 0;

    node = smgr->addAnimatedMeshSceneNode(mesh);
    node->setMaterialTexture(0, driver->getTexture("media/wall.jpg"));
    node->getMaterial(0).SpecularColor.set(0,0,0,0);

      mesh = smgr->addHillPlaneMesh( "myHill",
        core::dimension2d<f32>(20,20),
        core::dimension2d<u32>(40,40), 0, 0,
        core::dimension2d<f32>(0,0),
        core::dimension2d<f32>(10,10));

    node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 3.0f, 300.0f, 30.0f);
    node->setPosition(core::vector3df(0,7,0));

    node->setMaterialTexture(0, driver->getTexture("media/stones.jpg"));
    node->setMaterialTexture(1, driver->getTexture("media/water.jpg"));

    node->setMaterialType(video::EMT_REFLECTION_2_LAYER);
 // create light

    node = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
        video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
    scene::ISceneNodeAnimator* anim = 0;
    anim = smgr->createFlyCircleAnimator (core::vector3df(0,150,0),250.0f);
    node->addAnimator(anim);
    anim->drop();

    // attach billboard to light

    node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(50, 50));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    node->setMaterialTexture(0, driver->getTexture("media/particlewhite.bmp"));

    //Create particle system
    scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode(false);

    scene::IParticleEmitter* em = ps->createBoxEmitter(
      core::aabbox3df(-7, 0, -1, 7, 1, 7), //size
      core::vector3df(0.0f, 0.06f, 0.0f), //initial direction
      80, 100, //emit rate
      video::SColor(0, 255, 255, 255), //darkest color
      video::SColor(0, 255, 255, 255), //brightest color
      800, 2000, 0, //min and max age, angle
      core::dimension2df(10.f, 10.f), //min size
      core::dimension2df(20.f, 20.f) //max size
    );

    ps->setEmitter(em);
    em->drop();

    ps->setPosition(core::vector3df(-70, 60, 40));
    ps->setScale(core::vector3df(2, 2, 2));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

    scene::IVolumeLightSceneNode* n = smgr->addVolumeLightSceneNode(0, -1, 32, 32, video::SColor(0, 255, 255, 255), video::SColor(0, 0, 0, 0));

    if(n) {
      n->setScale(core::vector3df(56.0f, 56.0f, 56.0f));
      n->setPosition(core::vector3df(-120, 50, 40));

      core::array<video::ITexture*> textures;
      for(s32 g = 7; g > 0; --g) {
        core::stringc tmp;
        tmp = "media/portal";
        tmp += g;
        tmp += ".bmp";
        video::ITexture* t = driver->getTexture(tmp.c_str());
        textures.push_back(t);
      }

      scene::ISceneNodeAnimator* glow = smgr->createTextureAnimator(textures, 150);
      n->addAnimator(glow);

      glow->drop();
    }

    mesh = smgr->getMesh("media/dwarf.x");
    scene::IAnimatedMeshSceneNode* anode = 0;

    anode = smgr->addAnimatedMeshSceneNode(mesh);
    anode->setPosition(core::vector3df(-50, 20, -60));
    anode->setAnimationSpeed(15);

    //add shadow
    anode->addShadowVolumeSceneNode();
    smgr->setShadowColor(video::SColor(150, 0, 0, 0));

    anode->setScale(core::vector3df(2, 2, 2));
    anode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);


    smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);

    while(device->run()) {

      if(device->isWindowActive()) {
        driver->beginScene();
        smgr->drawAll();
        driver->endScene();
      }

    }

    device->drop();
    return 0;
}
