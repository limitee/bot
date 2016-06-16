#pragma once
#include"Array.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


class IDeviceChannel {
public:
    void init(int connStringType, char* connString);

        /*
     所属组件，连接参数
     */
    void openDevice();

    bool isDeviceOpened();

    /*
     关闭连接
     */
    void closeDevice();

    /**
     * 读取数据
     */
    //zhanglin int read(RingBytesBuffer buffer);

    /**
     * 发送数据
     *
     * @param data
     * @return
     */
    int write(Array<BYTE> data);
};