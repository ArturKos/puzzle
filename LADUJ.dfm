object Form3: TForm3
  Left = 749
  Top = 102
  BorderStyle = bsToolWindow
  Caption = #321'aduj Gr'#281
  ClientHeight = 276
  ClientWidth = 185
  Color = clBtnFace
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
    Top = 16
    Width = 161
    Height = 21
    TabOrder = 0
  end
  object ListBox1: TListBox
    Left = 8
    Top = 48
    Width = 161
    Height = 177
    ItemHeight = 13
    TabOrder = 1
    OnClick = ListBox1Click
  end
  object BitBtn1: TBitBtn
    Left = 16
    Top = 232
    Width = 41
    Height = 25
    Caption = 'Ok'
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 88
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 3
    OnClick = BitBtn2Click
  end
end
