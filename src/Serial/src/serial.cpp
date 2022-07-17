#include <ros/ros.h>
#include <serial/serial.h>
#include <opencv2/opencv.hpp>
unsigned char signal;
int main(int argc, char **argv)
{
    // ros::init(argc, argv, "serial_port");
    // //创建句柄（虽然后面没用到这个句柄，但如果不创建，运行时进程会出错）
    // ros::NodeHandle n;

    //创建一个serial类
    serial::Serial sp;
    //创建timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    char *tty="/dev/ttyACM0";
    sp.setPort(tty);
    //设置串口通信的波特率
    sp.setBaudrate(112500);
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
        return -1;
    }

    //判断串口是否打开成功
    if (sp.isOpen())
    {
        ROS_INFO_STREAM("ttyACM0 is opened.");
    }
    else
    {
        return -1;
    }
    while (1)
    {
        int key_value = cv::waitKey(10);
        if (key_value == 27)
        {
            sp.close();
            ROS_INFO("close");
            break;
        }
        //获取缓冲区内的字节数
        uint8_t buffer[1];
        uint8_t buffer_read[1];
        buffer[0] = 1;
        //读出数据
        buffer_read[1]=0;
        int n=sp.read(buffer_read, 1);
        if (n != 0)
        {
            ROS_INFO("%d", buffer_read[0] & 0xff);
        }
        sp.write(buffer, 1);
        // 关闭串口
    }
    sp.close();
    return 0;
}