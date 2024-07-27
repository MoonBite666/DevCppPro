#include "dcmainwindow.h"
#include "dcmenubar.h"
#include "dw_classdock.h"
#include "dw_projectdock.h"


DCMainWindow::DCMainWindow(QWidget* parent): ElaWindow(parent)
{

    setIsNavigationBarEnable(false);
    showMaximized();
    // moveToCenter();
    auto *menubar = new DCMenuBar(this);
    setMenuBar(menubar);
    auto *projectdock = new ProjectDock(this);
    this->addDockWidget(Qt::LeftDockWidgetArea,projectdock);
    resizeDocks({projectdock}, {600}, Qt::Vertical);
    auto *classdock = new ClassDock(this);
    this->addDockWidget(Qt::LeftDockWidgetArea,classdock);
    resizeDocks({classdock}, {400}, Qt::Vertical);
}


DCMainWindow::~DCMainWindow()
{
}
