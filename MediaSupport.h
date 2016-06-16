//---------------------------------------------------------------------------

#ifndef MediaSupportH
#define MediaSupportH

#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------


class CMediaSupport
{
public:
	CMediaSupport();
	virtual ~CMediaSupport();

	void SoundOK();
	void SoundErrorLocal();
	void SoundErrorNet();
	void SoundRemind();

	//���Ҳ�����ͼƬ���ȱ��أ���û����ȥURL���أ�Ȼ�󱣴������أ�����
	void LoadNodeImage(TImage *image, AnsiString terminalType, AnsiString node);

	void DownLoadResource(AnsiString URL, AnsiString fileName);

private:

};



#endif
