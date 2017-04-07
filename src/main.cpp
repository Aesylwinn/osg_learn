#include "geometry.hpp"

#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Shader>
#include <osg/Vec3d>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

int main(int argc, const char* argv[])
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->realize();

    // Setup camera
    osg::ref_ptr<osg::State> camState = viewer->getCamera()->getGraphicsContext()->getState();
    camState->setUseModelViewAndProjectionUniforms(true);
    camState->setUseVertexAttributeAliasing(true);


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


    // Some lighting
    osg::ref_ptr<osg::Light> light = new osg::Light();
    light->setLightNum(0);
    light->setAmbient(osg::Vec4(0.1f, 0.2f, 0.2f, 1.0f));
    light->setDiffuse(osg::Vec4(0.3f, 0.7f, 0.7f, 1.0f));
    light->setSpecular(osg::Vec4(0.3f, 0.7f, 0.7f, 1.0f));
    light->setPosition(osg::Vec4(10.f, 10.f, 10.f, 1.0f));
    light->setDirection(osg::Vec3(-0.577f, -0.577f, -0.577f));
    light->setSpotCutoff(25.0f);

    osg::ref_ptr<osg::Light> purpleLight = new osg::Light();
    purpleLight->setLightNum(1);
    purpleLight->setAmbient(osg::Vec4(0.2f, 0.1f, 0.2f, 1.0f));
    purpleLight->setDiffuse(osg::Vec4(0.7f, 0.2f, 0.8f, 1.0f));
    purpleLight->setSpecular(osg::Vec4(0.7f, 0.2f, 0.8f, 1.0f));
    purpleLight->setPosition(osg::Vec4(-10, -10, 10, 1));
    purpleLight->setDirection(osg::Vec3(0.577f, 0.577f, -0.577f));
    purpleLight->setSpotCutoff(25.0f);

    // Attach lights to scene
    osg::ref_ptr<osg::Group> lightRoot = new osg::Group();
    root->addChild(lightRoot);

    osg::ref_ptr<osg::LightSource> lightSrc = new osg::LightSource();
    lightSrc->setLight(light);
    lightSrc->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSrc->setStateSetModes(*rootSS, osg::StateAttribute::ON);
    lightRoot->addChild(lightSrc.get());

    osg::ref_ptr<osg::LightSource> purpleLightSrc = new osg::LightSource();
    purpleLightSrc->setLight(purpleLight);
    purpleLightSrc->setLocalStateSetModes(osg::StateAttribute::ON);
    purpleLightSrc->setStateSetModes(*rootSS, osg::StateAttribute::ON);
    lightRoot->addChild(purpleLightSrc.get());


    // Run scene
    return viewer->run();
}

