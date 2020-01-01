object Form4: TForm4
  Left = 445
  Top = 356
  BorderStyle = bsToolWindow
  Caption = 'Najlepsze wyniki'
  ClientHeight = 302
  ClientWidth = 273
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnCanResize = FormCanResize
  PixelsPerInch = 96
  TextHeight = 13
  object TabControl1: TTabControl
    Left = 0
    Top = 0
    Width = 273
    Height = 302
    Align = alClient
    TabOrder = 0
    Tabs.Strings = (
      'Poziom '#322'atwy'
      'Poziom '#347'redni'
      'Poziom trudny')
    TabIndex = 0
    OnChange = TabControl1Change
    object val: TValueListEditor
      Left = 4
      Top = 24
      Width = 265
      Height = 274
      Align = alClient
      Strings.Strings = (
        'aaaaaaaaaa=255 godzin 255 minut 255 sekund')
      TabOrder = 0
      TitleCaptions.Strings = (
        'Gracz'
        'Czas')
      ColWidths = (
        75
        184)
    end
  end
end
