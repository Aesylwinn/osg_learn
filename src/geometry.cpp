#include "geometry.hpp"

#include <cmath>
#include <osg/Geode>
#include <osg/Geometry>

osg::ref_ptr<osg::Node> createPlane(int w, int h)
{
    const float SubDivisionSegmentLength = 0.5;

    int numCols = std::abs(w / SubDivisionSegmentLength);
    int numRows = std::abs(h / SubDivisionSegmentLength);

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    
    // Geometry
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
    osg::ref_ptr<osg::DrawElementsUShort> indices = new osg::DrawElementsUShort();
    indices->setMode(osg::PrimitiveSet::TRIANGLES);

    for (int r = 0; r < numRows; ++r)
    {
        for (int c = 0; c < numCols; ++c)
        {
            float x = c / (float)numCols * w - w / 2.f;
            float y = r / (float)numRows * h - h / 2.f;
            float i = SubDivisionSegmentLength;
            float j = SubDivisionSegmentLength;

            int baseIndex = vertices->size();

            vertices->push_back(osg::Vec3(x+0,y+0,  0));
            vertices->push_back(osg::Vec3(x+i,y+0,  0));
            vertices->push_back(osg::Vec3(x+i,y+j,  0));
            vertices->push_back(osg::Vec3(x+0,y+j,  0));

            indices->addElement(baseIndex+0);
            indices->addElement(baseIndex+1);
            indices->addElement(baseIndex+2);
            indices->addElement(baseIndex+0);
            indices->addElement(baseIndex+2);
            indices->addElement(baseIndex+3);
        }
    }

    geometry->setVertexArray(vertices.get());
    geometry->addPrimitiveSet(indices.get());


    // Colors
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
    colors->push_back(osg::Vec4(0.1f, 1.0f,  0.1f, 1.0f));
    geometry->setColorArray(colors.get());
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);


    // Normals
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();
    normals->push_back(osg::Vec3(0.f, 0.f, 1.0f));
    geometry->setNormalArray(normals.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);


    // Node
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(geometry.get());

    return geode;
}

