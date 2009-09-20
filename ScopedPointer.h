/* 
 * File:   ScopedPointer.h
 * Author: mark
 *
 * Created on September 12, 2009, 1:41 PM
 */

#ifndef _SCOPEDPOINTER_H
#define	_SCOPEDPOINTER_H

template<class T>
class ScopedPointer {
public:
    ScopedPointer(T* ptr = new T) : m_ptr(ptr) {}
    ~ScopedPointer() {
        delete m_ptr;
    }
    operator T*() const {
        return m_ptr;
    }
private:
    T *m_ptr;
};

#endif	/* _SCOPEDPOINTER_H */

