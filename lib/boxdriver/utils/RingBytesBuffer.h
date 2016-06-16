//---------------------------------------------------------------------------

#ifndef RingBytesBufferH
#define RingBytesBufferH
//---------------------------------------------------------------------------

#include"Array.h"

class RingBytesBuffer {
    private:
        int capcity;
     /**
     * ��Ϣ����Ļ���������ʹ�õĳ���
     */
        BYTE* buffer;
    /**
     * �´ζ���ʼ������λ��
     */
        int readIndex;
    /**
     * �´�д��ʼ������λ��
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