#include "geometry.hpp"

#include <osg/Geode>
#include <osg/Geometry>

osg::ref_ptr<osg::Node> createPlane(int w, int h)
{
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
    vertices->push_back(osg::Vec3(-w, -h, 0));
    vertices->push_back(osg::Vec3( w, -h, 0));
    vertices->push_back(osg::Vec3( w,  h, 0));
    vertices->push_back(osg::Vec3(-w,  h, 0));
    geometry->setVertexArray(vertices.get());

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
    colors->push_back(osg::Vec4(0.f, 1.0f,  0.f, 1.0f));
    colors->push_back(osg::Vec4(0.f, 1.0f,  0.f, 1.0f));
    colors->push_back(osg::Vec4(0.f, 1.0f,  0.f, 1.0f));
    colors->push_back(osg::Vec4(0.f, 1.0f,  0.f, 1.0f));
    geometry->setColorArray(colors.get());
    geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();
    normals->push_back(osg::Vec3(0.f, 0.f, -1.0f));
    geometry->setNormalArray(normals.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

    osg::ref_ptr<osg::DrawElementsUShort> indices = new osg::DrawElementsUShort();
    indices->setMode(osg::PrimitiveSet::TRIANGLES);
    indices->addElement(0);
    indices->addElement(1);
    indices->addElement(2);
    indices->addElement(0);
    indices->addElement(2);
    indices->addElement(3);
    geometry->addPrimitiveSet(indices.get());

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(geometry.get());

    return geode;
}

