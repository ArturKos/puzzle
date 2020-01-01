object intro: Tintro
  Left = 396
  Top = 217
  BorderStyle = bsNone
  Caption = 'Intro'
  ClientHeight = 430
  ClientWidth = 1050
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClick = FormClick
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object MediaPlayer1: TMediaPlayer
    Left = -100
    Top = 288
    Width = 29
    Height = 30
    VisibleButtons = []
    Display = Owner
    FileName = 'intro.avi'
    ParentShowHint = False
    ShowHint = False
    TabOrder = 0
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 136000
    OnTimer = Timer1Timer
    Left = 168
    Top = 40
  end
end
