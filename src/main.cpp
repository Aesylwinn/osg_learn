#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

int main(int argc, const char* argv[])
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->setSceneData(osgDB::readNodeFile("test/cow.osg"));
    return viewer->run();
}

