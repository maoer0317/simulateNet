object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 648
  ClientWidth = 952
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 16
  object redt1: TRichEdit
    Left = 0
    Top = 41
    Width = 952
    Height = 607
    Align = alClient
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    HideScrollBars = False
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 952
    Height = 41
    Align = alTop
    TabOrder = 1
    object btnStart: TButton
      Left = 96
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Start'
      TabOrder = 0
      OnClick = btnStartClick
    end
    object btnGoon: TButton
      Left = 208
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Go on'
      TabOrder = 1
      OnClick = btnGoonClick
    end
    object btnGo: TButton
      Left = 320
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Go'
      TabOrder = 2
      OnClick = btnGoClick
    end
    object btnStop: TButton
      Left = 528
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Stop'
      TabOrder = 3
      OnClick = btnStopClick
    end
    object btnSuspend: TButton
      Left = 424
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Suspend'
      TabOrder = 4
      OnClick = btnSuspendClick
    end
  end
end