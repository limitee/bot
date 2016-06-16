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

	//查找并加载图片，先本地，如没有则去URL下载，然后保存至本地，返回
	void LoadNodeImage(TImage *image, AnsiString terminalType, AnsiString node);

	void DownLoadResource(AnsiString URL, AnsiString fileName);

private:

};



#endif
