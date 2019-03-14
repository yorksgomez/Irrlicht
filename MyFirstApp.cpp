/*input
a
*/

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
	#pragma comment(lib, "irrlicht.lib")
#endif

class CSampleSceneNode : public scene::ISceneNode {
	private: 
		core::aabbox3d<f32> Box;
		video::S3DVertex vertices[4];
		video::SMaterial Material;

	public:
		CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id) {
			Material.Wireframe = false;
			Material.Lighting = false;

			vertices[0] = video::S3DVertex(0, 0, 10, 1, 1, 0, video::SColor(255, 0, 255, 255), 0, 1);
			vertices[1] = video::S3DVertex(10, 0, -10, 1, 0, 0, video::SColor(255, 255, 0, 255), 1, 1);
			vertices[2] = video::S3DVertex(0, 20, 0, 0, 1, 1, video::SColor(255, 255, 255, 0), 1, 0);
			vertices[3] = video::S3DVertex(-10, 0, -10, 0, 0, 1, video::SColor(255, 0, 255, 0), 0, 0);

			Box.reset(vertices[0].Pos);
			for(s32 i = 1; i < 4; ++i)
				Box.addInternalPoint(vertices[i].Pos);

		}

		virtual void OnRegisterSceneNode() {

			if(IsVisible)
				SceneManager->registerNodeForRendering(this);

			ISceneNode::OnRegisterSceneNode();
		}

		virtual void render() {
			u16 indices[] = {0, 2, 3, 2, 1, 3, 1, 0, 3, 2, 0, 1};

			video::IVideoDriver* driver = SceneManager->getVideoDriver();

			driver->setMaterial(Material);
			driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
			driver->drawVertexPrimitiveList(&vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
		}

		virtual const core::aabbox3d<f32>& getBoundingBox() const {
			return Box;
		}

		virtual u32 getMaterialCount() {
			return 1;
		}

		virtual video::SMaterial& getMaterial(u32 i) {
			return Material;
		}

};

int main() {

	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if(driverType == video::EDT_COUNT)
		return 1;

	IrrlichtDevice* device = createDevice(driverType, core::dimension2d<u32>(640, 480), 16, false);
	if(!device)
		return 2;

	device->setWindowCaption(L"Scene node");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	smgr->addCameraSceneNode(0, core::vector3df(0, -40, 0), core::vector3df(0, 0, 0));

	CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);

	scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));

	if(anim) {
		myNode->addAnimator(anim);
		anim->drop();
		anim = 0;
	}

	myNode->drop();
	myNode = 0;

	u32 frames = 0;
	while(device->run()) {
		driver->beginScene(true, true, video::SColor(0, 100, 100, 100));

		smgr->drawAll();

		driver->endScene();
		if(++frames == 100) {
			core::stringw str = L"Edhawk Productions: [";
			str += driver->getName();
			str += L"] FPS[";
			str += (s32)driver->getFPS();
			str += L"]";

			device->setWindowCaption(str.c_str());
			frames = 0;
		}

	}

	device->drop();
	return 0;
}
