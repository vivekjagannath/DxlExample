#ifndef DXL_H
#define DXL_H

#include <dynamixel_sdk/dynamixel_sdk.h>
#include <iostream>
#include <iterator>
#include <map>

class Dxl
{
    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;
    int dxl_comm_result = COMM_TX_FAIL;
    uint8_t dxl_error = 0;
    int id;
    bool dxl_addparam_result = false;
    uint8_t bytearray[2];

public:
    Dxl(int, const char *);
    int enable_torque();
    int move(int);
    int disable_torque();
    int write_speed(int);
    int set_goal_position(std::map<int, int>);
    int write_sync_speed(std::map<int, int>);
};
#endif
