#include "geometry.hpp"

#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Vec3d>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

int main(int argc, const char* argv[])
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    // The root node everything else attaches to
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::StateSet> rootSS = root->getOrCreateStateSet();
    viewer->setSceneData(root);


    // A shiny cow
    osg::ref_ptr<osg::PositionAttitudeTransform> cowTrans =
        new osg::PositionAttitudeTransform();
    cowTrans->addChild(osgDB::readNodeFile("test/cow.osg"));
    root->addChild(cowTrans);


    // A simple plane
    osg::ref_ptr<osg::PositionAttitudeTransform> planeTrans =
        new osg::PositionAttitudeTransform();
    planeTrans->addChild(createPlane(30, 30));
    planeTrans->setPosition(osg::Vec3d(0, 0, -3));
    root->addChild(planeTrans);


    // Some lighting
    osg::ref_ptr<osg::Light> light = new osg::Light();
    light->setLightNum(0);
    light->setAmbient(osg::Vec4(0.1f, 0.1f, 0.1f, 1.0f));
    light->setDiffuse(osg::Vec4(0.3f, 0.7f, 0.7f, 1.0f));
    light->setSpecular(osg::Vec4(0.3f, 0.7f, 0.7f, 1.0f));
    light->setPosition(osg::Vec4(0.f, 0.f, 10.0f, 1.0f));
    light->setDirection(osg::Vec3(0, 0, -1));
    light->setSpotCutoff(25.0f);

    osg::ref_ptr<osg::LightSource> lightSrc = new osg::LightSource();
    lightSrc->setLight(light);
    lightSrc->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSrc->setStateSetModes(*rootSS, osg::StateAttribute::ON);

    osg::ref_ptr<osg::Group> lightRoot = new osg::Group();
    lightRoot->addChild(lightSrc.get());
    root->addChild(lightRoot);

    // Run scene
    return viewer->run();
}

