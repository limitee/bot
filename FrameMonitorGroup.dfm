object FrameMonitor: TFrameMonitor
  Left = 0
  Top = 0
  Width = 451
  Height = 305
  HorzScrollBar.Visible = False
  VertScrollBar.Smooth = True
  VertScrollBar.Tracking = True
  VertScrollBar.Visible = False
  Align = alClient
  AutoSize = True
  DockSite = True
  DragKind = dkDock
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBtnText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  OnMouseWheel = FrameMouseWheel
  OnResize = FrameResize
  object CategoryPanelGroup: TCategoryPanelGroup
    Left = 0
    Top = 0
    Height = 305
    VertScrollBar.Tracking = True
    BevelInner = bvLowered
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBtnText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    HeaderAlignment = taRightJustify
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -16
    HeaderFont.Name = 'Tahoma'
    HeaderFont.Style = [fsBold]
    HeaderHeight = 32
    Images = ImageListTerminal
    ParentFont = False
    TabOrder = 0
  end
  object ImageListTerminal: TImageList
    Height = 32
    ShareImages = True
    Width = 32
    Left = 304
    Top = 208
    Bitmap = {
      494C010102001C01300120002000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000800000002000000001002000000000000040
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FEFEFE01FEFEFE01FDFDFD02FDFDFD02FDFDFD02FEFEFE01FEFEFE01FEFE
      FE01000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FEFEFE01FEFEFE01FEFEFE01FDFEFE02FEFEFE01FEFEFE010000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FDFDFD02FAFAFA06F7F7F70BF4F4F310F3F3
      F212F2F1F016F1F1F019F1F0EF1CF1F1EF1DF1F0EF1EF2F1F01BF2F2F118F3F3
      F215F4F4F311F5F5F40FF8F8F70AFBFBFB05FEFEFE0100000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FEFEFE01FAFCFA05F5FAF70AF1F9F40EEDF8
      F312EBF8F414E8F9F617E6FAF819E4FAF91BE4FAF91BE6FAF819E9F9F716ECF9
      F613EEF8F411F2F9F50DF6FAF809FBFDFB04FEFEFE0100000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FCFCFC04F6F6F60CEEEEEE17E5E4E325DBD9D735D3D1CE43CECB
      C84FCECBC658CDCAC464CAC8C072C8C7BE7BC8C8BF7BCACAC273CECEC864D1D1
      CC56D2D2CD4BD7D6D23FDDDCD932E7E6E423EFEFEE16F7F6F60BFCFCFC030000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FCFDFC03F4F9F50BEAF4EC15DDEEE222CEE7D731C1E4D23EB7E4
      D348ADE7DA52A1EAE25E94ECE86B8AEDEA758AEDEB7593EDE96CA1ECE55EAFE9
      DE50B9E6D746C4E6D63BD1E9DB2EDFEFE420EBF5ED14F5F9F60AFCFDFC030000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F9F9F908F1F1F113E4E3E226D2D0CF40BCB9B760AAA6A27CA19C968F978F
      85AC968C7DCA99907CE298957DF0999A82F69C9C88F69E9E8CEF9E9E8EDF9F9F
      8EC5A5A397A1AAA69D89B0ADA576BFBDB75CD3D2CE3DE4E4E224F1F1F012F9F9
      F907000000000000000000000000000000000000000000000000000000000000
      0000F8FBF807EEF6EF11DCECE023C4E0CB3BA6D2B45989C7A17677C4A08858C2
      A1A738C99FC71FD592E010DA85EF08DD7EF70AE084F511E093EE22DCA8DD3ED2
      B2C163CCAF9C7EC9A8818FCBA870A9D4B756C7E2CE38DEEEE221EEF6EF11F9FB
      F906000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FCFC
      FC04F3F3F310E4E3E325D0CECE42B4B1AF69938D8998797168D47E7163F88174
      61FF7B6F59FF746A53FF716D58FF757562FF7E7E71FF8B8B7DFF9C9C8BFFACAB
      97FFAEA892FF98947FF0858674C795978C8EB2B4AD65CFD0CC3FE5E6E421F3F3
      F20FFBFBFB04000000000000000000000000000000000000000000000000FBFC
      FB04EFF6F010DEEDE121C2DFC93D9CCBA8636DB384922EAE6DD107C360F800C9
      50FF00BA41FF00AA3BFF00A63AFF00AB3CFF02B641FF02C748FF02E053FF02F7
      69FF02F983FF10DD9AEF3CBA85C377B98B88A0CEAC5FC5E1CC3ADFEEE220F0F7
      F10FFCFDFC030000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FAFA
      F907F2F2F112E2E1E128CBC9C8488D8784A9877D75FD73685DFF4D4235FF453B
      2BFF473D2CFF4E4535FF524E3FFF5D5D51FF66665FFF6C6C63FF747467FF7E7F
      6DFF8C8F7AFFA3AC94FFA0AD92FF88997CF3929B8E96C8CBC645DFE1DF27EFF0
      EF13FBFBFB05000000000000000000000000000000000000000000000000F9FB
      F906EFF6F010DAEBDD25BDDCC4425AB37EA503D762FC00BC47FF008632FF0077
      2BFF007529FF00762AFF00792BFF068334FF0A8C3AFF09933EFF099F42FF09AF
      49FF09CC54FF09FC72FF0AFFADFF12E7BEF26DC39292BFDDC640DCECDF23EEF6
      EF11FBFCFB040000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FDFD
      FD02F6F6F60CEBEBEA1BDBDBDA30887E78F06C625BFF3D332AFF342B1FFF362D
      20FF3C3529FF443F34FF4B483FFF65655FFF696966FF6D6D69FF707268FF6E77
      66FF71816AFF7C9276FF91AE8EFF95B391FF8CAB86FFD4D8D434E9EBE91AF6F6
      F60BFEFEFE01000000000000000000000000000000000000000000000000FEFE
      FE01F3F8F40CE6F1E819D3E7D72C10D269EF00B544FF00732BFF006425FF0064
      24FF006825FF006C26FF007028FF12813CFF13873EFF128D42FF129346FF129B
      4AFF12AC53FF12C95FFF12F473FF13FFBBFF0FFDECFFCEE5D231E8F2EA17F5F9
      F60AFEFEFE010000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FDFDFD02F9F9F907E1E0DF2A82776FFF4A4238FF332A21FF2D261CFF322D
      24FF3A372FFF43413CFF51514EFF747474FF767677FF777978FF737C75FF6D7F
      6FFF718C72FF709371FF7FA780FF94BF96FF8DB88DFFDCE0DC2BF7F8F709FEFE
      FE01000000000000000000000000000000000000000000000000000000000000
      0000FEFEFE01F9FBF906D7EADD2800D163FF008530FF006525FF005E22FF0062
      22FF006825FF006E28FF04782FFF1D8B48FF1C8F4AFF1C944DFF1C9950FF1C9D
      54FF1CAF5DFF1CBA62FF1CD970FF1DFF96FF17FEEBFFD7EBDC28F7FAF708FEFE
      FE01000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CECBC75B81766AFF8D8378FF544B41FF322B22FF302B23FF3633
      2CFF3E3E3BFF454948FF5E6364FF808585FF818687FF7F8987FF7C8D81FF7D97
      82FF799B7DFF76A079FF82B085FF9CCD9EFF90C190FF95AC9697000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A4E4C85B00C558FF00DE66FF009245FF006523FF006223FF0067
      24FF007028FF00762CFF0D853CFF299855FF279D59FF27A05BFF27A55FFF27B3
      67FF27BB6BFF27C070FF28D87CFF2AFE9CFF1CFDE7FF67D2A698000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FAFAFA06898271FB544838FF615749FF8F877AFF3A3328FF37342BFF3C3C
      36FF444745FF4B5152FF6B7373FF8F9595FF8F9897FF8C9A94FF8FA494FF8EAB
      90FF88AC89FF86B086FF9BC99AFFAFDFAEFF8EBE8CFF79AA76FFB0C9AE840000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F9FBFA0604C55DFB007F2DFF009B3BFF00E27FFF006C26FF006925FF006E
      29FF00762DFF007E2FFF179048FF35A463FF34A866FF34AD6AFF34BA73FF34C3
      79FF34C67BFF33CC80FF3DE591FF43FFB5FF1AFAE9FF00F99FFF7CEED1830000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DADAD73697947DFF736C58FF665D4AFF97907FFF666254FF3D3D32FF4346
      3EFF4C524EFF515858FF7A8181FF9FA6A6FF9FA9A6FFA3B2A7FFA3B8A3FF9EBB
      9BFF9BBD95FF9BC194FFC4EDBDFFC3EDBCFF8EB987FF739F6CFF89B082E10000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CAE4DB350ECC5AFF15944AFF009C46FF00E77FFF00A764FF006F26FF0075
      2BFF007F30FF008534FF219C55FF41AF71FF40B575FF40C27EFF40CB84FF40CF
      89FF40D28BFF3DDB90FF60F5B0FF57FFD1FF13F8E5FF00E87CFF1EF3C7E10000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EFEFEE16ABAB95FFA9A68EFF8E8872FF918B76FF9A9985FF4E5140FF4D53
      46FF525A52FF575E5CFF878E8EFFB4BBBBFFB8C1BAFFB8C5B6FFB6C8AEFFB4CB
      A9FFB2CEA4FFC2DFB3FFE4FDD5FFDBF8CDFF83A777FF81A476FF93B187E30000
      0000000000000000000000000000000000000000000000000000000000000000
      0000E9F3EF1615E37EFF3ABA74FF14BA6CFF00D978FF00EAB5FF00822FFF007F
      31FF008635FF008D3AFF26A760FF4DC183FF4CCA89FF4CD08EFF4CD593FF4CDA
      96FF4BDD9BFF59EAA9FF7AFDC9FF6EFFEFFF00F1C8FF00EF89FF1DF7D0E20000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000B1B1A3A7E3E3CCFFD3D3B8FF9B9A7EFFA1A489FF6F765DFF5A63
      51FF60685DFF656C66FF919894FFC8CEC9FFCAD0C6FFCCD4C2FFCED7BFFFCDD9
      BCFFCEDDB9FFF6FAE8FFF0F8DFFFE1EAD1FF88A077FF95AF86FFBECCB58C0000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000058D9B0A756F2ADFF54DCA2FF03DE8CFF00F0B5FF00AD62FF0092
      37FF009940FF00A145FF24B868FF5ACE92FF58D497FF58DA9CFF58DEA1FF58E2
      A6FF55E8A9FF90F9CCFF7CFFDCFF6BFEFFFF00EDA1FF00FFBFFF73F6D88C0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FAFAFA07B9B9A5E7FFFFE9FFDFDFC1FFA2A384FF81876AFF636B
      53FF636D5BFF687265FF899087FFD8DDD4FFDBDED3FFE0E0D4FFE4E5D3FFE8E8
      D4FFEEEED9FFF9FAEBFFFDFEF5FFBFC4AEFFA0AB8DFFA6B296DAFDFDFD020000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000F8FBFA073BDFBEE77BF9CCFF51F1C1FF00F2AFFF00C67DFF009E
      3FFF00A145FF00A94BFF17BA65FF67D8A0FF64DCA3FF64E2A8FF64E5ACFF63EB
      B2FF60F5B8FF7BFED4FF9BFFF5FF30FAEEFF00FCAAFF25F3D0DAFDFEFE020000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000DFDFDA37DADACBFFFFFFF8FFCACBA8FF949A78FF707C
      5BFF69755BFF6E7964FF757E6EFFE3E7DBFFEAEAE1FFEEEEE5FFF2F2ECFFF7F7
      F3FFFDFDFBFFFDFDF7FFF1F1EAFFA6A69AFFAAAA99FBF1F1EF20000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C8ECE0375BF3E5FF97FDEAFF28FDCAFF00E38AFF00B5
      4EFF00AC4DFF00B153FF00BA5BFF70DEAAFF6FE3AEFF6FE7B2FF6EEDB8FF73F6
      C2FFACFEE0FF72FFEAFF5EFEFFFF00F7BCFF04F7D4FBDFFAF220000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000BCBCAC83F8F8EBFFFFFFEDFFB2B990FF8F9B
      75FF798866FF758468FF78836EFFC8CDBEFFF8F8F0FFFAFAF9FFFDFDFDFFFEFE
      FEFFFFFFFFFFFFFFFFFFB8B8B8FFABABABFFDFDFDD5600000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007CDBC28393FFFFFF9BFEF3FF0CFFAAFF00E4
      66FF00C659FF00C15CFF00C462FF4CDC98FF7AE9B9FF77F0BDFF7BF9C6FFC6FE
      EAFFAEFFF5FFCCFFFFFF1DF8DBFF00FBD4FFAAF9E35500000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B3B39BA3E8E8CFFFCAD0AAFFA0AE
      82FF9AAB82FF91A280FF919E84FFA2A897FFFEFEFDFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFC5C5C5FFA7A7A7FFCCCCCC8C0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000060D8BCA384FAF8FF40FFEDFF00FF
      A1FF00F979FF00EC74FF00E876FF07EC84FF7FF9C4FF81FDCDFFB7FEE9FFC4FF
      FBFFCCFFFFFF3CFAEAFF00F8D2FF73F6D88C0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D9DACE44AEB392AC96A4
      77EA9DB083FF9BB088FF9FAF91FFA4AD9BFFB7B8B3FFEDEDEDFFFCFCFCFFECEC
      ECFFB7B7B7FFACACACD8DEDEDE56000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000BBEADB4453E1C8AC16E6
      CDE900FFDEFF00FFB9FF00FFACFF00FFB1FF0EFFC9FF67FFF0FF80FFFEFF7BFF
      FFFF21F6D8FF27EEC2D8AAF8E355000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FCFD
      FC03BDC7B17A8B9F77F8A0B493FFB1BEAAFFBDBFBAFFB5B5B6FFA5A5A5FBC8C8
      C88DF5F5F5120000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FCFD
      FD0385E7CE7A07E8D1F816EFC1FF21F1B3FF20F4BBFF11F6D0FF04F4D9FB74F4
      D68BEDFAF6120000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2C0A2A2A7BF94FF91A785FF8B9C86FF9AA39CFFB8BAB9FFD1D1D1FFCECE
      CEA6000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000069E1B5A130E38DFF1BD77FFF0ED57FFF0EDF8BFF1BF0A2FF31FBC5FF65F7
      D2A6000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5BE
      A39D9BAF83FF6B8259FF698160FF778C74FF89998DFF939D9CFFA8ACACFFD2D2
      D2FFD4D3D3A10000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006CDE
      B49D2AD37DFF05B963FF00BE68FF02C975FF0AD485FF0ADB90FF0FEAA1FF31FE
      D6FF6BFDDAA10000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E2E2DE2FA6B1
      8DFF6A7C57FF647A57FF6A8265FF859E88FF8DA598FF96A9A4FFACBDBCFFB5C1
      C2FFCDD8D5FFE9EBEA3200000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D0ECE22F2FD1
      7FFF05AF59FF00B45EFF00BF68FF17CE82FF19D78DFF17DD96FF2BE6AAFF26F3
      BCFF39FEF1FFCDFAEC3200000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BDBEB38D8F98
      80FF637256FF667A5FFF768E76FF92AC99FF95B2A4FF99B4ABFFBCD6CFFFC2DA
      D1FFCEE1DAFFC8D0CB9500000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007BD9B68D1FBC
      67FF00A852FF00B35DFF0DC170FF29D18AFF27D994FF25DF9CFF4BE9B6FF44F7
      C4FF4BFFF0FF75FBDB9500000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B5B5B0B28186
      79FF66705FFF687866FF899D8CFFA1BBACFFA2BFB2FFA2C1B5FFD1ECE4FFD5EA
      E5FFE9F9F4FFB9C3BFBF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000061D1A2B214B0
      5AFF00A550FF00B15AFF20C57AFF3BD492FF3ADB9BFF37E0A1FF6DECC2FF63FD
      D0FF7EFFECFF56FBDDBF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B7B7B8AF8788
      85FF696D68FF6C756CFF98A99CFFB4C9BDFFB1CCC0FFB2CEC3FFC3DCD4FFC6DA
      D3FFD1E0DAFFB8C0BCBA00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000063D3A3AF16B1
      5BFF00A34EFF00AF57FF2EC67FFF4DD69AFF4CDBA0FF4BE1A9FF52F4BBFF51FB
      C4FF5FFFDFFF5AF9DBBA00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C07FABAB
      ABFF737473FF737573FFA0A9A3FFCAD9D0FFC9DED2FFCCE4D8FFFEFFFFFFEAF3
      F0FFEEF4F4FFC5C9C78500000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000086D7B87F29CF
      71FF00A950FF00AE55FF2FC47EFF60DAA4FF5DE4ACFF5CEFB4FFC5FAE7FF97FA
      D7FFA2FFF5FF80F6D78500000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000EEEEEE19B4B4
      B4FF878787FF7C7C7CFF9A9B9AFFE8EEE8FFE0EEE2FFECF5EEFFFCFDFBFFFAFE
      FCFFC5CCC8FFEFF0F01C00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E7F2EE1832D3
      81FF0AB95BFF00B859FF18C973FF73E4B0FF6CE9B3FF97F2CCFFC5F9E5FFBAFC
      E3FF4AF7D8FFE3F9F21C00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      C670BDBDBDFF8C8C8CFF7D7D7DFFDCDCDAFFF6F9EFFFF3FAEEFFFAFEF8FFF1F2
      F0FFCCCFCC760000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000095DA
      C06F34DC82FF0CC061FF00BC5CFF62DCA2FF7EE7B8FF7AEBBBFF82F7C6FF78FC
      D9FF8DF0D4760000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C8C8C86BB7B7B7FCBCBCBDFFB0B0AFFFF2F2F0FFFFFFFFFFDCDBD9FDD1D2
      CE6F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099DDC46A31D989FC2CE485FF20DE80FF72F2B6FF96FDD2FF6DEDC5FD95ED
      D26F000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000F5F5F50FC7C7C76EC0C0C0A1C1C1C1A1CACAC970F5F5F4110000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000F0F7F40F95DDC46D6FDDB4A06CDEB6A192E4C96FEFF8F5100000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000080000000200000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFFFFFFFFF0000000000000000
      FFF00FFFFFF81FFF0000000000000000FE00007FFE00007F0000000000000000
      F800001FF800001F0000000000000000F000000FF000000F0000000000000000
      E0000007E00000070000000000000000E0000007E00000070000000000000000
      E0000007E00000070000000000000000F000000FF000000F0000000000000000
      F800003FF800003F0000000000000000F000001FF000001F0000000000000000
      F000001FF000001F0000000000000000F000001FF000001F0000000000000000
      F800001FF800001F0000000000000000F800001FF800001F0000000000000000
      FC00003FFC00003F0000000000000000FE00007FFE00007F0000000000000000
      FF0000FFFF0000FF0000000000000000FF8001FFFF8001FF0000000000000000
      FFE007FFFFE007FF0000000000000000FFF00FFFFFF00FFF0000000000000000
      FFE007FFFFE007FF0000000000000000FFC003FFFFC003FF0000000000000000
      FFC003FFFFC003FF0000000000000000FFC003FFFFC003FF0000000000000000
      FFC003FFFFC003FF0000000000000000FFC003FFFFC003FF0000000000000000
      FFC003FFFFC003FF0000000000000000FFE007FFFFE007FF0000000000000000
      FFF00FFFFFF00FFF0000000000000000FFF81FFFFFF81FFF0000000000000000
      FFFFFFFFFFFFFFFF000000000000000000000000000000000000000000000000
      000000000000}
  end
end
