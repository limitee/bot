//---------------------------------------------------------------------------

#ifndef RingBytesBufferH
#define RingBytesBufferH
//---------------------------------------------------------------------------

#include"Array.h"

class RingBytesBuffer {
    private:
        int capcity;
     /**
     * 消息命令的缓冲区，和使用的长度
     */
        BYTE* buffer;
    /**
     * 下次读开始的索引位置
     */
        int readIndex;
    /**
     * 下次写开始的索引位置
     */
        int writeIndex;

    public:
        RingBytesBuffer(int capcity);

        int get_capcity();

        int readable();

		int writable();

		void push(BYTE b);

		void push(Array<BYTE> data);

		void push(BYTE data[], int offset, int length);

		BYTE pop();

		Array<BYTE> pop(int len);

		Array<BYTE> popAll();

		void clear();

		BYTE peek(int relativeIndex);

		void back(int i);
};

#endif
