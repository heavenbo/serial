#include <ros/ros.h>
#include <serial/serial.h>

bool serial_open(serial::Serial &sp, uint32_t baudrate, uint32_t timeout, char *tty)
{
    serial::Timeout to = serial::Timeout::simpleTimeout(timeout);
    //设置要打开的串口名称
    sp.setPort(tty);
    //设置串口通信的波特率
    sp.setBaudrate(baudrate);
    //串口设置timeout
    sp.setTimeout(to);

    try
    {
        //打开串口
        sp.open();
    }
    catch (serial::IOException &e)
    {
        ROS_ERROR_STREAM("Unable to open port,shit");
        return false;
    }

    //判断串口是否打开成功
    if (sp.isOpen())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool serial_read(serial::Serial &sp,uint8_t buffer[])
{
    int n=sizeof(buffer);
    n=sp.read(buffer,n);
    if(n!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool serial_write(serial::Serial &sp,const uint8_t buffer[])
{
    int n=sizeof(buffer);
    n=sp.write(buffer,n);
        if(n!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
