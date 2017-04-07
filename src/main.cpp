#include "geometry.hpp"

#include <cassert>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Shader>
#include <osg/Vec3d>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

int main(int argc, const char* argv[])
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    // Context setup
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();
    traits->x = 100;
    traits->y = 100;
    traits->width = 640;
    traits->height = 480;
    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;

    osg::ref_ptr<osg::GraphicsContext> context = osg::GraphicsContext::createGraphicsContext(traits.get());
    assert(context.get());


    // Setup camera
    osg::ref_ptr<osg::Camera> camera = new osg::Camera();
    camera->setGraphicsContext(context.get());
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
    camera->setDrawBuffer(buffer);
    camera->setReadBuffer(buffer);
    viewer->addSlave(camera.get(), osg::Matrixd(), osg::Matrixd());
    viewer->realize();

    context->getState()->setUseModelViewAndProjectionUniforms(true);
    context->getState()->setUseVertexAttributeAliasing(true);


    // The root node everything else attaches to
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::StateSet> rootSS = root->getOrCreateStateSet();
    viewer->setSceneData(root);


    // Shaders
    osg::ref_ptr<osg::Program> modelProgram = new osg::Program();
    modelProgram->setName("modelshader");
    osg::ref_ptr<osg::Shader> vertShader =
        osg::Shader::readShaderFile(osg::Shader::VERTEX, "test/model.vert");
    osg::ref_ptr<osg::Shader> fragShader =
        osg::Shader::readShaderFile(osg::Shader::FRAGMENT, "test/model.frag");

    modelProgram->addShader(vertShader.get());
    modelProgram->addShader(fragShader.get());


    // A shiny cow
    osg::ref_ptr<osg::PositionAttitudeTransform> cowTrans =
        new osg::PositionAttitudeTransform();
    cowTrans->addChild(osgDB::readNodeFile("test/cow.osg"));
    cowTrans->getOrCreateStateSet()->setAttribute(modelProgram.get(), osg::StateAttribute::ON);
    root->addChild(cowTrans);


    // A simple plane
    osg::ref_ptr<osg::PositionAttitudeTransform> planeTrans =
        new osg::PositionAttitudeTransform();
    planeTrans->addChild(createPlane(30, 30));
    planeTrans->setPosition(osg::Vec3d(0, 0, -3));
    planeTrans->getOrCreateStateSet()->setAttribute(modelProgram.get(), osg::StateAttribute::ON);
    root->addChild(planeTrans);


    // Run scene
    return viewer->run();
}

