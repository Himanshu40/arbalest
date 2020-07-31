/*                     D I S P L A Y . C P P
 * BRL-CAD
 *
 * Copyright (c) 2020 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file Display.cpp */

#include "Display.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <QtWidgets/QApplication>
#include <QWidget>
#include <OrthographicCamera.h>
#include "DisplayManager.h"
#include "GeometryRenderer.h"
#include "Utils.h"

using namespace std;


Display::Display(Document*  document):document(document) {
    camera = new OrthographicCamera();
    displayManager = new DisplayManager(*this);
    geometryRenderer = new GeometryRenderer(document);
    axesRenderer = new AxesRenderer();

    displayManager->setBGColor(bgColor[0],bgColor[1],bgColor[2]);

    makeCurrent();
    onDatabaseUpdated();
    autoView();
    update();
}

Display::~Display() {
    delete camera;
    delete displayManager;
    delete geometryRenderer;
    delete axesRenderer;
}

void Display::onDatabaseUpdated() {
    geometryRenderer->onDatabaseUpdated();
    update();
}

void Display::refresh() {
    makeCurrent();
    update();
}

void Display::autoView() const
{
	BRLCAD::Vector3D midPoint = (document->getDatabase()->BoundingBoxMinima() + document->getDatabase()->BoundingBoxMaxima()) / 2;
	auto a = document->getDatabase()->BoundingBoxMinima();
	auto b = document->getDatabase()->BoundingBoxMaxima();
	camera->setEyePosition(midPoint.coordinates[0], midPoint.coordinates[1], midPoint.coordinates[2]);

	const BRLCAD::Vector3D volume = (document->getDatabase()->BoundingBoxMinima() - document->getDatabase()->BoundingBoxMaxima());
	camera->setZoom(vector3DLength(volume) * 1.1);
}

int Display::getW() const {
    return w;
}

int Display::getH() const {
    return h;
}

const Document* Display::getDocument() const
{
    return document;
}

DisplayManager* Display::getDisplayManager() const
{
	return displayManager;
}

void Display::resizeGL(const int w, const int h) {
    camera->setWH(w,h);
    this->w = w;
    this->h = h;
}

void Display::paintGL() {
    displayManager->drawBegin();

    glViewport(0,0,w,h);
    displayManager->loadMatrix(static_cast<const float*>(glm::value_ptr(camera->modelViewMatrix())));
    displayManager->loadPMatrix(static_cast<const float*>(glm::value_ptr(camera->projectionMatrix())));
    geometryRenderer->render();

    glViewport(w*.9,0,w/10,w/10);
    displayManager->loadMatrix(static_cast<const float*>(glm::value_ptr(camera->modelViewMatrixNoTranslate())));
    displayManager->loadPMatrix(static_cast<const float*>(glm::value_ptr(camera->projectionMatrix(w / 10, w / 10))));
    axesRenderer->render();
}

void Display::mouseMoveEvent(QMouseEvent *event) {
	const int x = event->x();
	const int y = event->y();
    int globalX = event->globalX();
    int globalY = event->globalY();

    bool resetX = false, resetY = false;

    if(prevMouseX != -1 && prevMouseY != -1 && (event->buttons() & (rotateCameraMouseButton|moveCameraMouseButton))) {
        if (skipNextMouseMoveEvent) {
            skipNextMouseMoveEvent = false;
            return;
        }
        if(event->buttons() & (rotateCameraMouseButton)) {
	        const bool rotateThirdAxis = QApplication::keyboardModifiers().testFlag(rotateAroundThirdAxisModifier);
            camera->processRotateRequest(x- prevMouseX, y - prevMouseY,rotateThirdAxis);
        }
        if(event->buttons() & (moveCameraMouseButton)){
            camera->processMoveRequest(x- prevMouseX, y - prevMouseY);
        }

        refresh();

        const QPoint topLeft = mapToGlobal(QPoint(0,0));
        const QPoint bottomRight = mapToGlobal(QPoint(size().width(),size().height()));

        int newX = -1;
        int newY = -1;

        if (globalX <= topLeft.x()) {
            newX = bottomRight.x()-1;
            resetX = true;
        }
        if (globalX >= bottomRight.x()) {
            newX = topLeft.x()+1;
            resetX = true;
        }
        if (globalY <= topLeft.y()) {
            newY = bottomRight.y()-1;
            resetY = true;
        }
        if (globalY >= bottomRight.y()) {
            newY = topLeft.y()+1;
            resetY = true;
        }

        if (resetX || resetY) {
            prevMouseX = resetX ? mapFromGlobal(QPoint(newX,newY)).x() : x;
            prevMouseY = resetY ? mapFromGlobal(QPoint(newX,newY)).y() : y;
            QCursor::setPos(resetX ? newX : globalX, resetY ? newY : globalY);
            skipNextMouseMoveEvent = true;
        }
    }

    if(!resetX && !resetY) {
        prevMouseX = x;
        prevMouseY = y;
    }
}

void Display::mousePressEvent(QMouseEvent *event) {
    prevMouseX = event->x();
    prevMouseY = event->y();
}

void Display::mouseReleaseEvent(QMouseEvent *event) {
    prevMouseX = -1;
    prevMouseY = -1;
}

void Display::wheelEvent(QWheelEvent *event) {

    if (event->phase() == Qt::NoScrollPhase || event->phase() == Qt::ScrollUpdate || event->phase() == Qt::ScrollMomentum) {
        camera->processZoomRequest(event->angleDelta().y() / 8);
        refresh();
    }
}

void Display::keyPressEvent( QKeyEvent *k ) {
    switch (k->key()) {
        case Qt::Key_Up:
            camera->processMoveRequest(0, keyPressSimulatedMouseMoveDistance);
            refresh();
            break;
        case Qt::Key_Down:
            camera->processMoveRequest(0, -keyPressSimulatedMouseMoveDistance);
            refresh();
            break;
        case Qt::Key_Left:
            camera->processMoveRequest(keyPressSimulatedMouseMoveDistance, 0);
            refresh();
            break;
        case Qt::Key_Right:
            camera->processMoveRequest(-keyPressSimulatedMouseMoveDistance, 0);
            refresh();
            break;
    }
}
