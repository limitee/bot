object ConfigForm: TConfigForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #37197#32622#32456#31471#26426
  ClientHeight = 213
  ClientWidth = 542
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 45
    Height = 16
    Caption = #32534#21495#65306
  end
  object Label2: TLabel
    Left = 186
    Top = 24
    Width = 90
    Height = 16
    Caption = #32456#31471#26426#22411#21495#65306
  end
  object Label3: TLabel
    Left = 338
    Top = 64
    Width = 75
    Height = 16
    Caption = #20986#31080#24425#31181#65306
  end
  object Label4: TLabel
    Left = 16
    Top = 105
    Width = 75
    Height = 16
    Caption = #38144#21806#36134#21495#65306
  end
  object Label5: TLabel
    Left = 186
    Top = 105
    Width = 45
    Height = 16
    Caption = #23494#30721#65306
  end
  object Label6: TLabel
    Left = 338
    Top = 105
    Width = 98
    Height = 16
    Caption = 'U'#30462#30331#24405#23494#30721#65306
  end
  object Label7: TLabel
    Left = 16
    Top = 64
    Width = 105
    Height = 16
    Caption = #20113#21830#24425#30418#31471#21475#65306
  end
  object Label8: TLabel
    Left = 32
    Top = 206
    Width = 180
    Height = 16
    Caption = #25903#25345#20986#31080#28216#25103#30340#25353#38190#35774#32622#65306
    Visible = False
  end
  object ButtonSaveConfig: TButton
    Left = 304
    Top = 150
    Width = 197
    Height = 50
    Caption = #20445#23384#37197#32622'(&S)'
    TabOrder = 0
  end
  object EditNo: TEdit
    Left = 64
    Top = 21
    Width = 90
    Height = 24
    MaxLength = 12
    ReadOnly = True
    TabOrder = 1
  end
  object ComboBoxTerminalType: TComboBox
    Left = 288
    Top = 21
    Width = 113
    Height = 24
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 2
    Text = #39640#33150'C8'
    Items.Strings = (
      #39640#33150'C8')
  end
  object ComboBoxLotteryKind: TComboBox
    Left = 424
    Top = 61
    Width = 97
    Height = 24
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 3
    Text = 'TC001'
    Items.Strings = (
      'TC001'
      '')
  end
  object CheckBoxManager: TCheckBox
    Left = 424
    Top = 25
    Width = 97
    Height = 17
    Caption = #35774#20026#31649#29702#26426
    TabOrder = 4
  end
  object ComboBoxCom: TComboBox
    Left = 152
    Top = 61
    Width = 82
    Height = 24
    ItemIndex = 1
    TabOrder = 5
    Text = 'COM3'
    Items.Strings = (
      'COM1'
      'COM3'
      'COM4'
      'COM5')
  end
  object EditAccount: TEdit
    Left = 97
    Top = 102
    Width = 57
    Height = 24
    MaxLength = 3
    TabOrder = 6
  end
  object EditPasswd: TEdit
    Left = 232
    Top = 102
    Width = 81
    Height = 24
    MaxLength = 6
    TabOrder = 7
  end
  object EditUKey: TEdit
    Left = 440
    Top = 102
    Width = 81
    Height = 24
    MaxLength = 8
    TabOrder = 8
  end
  object ValueListEditor: TValueListEditor
    Left = 202
    Top = 206
    Width = 319
    Height = 73
    KeyOptions = [keyDelete, keyUnique]
    ScrollBars = ssVertical
    TabOrder = 9
    TitleCaptions.Strings = (
      #29609#27861#21517#31216
      #33756#21333#25353#38190)
    Visible = False
    ColWidths = (
      193
      120)
  end
  object ButtonUpdateFirmware: TButton
    Left = 48
    Top = 150
    Width = 201
    Height = 50
    Caption = #26356#26032#22266#20214'(&U)'
    TabOrder = 10
    OnClick = ButtonUpdateFirmwareClick
  end
  object OpenDialogFirmware: TOpenDialog
    Ctl3D = False
    DefaultExt = 'bin'
    Filter = 'BOX'#22266#20214'|*.bin'
    Title = #36873#25321#26356#26032#22266#20214#25991#20214
    Left = 16
    Top = 152
  end
end
