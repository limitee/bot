//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include "RingBytesBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


RingBytesBuffer::RingBytesBuffer(int capcity)
{
	readIndex = 0;
    writeIndex = 0;
    this->capcity=capcity;
    buffer = new BYTE[capcity];
}

int RingBytesBuffer::get_capcity()
{
    return capcity;
}

int RingBytesBuffer::readable()
{
	return (writeIndex>=readIndex)?(writeIndex-readIndex):(writeIndex+capcity-readIndex);
}

int RingBytesBuffer::writable()
{
    return capcity-readable();
}

void RingBytesBuffer::push(BYTE b)
{
	if (writable() < 1) {
		return;
    }
    buffer[writeIndex]=b;
	writeIndex++;
	if(writeIndex>=capcity)writeIndex=0;
}

void RingBytesBuffer::push(Array<BYTE> data)
{
	push(data.GetPt(), 0, data.GetSize());
}

void RingBytesBuffer::push(BYTE data[], int offset, int length)
{
	for(int i = 0;i<length;i++)
	{
		push(data[i]);
	}
}

BYTE RingBytesBuffer::pop()
{
	BYTE temp = buffer[readIndex];
	readIndex++;
	if(readIndex>=capcity)readIndex=0;
	return temp;
}

Array<BYTE> RingBytesBuffer::pop(int len)
{
	int actual_len = len;
	if(len > readable())actual_len = readable();
	BYTE* data = new BYTE[actual_len];
	for(int i = 0;i< actual_len;i++)
	{
		data[i] = pop();
	}
	Array<BYTE> return_array = Array<BYTE>(actual_len,0);
	memcpy(return_array.GetPt(),data,actual_len);
	delete []data;
    return return_array;
}

Array<BYTE> RingBytesBuffer::popAll()
{
	int actual_len = readable();
	BYTE* data = new BYTE[actual_len];
	for(int i = 0;i< actual_len;i++)
	{
		data[i] = pop();
	}
	Array<BYTE> return_array = Array<BYTE>(actual_len,0);
	memcpy(return_array.GetPt(),data,actual_len);
	delete []data;
    return return_array;
}

void RingBytesBuffer::clear()
{
	readIndex = 0;
    writeIndex = 0;
}

BYTE RingBytesBuffer::peek(int relativeIndex)
{
	return buffer[(readIndex+relativeIndex)%capcity];
}

void RingBytesBuffer::back(int i)
{
	if(readIndex<i)
	{
		readIndex = capcity+readIndex-i;
	}
	else
	{
		readIndex = readIndex-i;
	}
}