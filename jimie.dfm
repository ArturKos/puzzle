object imie: Timie
  Left = 411
  Top = 164
  ActiveControl = Edit1
  BorderStyle = bsToolWindow
  Caption = 'Jak masz na imi'#281'?'
  ClientHeight = 341
  ClientWidth = 302
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
  object SpeedButton1: TSpeedButton
    Left = 192
    Top = 16
    Width = 89
    Height = 22
    Caption = 'Nowy gracz'
    Flat = True
    OnClick = SpeedButton1Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 16
    Width = 169
    Height = 21
    MaxLength = 20
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 120
    Top = 304
    Width = 73
    Height = 25
    Caption = 'OK'
    Enabled = False
    TabOrder = 1
    OnClick = BitBtn1Click
  end
  object ListBox1: TListBox
    Left = 8
    Top = 56
    Width = 273
    Height = 233
    ItemHeight = 13
    TabOrder = 2
    OnClick = ListBox1Click
  end
end
