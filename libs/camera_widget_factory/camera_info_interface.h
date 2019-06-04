#ifndef CAMERA_INFO_INTERFACE_H
#define CAMERA_INFO_INTERFACE_H

#include <QString>

enum Status : int {
    UnavailableStatus,
    UnloadedStatus,
    LoadingStatus,
    UnloadingStatus,
    LoadedStatus,
    StandbyStatus,
    StartingStatus,
    StoppingStatus,
    ActiveStatus
};

enum State : int {
    UnloadedState,
    LoadedState,
    ActiveState
};

enum camera_position : int  {
    UnspecifiedPosition = 0,
    BackFace = 1,
    FrontFace = 2
};

struct camera_info_interface
{
   public:
    camera_info_interface() { }
    virtual ~camera_info_interface() { };

    virtual QString description() const = 0;
    virtual QString deviceName() const = 0;
    virtual bool isNull() const = 0;
    virtual int orientation() const = 0;
    virtual camera_position position() const = 0;
};


#endif // CAMERA_INFO_INTERFACE_H
