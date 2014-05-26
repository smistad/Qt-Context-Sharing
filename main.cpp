#include "main.hpp"
#include <iostream>
#include <QApplication>
#include <GL/glx.h>
#include <QHBoxLayout>

WindowWidget::WindowWidget(QGLContext* context) {
    mView = new View(context);
    QGLContext* context2 = new QGLContext(QGLFormat::defaultFormat(), mView);
    context2->create(context);
    if(!context2->isValid()) {
        std::cout << "QGL context 2 is invalid!" << std::endl;
        exit(-1);
    }
    if(context2->isSharing()) {
        std::cout << "context 2 is sharing" << std::endl;
    }

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mView);
    setLayout(mainLayout);
    setWindowTitle("Test");
    resize(512,512);
    setContentsMargins(0, 0, 0, 0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
}

void View::paintGL() {
    // TODO force a specific GL context
    std::cout << "View GL context: " << glXGetCurrentContext() << std::endl;
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f,-1.0f, 0.0f);
        glVertex3f(-1.0f,-1.0f, 0.0f);
    glEnd();
};


void View::initializeGL() {};
void View::resizeGL(int w, int h) {};

int main(int argc, char ** argv) {

    QApplication *app = new QApplication(argc, argv);

    QGLWidget* widget = new QGLWidget;

    // Create GL context
    QGLContext* context = new QGLContext(QGLFormat::defaultFormat(), widget); // by including widget here the context becomes valid
    context->create();
    if(!context->isValid()) {
        std::cout << "QGL context is invalid!" << std::endl;
        return 0;
    }

    context->makeCurrent();
    std::cout << "Initial GL context: " << glXGetCurrentContext() << std::endl;
    // TODO Send the actual GL context to the View

    WindowWidget *window1 = new WindowWidget(context);
    window1->show();

    if(context->isSharing()) {
        std::cout << "initial context is sharing" << std::endl;
    }

    QApplication::exec();

    return 0;
}
