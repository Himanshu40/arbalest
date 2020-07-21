
#include <brlcad/Cone.h>
#include <brlcad/Arb8.h>


#include <QtWidgets/QVBoxLayout>
#include <QtOpenGL/QtOpenGL>
#include "TypeSpecificProperties.h"
#include "QHBoxWidget.h"

#include <QStyledItemDelegate>
#include <include/QVBoxWidget.h>
#include <include/DataRow.h>
#include <include/ObjectDataField.h>
#include <include/ObjectDataTable.h>
#include <brlcad/BagOfTriangles.h>
#include <brlcad/EllipticalTorus.h>
#include <brlcad/Halfspace.h>
#include <brlcad/HyperbolicCylinder.h>
#include <brlcad/Hyperboloid.h>
#include <brlcad/ParabolicCylinder.h>
#include <brlcad/Paraboloid.h>
#include <brlcad/Particle.h>
#include <brlcad/Sphere.h>
#include <brlcad/Torus.h>

using namespace std;

TypeSpecificProperties::TypeSpecificProperties(Document &document, BRLCAD::Object *object)
        : document(document), object(object) {
    setObjectName("properties-TypeSpecificProperties");
    l = new QVBoxLayout(this);
    l->setContentsMargins(0, 0, 0, 0);
    setLayout(l);

    const QStringList pointsIndices = {"P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8"};
    const QStringList abcdIndices = {"A", "B", "C", "D", "E", "F"};

    if(QString(object->Type()) == "Arb8") {
        ObjectDataField<BRLCAD::Arb8> * property;
        property = new ObjectDataField<BRLCAD::Arb8>(
                &document,
                object,
                &BRLCAD::Arb8::Point,
                &BRLCAD::Arb8::SetPoint,
                1,
                dynamic_cast<BRLCAD::Arb8*>(object)->NumberOfVertices(),
                pointsIndices,
                "Points");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "Cone") {
        ObjectDataField<BRLCAD::Cone> * property;

        property = new ObjectDataField<BRLCAD::Cone>(
                &document,
                object,
                &BRLCAD::Cone::BasePoint,
                &BRLCAD::Cone::SetBasePoint,
                "Base Point");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Cone>(
                &document,
                object,
                &BRLCAD::Cone::Height,
                &BRLCAD::Cone::SetHeight,
                "Height");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Cone>(
                &document,
                object,
                &BRLCAD::Cone::SemiPrincipalAxis,
                &BRLCAD::Cone::SetSemiPrincipalAxis,
                0,
                3,
                abcdIndices,
                "Semi Principal Axes");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "Ellipsoid") {
        ObjectDataField<BRLCAD::Ellipsoid> * property;

        property = new ObjectDataField<BRLCAD::Ellipsoid>(
                &document,
                object,
                &BRLCAD::Ellipsoid::Center,
                &BRLCAD::Ellipsoid::SetCenter,
                "Center");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Ellipsoid>(
                &document,
                object,
                &BRLCAD::Ellipsoid::SemiPrincipalAxis,
                &BRLCAD::Ellipsoid::SetSemiPrincipalAxis,
                0,
                3,
                abcdIndices,
                "Semi Principal Axes");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "EllipticalTorus") {
        ObjectDataField<BRLCAD::EllipticalTorus> * property;

        property = new ObjectDataField<BRLCAD::EllipticalTorus>(
                &document,
                object,
                &BRLCAD::EllipticalTorus::Center,
                &BRLCAD::EllipticalTorus::SetCenter,
                "Center");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::EllipticalTorus>(
                &document,
                object,
                &BRLCAD::EllipticalTorus::Normal,
                &BRLCAD::EllipticalTorus::SetNormal,
                "Normal");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::EllipticalTorus>(
                &document,
                object,
                &BRLCAD::EllipticalTorus::TubeCenterLineRadius,
                &BRLCAD::EllipticalTorus::SetTubeCenterLineRadius,
                "Tube Center Line Radius");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::EllipticalTorus>(
                &document,
                object,
                &BRLCAD::EllipticalTorus::TubeSemiMajorAxis,
                &BRLCAD::EllipticalTorus::SetTubeSemiMajorAxis,
                "Tube Semi Major Axes");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::EllipticalTorus>(
                &document,
                object,
                &BRLCAD::EllipticalTorus::TubeSemiMinorAxis,
                &BRLCAD::EllipticalTorus::SetTubeSemiMinorAxis,
                "Tube Semi Minor Axes");
        l->addWidget(property);

    }


    if(QString(object->Type()) == "Halfspace") {
        ObjectDataField<BRLCAD::Halfspace> * property;

        property = new ObjectDataField<BRLCAD::Halfspace>(
                &document,
                object,
                &BRLCAD::Halfspace::Normal,
                &BRLCAD::Halfspace::SetNormal,
                "Normal");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Halfspace>(
                &document,
                object,
                &BRLCAD::Halfspace::DistanceFromOrigin,
                &BRLCAD::Halfspace::SetDistanceFromOrigin,
                "Distance From Origin");
        l->addWidget(property);

    }


    if(QString(object->Type()) == "HyperbolicCylinder") {
        ObjectDataField<BRLCAD::HyperbolicCylinder> * property;

        property = new ObjectDataField<BRLCAD::HyperbolicCylinder>(
                &document,
                object,
                &BRLCAD::HyperbolicCylinder::BasePoint,
                &BRLCAD::HyperbolicCylinder::SetBasePoint,
                "Base Point");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::HyperbolicCylinder>(
                &document,
                object,
                &BRLCAD::HyperbolicCylinder::Height,
                &BRLCAD::HyperbolicCylinder::SetHeight,
                "Height");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::HyperbolicCylinder>(
                &document,
                object,
                &BRLCAD::HyperbolicCylinder::Depth,
                &BRLCAD::HyperbolicCylinder::SetDepth,
                "Depth");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::HyperbolicCylinder>(
                &document,
                object,
                &BRLCAD::HyperbolicCylinder::HalfWidth,
                &BRLCAD::HyperbolicCylinder::SetHalfWidth,
                "Half Width");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::HyperbolicCylinder>(
                &document,
                object,
                &BRLCAD::HyperbolicCylinder::ApexAsymptoteDistance,
                &BRLCAD::HyperbolicCylinder::SetApexAsymptoteDistance,
                "Apex Asymptote Distance");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "Hyperboloid") {
        ObjectDataField<BRLCAD::Hyperboloid> * property;

        property = new ObjectDataField<BRLCAD::Hyperboloid>(
                &document,
                object,
                &BRLCAD::Hyperboloid::BasePoint,
                &BRLCAD::Hyperboloid::SetBasePoint,
                "Base Point");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Hyperboloid>(
                &document,
                object,
                &BRLCAD::Hyperboloid::Height,
                &BRLCAD::Hyperboloid::SetHeight,
                "Height");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Hyperboloid>(
                &document,
                object,
                &BRLCAD::Hyperboloid::SemiMajorAxis,
                &BRLCAD::Hyperboloid::SetSemiMajorAxis,
                "Semi Major Axis");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Hyperboloid>(
                &document,
                object,
                &BRLCAD::Hyperboloid::SemiMajorAxisDirection,
                &BRLCAD::Hyperboloid::SetSemiMajorAxisDirection,
                "Semi Major Axis Direction");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Hyperboloid>(
                &document,
                object,
                &BRLCAD::Hyperboloid::SemiMajorAxisLength,
                &BRLCAD::Hyperboloid::SetSemiMajorAxisLength,
                "Semi Major Axis Length");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Hyperboloid>(
                &document,
                object,
                &BRLCAD::Hyperboloid::SemiMinorAxisLength,
                &BRLCAD::Hyperboloid::SetSemiMinorAxisLength,
                "Semi Minor Axis Length");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Hyperboloid>(
                &document,
                object,
                &BRLCAD::Hyperboloid::ApexAsymptoteDistance,
                &BRLCAD::Hyperboloid::SetApexAsymptoteDistance,
                "Apex Asymptote Distance");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "ParabolicCylinder") {
        ObjectDataField<BRLCAD::ParabolicCylinder> * property;

        property = new ObjectDataField<BRLCAD::ParabolicCylinder>(
                &document,
                object,
                &BRLCAD::ParabolicCylinder::BasePoint,
                &BRLCAD::ParabolicCylinder::SetBasePoint,
                "Base Point");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::ParabolicCylinder>(
                &document,
                object,
                &BRLCAD::ParabolicCylinder::Height,
                &BRLCAD::ParabolicCylinder::SetHeight,
                "Height");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::ParabolicCylinder>(
                &document,
                object,
                &BRLCAD::ParabolicCylinder::Depth,
                &BRLCAD::ParabolicCylinder::SetDepth,
                "Depth");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::ParabolicCylinder>(
                &document,
                object,
                &BRLCAD::ParabolicCylinder::HalfWidth,
                &BRLCAD::ParabolicCylinder::SetHalfWidth,
                "Half Width");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "Paraboloid") {
        ObjectDataField<BRLCAD::Paraboloid> * property;

        property = new ObjectDataField<BRLCAD::Paraboloid>(
                &document,
                object,
                &BRLCAD::Paraboloid::BasePoint,
                &BRLCAD::Paraboloid::SetBasePoint,
                "Base Point");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Paraboloid>(
                &document,
                object,
                &BRLCAD::Paraboloid::Height,
                &BRLCAD::Paraboloid::SetHeight,
                "Height");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Paraboloid>(
                &document,
                object,
                &BRLCAD::Paraboloid::SemiMajorAxis,
                &BRLCAD::Paraboloid::SetSemiMajorAxis,
                "Semi Major Axis");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Paraboloid>(
                &document,
                object,
                &BRLCAD::Paraboloid::SemiMajorAxisDirection,
                &BRLCAD::Paraboloid::SetSemiMajorAxisDirection,
                "Semi Major Axis Direction");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Paraboloid>(
                &document,
                object,
                &BRLCAD::Paraboloid::SemiMajorAxisLength,
                &BRLCAD::Paraboloid::SetSemiMajorAxisLength,
                "Semi Major Axis Length");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Paraboloid>(
                &document,
                object,
                &BRLCAD::Paraboloid::SemiMinorAxisLength,
                &BRLCAD::Paraboloid::SetSemiMinorAxisLength,
                "Semi Minor Axis Length");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "Particle") {
        ObjectDataField<BRLCAD::Particle> * property;

        property = new ObjectDataField<BRLCAD::Particle>(
                &document,
                object,
                &BRLCAD::Particle::BasePoint,
                &BRLCAD::Particle::SetBasePoint,
                "Base Point");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Particle>(
                &document,
                object,
                &BRLCAD::Particle::Height,
                &BRLCAD::Particle::SetHeight,
                "Height");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Particle>(
                &document,
                object,
                &BRLCAD::Particle::BaseRadius,
                &BRLCAD::Particle::SetBaseRadius,
                "Base Radius");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Particle>(
                &document,
                object,
                &BRLCAD::Particle::TopRadius,
                &BRLCAD::Particle::SetTopRadius,
                "Top Radius");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "Sphere") {
        ObjectDataField<BRLCAD::Sphere> * property;

        property = new ObjectDataField<BRLCAD::Sphere>(
                &document,
                object,
                &BRLCAD::Sphere::Center,
                &BRLCAD::Sphere::SetCenter,
                "Center");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Sphere>(
                &document,
                object,
                &BRLCAD::Sphere::Radius,
                &BRLCAD::Sphere::SetRadius,
                "Radius");
        l->addWidget(property);
    }


    if(QString(object->Type()) == "Torus") {
        ObjectDataField<BRLCAD::Torus> * property;

        property = new ObjectDataField<BRLCAD::Torus>(
                &document,
                object,
                &BRLCAD::Torus::Center,
                &BRLCAD::Torus::SetCenter,
                "Center");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Torus>(
                &document,
                object,
                &BRLCAD::Torus::Normal,
                &BRLCAD::Torus::SetNormal,
                "Normal");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Torus>(
                &document,
                object,
                &BRLCAD::Torus::TubeCenterLineRadius,
                &BRLCAD::Torus::SetTubeCenterLineRadius,
                "Tube Center Line Radius");
        l->addWidget(property);

        property = new ObjectDataField<BRLCAD::Torus>(
                &document,
                object,
                &BRLCAD::Torus::TubeRadius,
                &BRLCAD::Torus::SetTubeRadius,
                "Tube TubeRadius");
        l->addWidget(property);
    }

    l->addStretch(1);
}
