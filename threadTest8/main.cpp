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

#include <core/application.h>
#include <core/thread.h>
#include <core/timer.h>

using namespace IdealCore;

static void printResult(iint32 result)
{
    IDEAL_SDEBUG("The result of the heavy math is " << result);
}

class OneClass
    : public Thread
{
public:
    OneClass(Object *parent);

    IDEAL_SIGNAL(resultOfHeavyMath, int);

protected:
    void run();
};

OneClass::OneClass(Object *parent)
    : Thread(parent, NoJoinable)
    , IDEAL_SIGNAL_INIT(resultOfHeavyMath, int)
{
}

void OneClass::run()
{
    // Do expensive math here
    resultOfHeavyMath.emit(1234);
    resultOfHeavyMath.emit(5678);
    resultOfHeavyMath.emit(9123);
    resultOfHeavyMath.emit(4567);
}

class OtherClass
    : public Object
{
public:
    OtherClass(Object *parent);

    IDEAL_SIGNAL(resultOfHeavyMath, int);
};

OtherClass::OtherClass(Object *parent)
    : Object(parent)
    , IDEAL_SIGNAL_INIT(resultOfHeavyMath, int)
{
}

int main(int argc, char **argv)
{
    Application app(argc, argv);

    OneClass *oneClass = new OneClass(&app);
    OtherClass *otherClass = new OtherClass(&app);
    oneClass->resultOfHeavyMath.connect(otherClass->resultOfHeavyMath);
    otherClass->resultOfHeavyMath.connectStatic(printResult);
    oneClass->exec();

    Timer::wait(500);

    return 0;
}
