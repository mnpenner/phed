/* 
 * File:   Object.h
 * Author: mark
 *
 * Created on September 20, 2009, 1:56 PM
 */

#ifndef _OBJECT_H
#define	_OBJECT_H

#include <QtCore/QObject>

class Object : public QObject {
    Q_OBJECT
    
public:
    Object(QObject *parent = NULL);
    void touch() const;

signals:
    void propertyChanged() const;
};

#endif	/* _OBJECT_H */

