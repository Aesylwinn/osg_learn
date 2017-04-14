#include "geometry.hpp"

#include <cassert>
#include <iostream>
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
    assert(context.get() && context.valid());
    context->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.2f, 1.0f));
    context->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    std::cout << "Created Context" << std::endl;


    // Setup camera
    osg::ref_ptr<osg::Camera> camera = new osg::Camera();
    camera->setGraphicsContext(context.get());
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
    camera->setDrawBuffer(buffer);
    camera->setReadBuffer(buffer);
    viewer->addSlave(camera.get(), osg::Matrixd(), osg::Matrixd::scale(1.0, 1.0, 1.0));
    viewer->realize();

    osg::ref_ptr<osg::State> state = context->getState();
    state->setUseModelViewAndProjectionUniforms(true);
    state->setUseVertexAttributeAliasing(true);


    std::cout << "Created Camera" << std::endl;


    // The root node everything else attaches to
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::StateSet> rootSS = root->getOrCreateStateSet();
    viewer->setSceneData(root);
    
    osg::ref_ptr<osg::Uniform> lightPosUniform = new osg::Uniform("lightPos", 
        osg::Vec4f(10, 10, 10, 1));
    osg::ref_ptr<osg::Uniform> lightColUniform = new osg::Uniform("lightColor",
        osg::Vec4f(0.6, 0.7, 0.7, 1));
    osg::ref_ptr<osg::Uniform> brightUniform = new osg::Uniform("brightness",
        0.7f);
    osg::ref_ptr<osg::Uniform> ambientUniform = new osg::Uniform("ambient",
        osg::Vec4f(0.1, 0.1, 0.1, 1));
    rootSS->addUniform(lightPosUniform);
    rootSS->addUniform(lightColUniform);
    rootSS->addUniform(brightUniform);
    rootSS->addUniform(ambientUniform);


    std::cout << "Created Root Node." << std::endl;


    // Shaders
    osg::ref_ptr<osg::Program> modelProgram = new osg::Program();
    modelProgram->setName("modelshader");
    osg::ref_ptr<osg::Shader> vertShader =
        osg::Shader::readShaderFile(osg::Shader::VERTEX, "test/model.vert");
    osg::ref_ptr<osg::Shader> fragShader =
        osg::Shader::readShaderFile(osg::Shader::FRAGMENT, "test/model.frag");

    modelProgram->addShader(vertShader.get());
    modelProgram->addShader(fragShader.get());


    std::cout << "Created Shaders." << std::endl;


    // A shiny cow
    osg::ref_ptr<osg::PositionAttitudeTransform> cowTrans =
        new osg::PositionAttitudeTransform();
    cowTrans->addChild(osgDB::readNodeFile("test/cow.osg"));
    cowTrans->getOrCreateStateSet()->setAttribute(modelProgram.get(), osg::StateAttribute::ON);
    root->addChild(cowTrans);


    std::cout << "Created Cow." << std::endl;


    // A simple plane
    osg::ref_ptr<osg::PositionAttitudeTransform> planeTrans =
        new osg::PositionAttitudeTransform();
    planeTrans->addChild(createPlane(30, 30));
    planeTrans->setPosition(osg::Vec3d(0, 0, -3));
    planeTrans->getOrCreateStateSet()->setAttribute(modelProgram.get(), osg::StateAttribute::ON);
    root->addChild(planeTrans);


    std::cout << "Created plane." << std::endl;


    // Run scene
    return viewer->run();
}

