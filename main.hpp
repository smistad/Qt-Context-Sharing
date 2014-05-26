#ifndef MAIN_HPP
#define MAIN_HPP

#include <QWidget>
#include <QGLWidget>
#include <QGLContext>
#include <QTimer>

class View : public QGLWidget {
        Q_OBJECT
    public:
        View(QGLContext* context) {
            int mFramerate = 25;
            // Set up a timer that will call update on this object at a regular interval
            timer = new QTimer(this);
            timer->start(1000/mFramerate); // in milliseconds
            timer->setSingleShot(false);
            connect(timer,SIGNAL(timeout()),this,SLOT(update()));
        };
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
    private:
        QTimer* timer;

};

class WindowWidget : public QWidget {
        Q_OBJECT
    public:
        WindowWidget(QGLContext* context);
    private:
        View* mView;

};

#endif
