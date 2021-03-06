�
 TAUHTTPPROXYEDITOR 0i  TPF0TauHTTPProxyEditorauHTTPProxyEditorLeftTop� BorderIconsbiSystemMenu BorderStylebsDialogCaptionHTTP proxy settingsClientHeight� ClientWidth!Color	clBtnFaceFont.CharsetANSI_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.Style OldCreateOrder	PositionpoScreenCenterOnClose	FormCloseOnShowFormShowPixelsPerInch`
TextHeight TBevelBevel1LeftTop,WidthHeight{ShapebsFrame  TLabelProxyServerLabLeftTopJWidthGHeightHint�|Provides a space for you to type the address and port number of the proxy server you want to use to gain access to the Internet over HTTP protocol.CaptionProxy server:Enabled  TLabel	BypassLabLeftTopbWidth@HeightHint�  |Provides a space for you to type the Web addresses that do not need to be accessed through your proxy server.

If you want to connect to a computer on your intranet, make sure you type its address in this box. For example, for a computer named Joe1, type [B]Joe1[].

You can use wild cards to match domain and host names or addresses ?for example, [NAVY]www.*.com; 128.*; 240.*; *.mygroup.*; *x*[DEF] and so on.Caption9Do not use proxy server for addresses that beginning withEnabled  TLabelTipLabLeftTop� Width� HeightHint�  |Provides a space for you to type the Web addresses that do not need to be accessed through your proxy server.

If you want to connect to a computer on your intranet, make sure you type its address in this box. For example, for a computer named Joe1, type [B]Joe1[].

You can use wild cards to match domain and host names or addresses ?for example, [NAVY]www.*.com; 128.*; 240.*; *.mygroup.*; *x*[DEF] and so on.Caption)Use semicolons ( ; ) to separate entries.Enabled  TLabelProxyAddressLabLeftNTop8WidthvHeightHint�|Provides a space for you to type the address and port number of the proxy server you want to use to gain access to the Internet over HTTP protocol.CaptionProxy address to use:Enabled  TLabelSeparatorLabLeft� TopJWidthHeightCaption:Enabled  TLabelPortLabLeft� Top8WidthHeightHint�|Provides a space for you to type the address and port number of the proxy server you want to use to gain access to the Internet over HTTP protocol.CaptionPortEnabled  TRadioButtonPreconfigBtnLeft
TopWidthHeightHint  |Specifies to retrive the proxy or direct configuration from the system registry. 

In this case you don't need to specify ANY proxy settings, even if user is behind firewall and requires them. All proxy settings already pre-configured in the Control Panel.Caption0Use pre-confugured settings (from Control Panel)Checked	TabOrder TabStop	OnClickPreconfigBtnClick  TRadioButton	DirectBtnLeft
TopWidthHeightHint_|Specifies whether you want to do NOT use any proxy servers and resolve all host names locally.Caption#Direct connection (don't use proxy)TabOrderOnClickPreconfigBtnClick  TRadioButtonProxyBtnLeft
Top&WidthmHeightHintG  |Specifies to connect to the Internet through a proxy server by using the settings you specify.

A proxy server acts as a security barrier between your internal network (intranet) and the Internet, keeping other people on the Internet from gaining access to confidential information on your internal network or your computer.CaptionUse proxy settingsTabOrderOnClickPreconfigBtnClick  TMemo
BypassMemoLeftToppWidthHeight#Hint�  |Provides a space for you to type the Web addresses that do not need to be accessed through your proxy server.

If you want to connect to a computer on your intranet, make sure you type its address in this box. For example, for a computer named Joe1, type [B]Joe1[].

You can use wild cards to match domain and host names or addresses ?for example, [NAVY]www.*.com; 128.*; 240.*; *.mygroup.*; *x*[DEF] and so on.Color	clBtnFaceEnabled
ScrollBars
ssVerticalTabOrder  TButtonOKBtnLeftxTop� WidthKHeightHint;|Closes the dialog box and saves any changes you have made.CaptionOKDefault	ModalResultTabOrderOnClick
OKBtnClick  TButton	CancelBtnLeft� Top� WidthKHeightHint@|Closes the dialog box without saving any changes you have made.Cancel	CaptionCancelModalResultTabOrderOnClickCancelBtnClick  TEdit
ServerEditLeftLTopFWidth� HeightHint�|Provides a space for you to type the address and port number of the proxy server you want to use to gain access to the Internet over HTTP protocol.AutoSizeColor	clBtnFaceEnabledTabOrder  TEditPortEditLeft� TopFWidth)HeightColor	clBtnFaceEnabledTabOrder   