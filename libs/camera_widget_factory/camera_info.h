#ifndef CAMERA_INFO_H
#define CAMERA_INFO_H

#include <QString>

#include "camera_info_interface.h"

enum camera_position : int;

struct camera_info
        : public camera_info_interface
{
friend class camera_device;
public:
    camera_info() { }
    virtual ~camera_info();

    virtual QString description() const;
    virtual QString deviceName() const;
    virtual bool isNull() const;
    virtual int orientation() const;
    virtual camera_position position() const;

private:
    QString descrip;
    QString dev_name;
    int     orient;
    int     pos;

};

#endif // CAMERA_INFO_H
