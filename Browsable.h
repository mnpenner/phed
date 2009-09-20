/* 
 * File:   Browsable.h
 * Author: mark
 *
 * Created on September 7, 2009, 10:52 PM
 */

#ifndef _BROWSABLE_H
#define	_BROWSABLE_H

#include <QtPropertyBrowser/QtVariantPropertyManager>

class Browsable : public QObject {
    Q_OBJECT
    
public:
    void touch();

signals:
    void propertyChanged() const;
};

#endif	/* _BROWSABLE_H */

