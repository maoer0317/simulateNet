unit UnitMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ieview, imageenview, ievect, ExtCtrls, ComCtrls;

type
  TForm1 = class(TForm)
    pnl1: TPanel;
    imgEnVect: TImageEnVect;
    btnAdd: TButton;
    tmr1: TTimer;
    btnMoveLeft: TButton;
    redt1: TRichEdit;
    btnFocusText: TButton;
    lbl1: TLabel;
    btnDel: TButton;
    procedure btnAddClick(Sender: TObject);
    procedure btnMoveLeftClick(Sender: TObject);
    procedure tmr1Timer(Sender: TObject);
    procedure btnFocusTextClick(Sender: TObject);
    procedure btnDelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.btnAddClick(Sender: TObject);
var
  hobj,n,i:Integer ;
begin
  n:=imgEnVect.ObjectsCount;
  with imgEnVect do
  begin
    hobj := -1; // -1 is the template for new objects
    ObjStyle[hobj]:=[ievsSelectable, ievsMoveable, ievsVisible];
    ObjKind[hobj]:= iekEllipse;
    ObjWidth[hobj] := 10;
    objHeight[hobj] := 10;
    ObjLeft[hobj] := 50+50*n;
    ObjTop[hobj] := 50+50*n;
    objBrushColor[hobj] := clMaroon;
    objBrushStyle[hobj] := bsSolid;
    //MouseInteractVt:=[miPutEllipse];
    hobj:=imgEnVect.AddNewObject ;
    //ShowMessage(IntToStr(imgEnVect.ObjectsCount ));

    lbl1.Caption := '共' + inttostr(n) +'个点：';
    for I := 0 to n-1 do
    begin

        lbl1.Caption :=lbl1.Caption + IntToStr(i);
        ObjBrushColor[i]:=clRed ;
        //Sleep(1000);
        //ObjBrushColor[i]:=clMaroon;

    end;
  end;
end;

procedure TForm1.btnDelClick(Sender: TObject);
var
  str:string ;
  n,i:Integer ;
begin
  str:=InputBox('删除点','删除序号：','0');
  n:=StrToInt(str);
  if n>=imgEnVect.ObjectsCount then
    ShowMessage('big')
  else begin
    imgEnVect.RemoveObject(n);
    lbl1.Caption :='共' + inttostr(imgEnVect.ObjectsCount) +'个点：';
    for I := 0 to imgEnVect.ObjectsCount-1 do
    begin
      lbl1.Caption :=lbl1.Caption + IntToStr(i);
        imgEnVect.ObjBrushColor[i]:=clRed ;
    end;

  end;

end;

procedure TForm1.btnFocusTextClick(Sender: TObject);
var
  str:string ;
  N:Integer;
begin
  with redt1 do
  begin
    //SelStart :=10;
    //SelLength :=20;
    //SelText :='3: focus line';
    str:='3: focus line';
    n:=FindText(str,0,Length(Text),[stWholeWord ]);

    ShowMessage(IntToStr(n));
    SelStart :=70;
    SelLength :=Length(str);
    SelAttributes.Color :=clRed ;
  end;
end;

procedure TForm1.btnMoveLeftClick(Sender: TObject);
var
  hobj:Integer ;
begin
  if imgEnVect.ObjectsCount=0 then
  begin
    ShowMessage('No Objexts');
  end else begin

    tmr1.Enabled :=True;
    tmr1.Interval :=100;

  end;

end;

procedure TForm1.tmr1Timer(Sender: TObject);
var
  hobj:Integer ;
begin
  with imgEnVect do
  begin
    hobj:=GetObjFromIndex(0);

    ObjLeft[hobj]:= ObjLeft[hobj]-10;
  end;


end;

end.
