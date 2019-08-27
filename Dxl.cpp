#include "Dxl.h"

Dxl::Dxl(int a, const char *port)
{
    id = a;
    portHandler = dynamixel::PortHandler::getPortHandler(port);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0);
    portHandler->openPort();
    portHandler->setBaudRate(1000000);
}
int Dxl::enable_torque()
{
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, id, 24, 1, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        packetHandler->getRxPacketError(dxl_error);
    }
}
int Dxl::move(int value)
{
    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, id, 30, value, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        packetHandler->getRxPacketError(dxl_error);
    }
}
int Dxl::disable_torque()
{
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, id, 24, 0, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        packetHandler->getRxPacketError(dxl_error);
    }
}
int Dxl::write_speed(int value)
{
    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, id, 32, value, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        packetHandler->getRxPacketError(dxl_error);
    }
}
int Dxl::set_goal_position(std::map<int, int> a)
{
    dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, 30, 2);
    std::map<int, int>::iterator b;
    for (b = a.begin(); b != a.end(); b++)
    {
        bytearray[0] = DXL_LOBYTE(b->second);
        bytearray[1] = DXL_HIBYTE(b->second);
        dxl_addparam_result = groupSyncWrite.addParam(b->first, bytearray);
        if (dxl_addparam_result != true)
        {
            fprintf(stderr, "[ID:%03d] groupSyncWrite addparam failed", b->first);
            return 0;
        }
    }
    dxl_comm_result = groupSyncWrite.txPacket();
    if (dxl_comm_result != COMM_SUCCESS)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    groupSyncWrite.clearParam();
}
int Dxl::write_sync_speed(std::map<int, int> a)
{
    dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, 32, 2);
    std::map<int, int>::iterator b;
    for (b = a.begin(); b != a.end(); b++)
    {
        bytearray[0] = DXL_LOBYTE(b->second);
        bytearray[1] = DXL_HIBYTE(b->second);
        dxl_addparam_result = groupSyncWrite.addParam(b->first, bytearray);
        if (dxl_addparam_result != true)
        {
            fprintf(stderr, "[ID:%03d] groupSyncWrite addparam failed", b->first);
            return 0;
        }
    }
    dxl_comm_result = groupSyncWrite.txPacket();
    if (dxl_comm_result != COMM_SUCCESS)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    groupSyncWrite.clearParam();
}