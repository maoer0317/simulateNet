object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 635
  ClientWidth = 786
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object lbl1: TLabel
    Left = 0
    Top = 616
    Width = 786
    Height = 19
    Align = alBottom
    Caption = 'lbl1'
  end
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 786
    Height = 41
    Align = alTop
    TabOrder = 0
    object btnAdd: TButton
      Left = 32
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Add'
      TabOrder = 0
      OnClick = btnAddClick
    end
    object btnMoveLeft: TButton
      Left = 248
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Move Left'
      TabOrder = 1
      OnClick = btnMoveLeftClick
    end
    object btnFocusText: TButton
      Left = 376
      Top = 9
      Width = 75
      Height = 25
      Caption = 'btnFocusText'
      TabOrder = 2
      OnClick = btnFocusTextClick
    end
    object btnDel: TButton
      Left = 119
      Top = 10
      Width = 75
      Height = 25
      Caption = 'btnDel'
      TabOrder = 3
      OnClick = btnDelClick
    end
  end
  object imgEnVect: TImageEnVect
    Left = 0
    Top = 41
    Width = 786
    Height = 575
    ParentCtl3D = False
    ImageEnVersion = '3.1.2'
    EnableInteractionHints = True
    Align = alClient
    TabOrder = 1
    ExplicitTop = 65
    ExplicitHeight = 594
    object redt1: TRichEdit
      Left = 504
      Top = 40
      Width = 275
      Height = 489
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      Lines.Strings = (
        '0: this is a test'
        '1: dfm.form1.redt1.lines'
        '2: test focusing some text'
        '3: focus line'
        '4: this is the end line ')
      ParentFont = False
      TabOrder = 0
    end
  end
  object tmr1: TTimer
    Enabled = False
    OnTimer = tmr1Timer
    Left = 664
    Top = 24
  end
end
