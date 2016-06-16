#pragma once
#include"Array.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


class IDeviceChannel {
public:
    void init(int connStringType, char* connString);

        /*
     ������������Ӳ���
     */
    void openDevice();

    bool isDeviceOpened();

    /*
     �ر�����
     */
    void closeDevice();

    /**
     * ��ȡ����
     */
    //zhanglin int read(RingBytesBuffer buffer);

    /**
     * ��������
     *
     * @param data
     * @return
     */
    int write(Array<BYTE> data);
};