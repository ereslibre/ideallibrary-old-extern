#!/usr/bin/env python

# This file is part of the Ideal Library
# Copyright (C) 2010 Rafael Fernández López <ereslibre@ereslibre.es>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public License
# along with this library; see the file COPYING.LIB.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301, USA.

VERSION    = '1.0'
APPNAME    = 'externTests'
srcdir     = '.'
blddir     = 'build'

def init():
    pass

def set_options(opt):
    opt.tool_options('compiler_cxx')

def configure(conf):
    conf.check_tool('compiler_cxx')
    conf.find_program('pkg-config')
    conf.check_cfg(package = 'idealcore', args = '--cflags --libs')
    conf.check_cfg(package = 'idealgui', args = '--cflags --libs')
    conf.env['CXXFLAGS'] += ['-std=c++0x', '-g']
    conf.sub_config(['ownModulesTest',
                     'pathTest'])

def build(bld):
    bld.add_subdirs(['anyTest',
                     'basicApp',
                     'callAfterTest',
                     'clockTest',
                     'connectionTest',
                     'crossedDeletions',
                     'deleteAfterSignal',
                     'fileTest',
                     'fileTest2',
                     'fileTest3',
                     'getTypeFile',
                     'guiTest',
                     'guiTest2',
                     'idleTest',
                     'leakTest',
                     'localeTest',
                     'mediaPlayer',
                     'mkdirTest',
                     'multiSlotTest',
                     'nonBlockingGUI',
                     'ownModulesTest',
                     'pathTest',
                     'processTest',
                     'protocolHandlerTest',
                     'protocolHandlerTest2',
                     'regExpTest',
                     'reparentTest',
                     'sigpipeTest',
                     'sigsegvTest',
                     'stringTest',
                     'threadTest',
                     'threadTest2',
                     'threadTest3',
                     'threadTest4',
                     'threadTest5',
                     'threadTest6',
                     'threadTest7',
                     'threadTest8',
                     'threadTest9',
                     'threadTest10',
                     'threadTest11',
                     'timerTest',
                     'timerTest2',
                     'uriTest',
                     'virtualTest'])
