/* 
 * File:   Browsable.cpp
 * Author: mark
 * 
 * Created on September 7, 2009, 10:52 PM
 */

#include <qt4/QtCore/qmetaobject.h>

#include "Browsable.h"

void Browsable::touch() {
    emit propertyChanged();
}