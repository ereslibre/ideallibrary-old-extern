/*
 * This file is part of the Ideal Library
 * Copyright (C) 2009 Rafael Fernández López <ereslibre@ereslibre.es>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <core/event.h>
#include <gui/widget.h>
#include <gui/painter.h>
#include <gui/application.h>

using namespace IdealGUI;

class MyWidget
    : public Widget
{
public:
    MyWidget(Object *parent);

    virtual Size minimumSize() const;

protected:
    virtual bool event(IdealCore::Event *event);
};

MyWidget::MyWidget(Object *parent)
    : Widget(parent)
{
}

Size MyWidget::minimumSize() const
{
    return Size(640, 480);
}

bool MyWidget::event(IdealCore::Event *event)
{
    if (event->type() == IdealCore::Event::MapNotify ||
        event->type() == IdealCore::Event::Expose) {
        Painter p(this);
        p.moveTo(10, 10);
        p.lineTo(100, 100);
        p.moveTo(200, 100);
        p.lineTo(300, 300);
        p.moveTo(200, 400);
        p.lineTo(600, 200);
        p.moveTo(200, 160);
        p.lineTo(600, 400);
    }
    return false;
}

class OtherWidget
    : public Widget
{
public:
    OtherWidget(Object *parent);

    virtual Size minimumSize() const;

protected:
    virtual bool event(IdealCore::Event *event);
};

OtherWidget::OtherWidget(Object *parent)
    : Widget(parent)
{
}

Size OtherWidget::minimumSize() const
{
    return Size(100, 100);
}

bool OtherWidget::event(IdealCore::Event *event)
{
    if (event->type() == IdealCore::Event::MapNotify ||
        event->type() == IdealCore::Event::Expose) {
        Painter p(this);
        p.rectangle(0, 0, 100, 100);
    } else if (event->type() == IdealCore::Event::ButtonPress) {
        Painter p(this);
        p.rectangle(0, 0, 100, 100);
        p.moveTo(0, 0);
        p.lineTo(100, 100);
        p.moveTo(100, 0);
        p.lineTo(0, 100);
    } else if (event->type() == IdealCore::Event::ButtonRelease) {
        application()->quit();
    }
    return false;
}

int main(int argc, char **argv)
{
    Application app(argc, argv);

    MyWidget *myWidget = new MyWidget(&app);
    OtherWidget *otherWidget = new OtherWidget(myWidget);
    myWidget->show(Point(0, 0));
    otherWidget->show(Point(100, 200));

    return app.exec();
}
