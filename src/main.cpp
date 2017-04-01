#include "geometry.hpp"

#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Vec3d>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

int main(int argc, const char* argv[])
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();


    osg::ref_ptr<osg::PositionAttitudeTransform> cowTrans =
        new osg::PositionAttitudeTransform();
    cowTrans->addChild(osgDB::readNodeFile("test/cow.osg"));


    osg::ref_ptr<osg::PositionAttitudeTransform> planeTrans =
        new osg::PositionAttitudeTransform();
    planeTrans->addChild(createPlane(30, 30));
    planeTrans->setPosition(osg::Vec3d(0, 0, -3));


    osg::ref_ptr<osg::Group> root = new osg::Group();
    root->addChild(cowTrans);
    root->addChild(planeTrans);
    viewer->setSceneData(root);


    return viewer->run();
}

