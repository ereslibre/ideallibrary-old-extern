/*
 * This file is part of the Ideal Library
 * Copyright (C) 2010 Rafael Fernández López <ereslibre@ereslibre.es>
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
#include <core/timer.h>
#include <gui/widget.h>
#include <gui/painter.h>
#include <gui/application.h>

#include <math.h>

using namespace IdealGUI;

class MyWidget
    : public Widget
{
public:
    MyWidget(Object *parent);

    void myTimeout();

    virtual Size minimumSize() const;

protected:
    virtual bool event(IdealCore::Event *event);

private:
    void drawClock();

private:
    ireal m_radius;
    ireal m_line_width;
    bool  m_color;
};

MyWidget::MyWidget(Object *parent)
    : Widget(parent)
    , m_radius(200)
    , m_line_width(2)
    , m_color(false)
{
}

void MyWidget::myTimeout()
{
    m_color = !m_color;
    update();
}

Size MyWidget::minimumSize() const
{
    return Size(640, 480);
}

bool MyWidget::event(IdealCore::Event *event)
{
    if (event->type() == IdealCore::Event::MapNotify ||
        event->type() == IdealCore::Event::Expose) {
        drawClock();
    }
    return false;
}

void MyWidget::drawClock()
{
    Painter p(this);

    if (m_color) {
        p.setSourceRGB(1.0, 0, 0);
    } else {
        p.setSourceRGB(0, 0, 0);
    }

    p.translate(minimumSize().width() / 2.0, minimumSize().height() / 2.0);
    p.setLineWidth(m_line_width);
    p.arc(0, 0, m_radius, 0, 2 * M_PI);
    p.save();

    p.setSourceRGBA(1.0, 1.0, 1.0, 0.8);
    p.fillPreserve();
    p.restore();
    p.strokePreserve();
    p.clip();

    for (int i = 0; i < 12; ++i) {
        double inset = 30;

        p.save();
        p.setLineCap(Painter::RoundLineCap);

        if(i % 3 != 0) {
            inset *= 0.8;
            p.setLineWidth(1.0);
        }

        p.moveTo((m_radius - inset) * cos (i * M_PI / 6.0),
                 (m_radius - inset) * sin (i * M_PI / 6.0));
        p.lineTo(m_radius * cos (i * M_PI / 6.0),
                 m_radius * sin (i * M_PI / 6.0));
        p.stroke();
        p.restore();
    }
#if 0
    // store the current time
    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo = localtime (&rawtime);

    // compute the angles of the indicators of our clock
    double minutes = timeinfo->tm_min * M_PI / 30;
    double hours = timeinfo->tm_hour * M_PI / 6;
    double seconds= timeinfo->tm_sec * M_PI / 30;

    cr->save();
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    // draw the seconds hand
    cr->save();
    cr->set_line_width(m_line_width / 3);
    cr->set_source_rgba(0.7, 0.7, 0.7, 0.8); // gray
    cr->move_to(0, 0);
    cr->line_to(sin(seconds) * (m_radius * 0.9), 
            -cos(seconds) * (m_radius * 0.9));
    cr->stroke();
    cr->restore();

    // draw the minutes hand
    cr->set_source_rgba(0.117, 0.337, 0.612, 0.9);   // blue
    cr->move_to(0, 0);
    cr->line_to(sin(minutes + seconds / 60) * (m_radius * 0.8),
            -cos(minutes + seconds / 60) * (m_radius * 0.8));
    cr->stroke();

    // draw the hours hand
    cr->set_source_rgba(0.337, 0.612, 0.117, 0.9);   // green
    cr->move_to(0, 0);
    cr->line_to(sin(hours + minutes / 12.0) * (m_radius * 0.5),
            -cos(hours + minutes / 12.0) * (m_radius * 0.5));
    cr->stroke();
    cr->restore();

    // draw a little dot in the middle
    cr->arc(0, 0, m_line_width / 3.0, 0, 2 * M_PI);
    cr->fill();
  }

  // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window();
  if(window)
  {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

    if(event)
    {
        // clip to the area indicated by the expose event so that we only
        // redraw the portion of the window that needs to be redrawn
        cr->rectangle(event->area.x, event->area.y,
                event->area.width, event->area.height);
        cr->clip();
    }

    // background gradient
    {
        Cairo::RefPtr<Cairo::LinearGradient> pat = Cairo::LinearGradient::create(0.0, 0.0, 0.0, height);
        pat->add_color_stop_rgb(1.0, 1.0, 1.0, 1.0);
        pat->add_color_stop_rgb(0.0, 0.0, 0.0, 0.0);
        cr->rectangle(0, 0, width, height);
        cr->set_source(pat);
        cr->fill();
    }

    // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
    // the center of the window
    cr->scale(width, height);
    cr->translate(0.5, 0.5);
    cr->set_line_width(m_line_width);

    cr->arc(0, 0, m_radius, 0, 2 * M_PI);
    cr->save();
    cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
    cr->fill_preserve();
    cr->restore();
    cr->stroke_preserve();
    cr->clip();

    //clock ticks
    for (int i = 0; i < 12; i++)
    {
        double inset = 0.05;

        cr->save();
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        if(i % 3 != 0)
        {
            inset *= 0.8;
            cr->set_line_width(0.03);
        }

        cr->move_to(
                (m_radius - inset) * cos (i * M_PI / 6),
                (m_radius - inset) * sin (i * M_PI / 6));
        cr->line_to (
                m_radius * cos (i * M_PI / 6),
                m_radius * sin (i * M_PI / 6));
        cr->stroke();
        cr->restore(); /* stack-pen-size */
    }

    // store the current time
    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo = localtime (&rawtime);

    // compute the angles of the indicators of our clock
    double minutes = timeinfo->tm_min * M_PI / 30;
    double hours = timeinfo->tm_hour * M_PI / 6;
    double seconds= timeinfo->tm_sec * M_PI / 30;

    cr->save();
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    // draw the seconds hand
    cr->save();
    cr->set_line_width(m_line_width / 3);
    cr->set_source_rgba(0.7, 0.7, 0.7, 0.8); // gray
    cr->move_to(0, 0);
    cr->line_to(sin(seconds) * (m_radius * 0.9), 
            -cos(seconds) * (m_radius * 0.9));
    cr->stroke();
    cr->restore();

    // draw the minutes hand
    cr->set_source_rgba(0.117, 0.337, 0.612, 0.9);   // blue
    cr->move_to(0, 0);
    cr->line_to(sin(minutes + seconds / 60) * (m_radius * 0.8),
            -cos(minutes + seconds / 60) * (m_radius * 0.8));
    cr->stroke();

    // draw the hours hand
    cr->set_source_rgba(0.337, 0.612, 0.117, 0.9);   // green
    cr->move_to(0, 0);
    cr->line_to(sin(hours + minutes / 12.0) * (m_radius * 0.5),
            -cos(hours + minutes / 12.0) * (m_radius * 0.5));
    cr->stroke();
    cr->restore();

    // draw a little dot in the middle
    cr->arc(0, 0, m_line_width / 3.0, 0, 2 * M_PI);
    cr->fill();
  }
#endif
}

int main(int argc, char **argv)
{
    Application app(argc, argv);

    MyWidget *myWidget = new MyWidget(&app);
    myWidget->show(Point(0, 0));

    IdealCore::Timer *timer = new IdealCore::Timer(&app);
    timer->setInterval(1000);
    IdealCore::Object::connect(timer->timeout, myWidget, &MyWidget::myTimeout);
    timer->start(IdealCore::Timer::NoSingleShot);

    return app.exec();
}
