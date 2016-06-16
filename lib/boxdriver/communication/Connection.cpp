//---------------------------------------------------------------------------

#pragma hdrstop

#include "Connection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include"Connection.h"
#include"Printceptor.h"
#include"FtdiChannel.h"
#include"SendThread.h"
#include"ReceiveThread.h"

Connection::Connection(Printceptor *p)
{
	isOpened = false;
	isOpening = false;
	isClosing = false;
	isClosed = true;
	isConnected = false;
	deviceOpened = false;
	deviceChannel = NULL;
    printceptor =p;
	toBoxOther = new BlockingQueue<BoxMessage>();
}

void Connection::open(int connStringType, char* connString)
{
	if (isOpened || isOpening)
	{
        return;
    }
	isOpening = true;
	deviceChannel = new FtdiChannel();
    deviceChannel->init(connStringType,connString);
    isClosed = false;
    isOpened = true;
    ReceiveThread* readDataThread = new ReceiveThread(this);
    SendThread* sendThread = new SendThread(printceptor);
    isOpening = false;
}

bool Connection::get_isOpened()
{
    return isOpened;
}

bool Connection::get_isConnected()
{
    return isConnected;
}

bool Connection::isDeviceOpened()
{
	if (deviceChannel == NULL) return false;
    deviceOpened = deviceChannel->isDeviceOpened();
    return deviceOpened;
}

void Connection::openDevice()
{
    if (deviceChannel == NULL) return;
    deviceChannel->openDevice();
}

int Connection::write(Array<BYTE> data)
{
    if (deviceChannel == NULL) return Device_Not_Inited;
    return deviceChannel->write(data);
}

int Connection::read(RingBytesBuffer* buffer)
{
    if (deviceChannel == NULL) return Device_Not_Inited;
    return deviceChannel->read(buffer);
}

void Connection::notifyDevicetException(int deviceStatus, bool fromRead)
{
    if (isConnected)
	{
        triggerDisConnected();
     }
}

void Connection::triggerDisConnected()
{
    if (!isConnected) return;
    isConnected = false;
    printceptor->onConnectChanged(false);
}

void Connection::setConnected()
{
    if (!isConnected) {
        isConnected = true;
        //printceptor.queryHardwareInfo();
        printceptor->onConnectChanged(true);
    }
}

void Connection::boxHasMessage()
{
    boxActiveTime = GetTickCount();
}

void Connection::sendMessage(BoxMessage* message)
{
    if (message == NULL) return;
	BlockingQueue<BoxMessage>* whichQueue = toBoxOther;
    //if (message.command.toPrinterReceipt) {
    //    whichQueue = toBoxPrintReceipt;
    //}
	BoxMessage temp_msg = BoxMessage(BoxMessage::APP_HEART_BEAT);
	temp_msg.command = message->command;
	temp_msg.length = message->length;
	temp_msg.seq = message->seq;
	temp_msg.data = message->data;
	whichQueue->Put(temp_msg);
}

void Connection::close()
{
	if (deviceChannel == NULL) return;
	isOpened = false;
	isOpening = false;
	isClosing = false;
	isClosed = true;
	isConnected = false;
	deviceOpened = false;
    return deviceChannel->closeDevice();
}