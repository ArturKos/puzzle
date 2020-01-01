object Form2: TForm2
  Left = 394
  Top = 230
  Width = 180
  Height = 297
  BorderStyle = bsSizeToolWin
  Caption = 'Zapisz Gr'#281
  Color = clBtnFace
  TransparentColor = True
  TransparentColorValue = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 153
    Height = 21
    TabOrder = 0
    Text = 'Edit1'
  end
  object ListBox1: TListBox
    Left = 8
    Top = 40
    Width = 153
    Height = 169
    ItemHeight = 13
    Items.Strings = (
      'ffffff')
    Sorted = True
    TabOrder = 1
    OnClick = ListBox1Click
  end
  object BitBtn1: TBitBtn
    Left = 24
    Top = 224
    Width = 57
    Height = 25
    Caption = 'Ok'
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 96
    Top = 224
    Width = 57
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 3
    OnClick = BitBtn2Click
  end
end
