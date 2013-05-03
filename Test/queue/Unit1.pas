unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, UnitEvents ,Generics.Collections;

const
    clientMax=3;

type
  TForm1 = class(TForm)
    redt1: TRichEdit;
    pnl1: TPanel;
    btnStart: TButton;
    btnGoon: TButton;
    btnGo: TButton;
    btnStop: TButton;
    btnSuspend: TButton;
    procedure FormCreate(Sender: TObject);
    procedure btnStartClick(Sender: TObject);
    procedure btnStopClick(Sender: TObject);
    procedure btnGoonClick(Sender: TObject);

    procedure QueueNotify(Sender: TObject; const Item: EventRec ;
          Action: TCollectionNotification);
    procedure fillEvent(OccTime, Dur,NName:Integer; GrphNName:string; eve:NET_EVENTS);
    function getRandom(range:Integer):Integer ;
    procedure btnGoClick(Sender: TObject);
    procedure btnSuspendClick(Sender: TObject);
  private
    { Private declarations }
    clientsCount:Integer;
    clientStates:array [0..clientMax-1] of NET_EVENTS ;
    lastTime:array [0..clientMax-1] of Integer;
    sendTimes,recvTimes:array [0..clientMax-1] of Integer ;
    //serState:NET_EVENTS ;
    EventTime:Integer ;
    bSuspend:Boolean ;
    EventsQueue: TList<EventRec>;

    procedure processQueue();
    procedure newClient(cliIndex:Integer);
    function getNoEventClient():integer;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.QueueNotify(Sender: TObject; const Item: EventRec ;
      Action: TCollectionNotification) ;
var
  str:string;
begin
  case Action of
    cnAdded:begin
      str:='a new event added: ';
    end;
    cnRemoved:
      str:='a event removed: ';
    cnExtracted:
      str:='a event extracted:';
  end;
  with Item do
  begin
    str:=str + ' OccurTime ' + IntToStr(OccurTime) + ',' +
               ' GoTime ' + IntToStr(GoTime) + ',' +
               ' Event ' +  IntToStr(Ord(event)) + ','  +
               ' ClinetNo ' + IntToStr(nodeNo) +',' +
               ' GraphaNodeName '+ graphNodeName;
  end;
  //redt1.Lines.Add('Notify  '+str);
end;

function TForm1.getNoEventClient: integer;
var
  i:Integer;
begin
  i:=0;
  while clientStates[i]<>EVENT_NONE  do
    Inc(i);
  Result :=i;
end;

function TForm1.getRandom(range: Integer): Integer;
{产生一个1到range的随机数，用作事件的持续时间}
begin
  Randomize ;
  Result :=Random(range)+1;
end;

procedure TForm1.btnGoClick(Sender: TObject);
begin
  bSuspend  :=False ;
  btnGoon.Click ;
end;

procedure TForm1.btnGoonClick(Sender: TObject);
begin
  processQueue ;
end;

procedure TForm1.btnStartClick(Sender: TObject);
begin
  btnStart.Enabled:=False ;
  fillEvent(EventTime,1,-1, '', SERV_INI_SOCK );
  processQueue  ;
end;

procedure TForm1.btnStopClick(Sender: TObject);
begin
  EventTime :=0;
  EventsQueue.Clear ;
  redt1.Clear ;
end;

procedure TForm1.btnSuspendClick(Sender: TObject);
begin
  bSuspend:=True  ;
end;

procedure TForm1.fillEvent(OccTime, Dur,NName:Integer; GrphNName:string ; eve:NET_EVENTS);
var
  AEventRec, inQueue :EventRec ;
  eventIndex: Integer ;
begin
  with AEventRec do
  begin
    OccurTime :=OccTime ;
    //Inc(EventTime);
    GoTime :=Dur ;
    Event :=eve ;
    NodeNo:=NName ;
    GraphNodeName:=GrphNName ;
  end;

  eventIndex :=0;
  with EventsQueue do
  begin
    while (eventIndex <Count)  do
    begin
      inQueue:=Items[eventIndex];
      if AEventRec.OccurTime >= inQueue.OccurTime then
        Inc(eventIndex)
      else
        break;
    end;
    Insert(eventIndex, AEventRec);
  end;
  //EventsQueue.Add(AEventRec);
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  i:Integer;
begin
  clientsCount :=0;
  EventTime :=0;
  EventsQueue:=TList<EventRec>.Create();
  EventsQueue.OnNotify := QueueNotify;
  bSuspend  :=True  ;
  for I := 0 to clientMax-1 do begin
    clientStates[i]:=EVENT_NONE ;
    lastTime[i]:=0;
    sendTimes[i]:=0;
    recvTimes [i]:=0;
  end;
end;

procedure TForm1.newClient(cliIndex: Integer);
var
  graNodeName:string;
begin
  graNodeName :='Client' + IntToStr(cliIndex);
  fillEvent(EventTime,1,cliIndex  ,graNodeName ,CLI_INI_SOCK);
  clientStates[cliIndex]:=CLI_INI_SOCK ;
  Inc(clientsCount);
  processQueue ;
end;

procedure TForm1.processQueue;
var
  aEvent:EventRec ;
  n,i,nram:Integer ;
  str,spaces:string;   //spaces:缩进字符串
begin
  repeat
  begin
    if EventsQueue.Count >0 then
    begin
      aEvent:=EventsQueue.First;
      //队首元素时间与Event计时相同时，执行队列事件；
      //不同时，可能产生新的client，但如果客户端已到最大值，也不会去产生新的client
      //上面两个条件都不满足，产生1～5随机数，
      //随机数大于clientCount产生新的client

      spaces:='    ';
      if (aEvent.OccurTime=EventTime) or (clientsCount=clientMax)
          or (getRandom(clientMax)<=clientsCount) then
      begin
        case aEvent.Event of
          SERV_INI_SOCK:     begin
            redt1.Lines.Add('Server socket initialized.');
            fillEvent(aEvent.OccurTime + aEvent.GoTime,1,-1,'',SERV_BIND);
          end;
          SERV_BIND: begin
            redt1.Lines.Add('Server socket binded.');
            fillEvent(aEvent.OccurTime + aEvent.GoTime,1,-1,'',SERV_LISTEN );
          end;
          SERV_LISTEN: begin
            redt1.Lines.Add('Server socket is listening now...');
          end;
          SERV_ACCEPTING: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces ;
            redt1.Lines.Add(spaces + 'Server socket is waiting client['
                + IntToStr(n) + '] to accept...');
            str:='Server' + IntToStr(n);
            fillEvent(aEvent.OccurTime + aEvent.GoTime, 1,
                aevent.NodeNo,str, SERV_ACCEPTED);
          end;
          SERV_ACCEPTED: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces ;
            redt1.Lines.Add(spaces + 'Server socket accepted: A new socket ['
                + IntToStr(n) + '] produced.');
            str:='Client' + IntToStr(n);
            fillEvent (aEvent.OccurTime + aevent.GoTime, getRandom(2),
                n, str, CLI_CONNECTED );
          end;
          SERV_RECV_READY: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            str:='Server' + IntToStr(n);
            redt1.Lines.Add(spaces + 'Server [' + IntToStr(n) +'] is ready for recv.');
            fillEvent(aEvent.OccurTime +aevent.GoTime, 1, n, str, SERV_RECV);
            lastTime[n]:=aEvent.OccurTime +aevent.GoTime+1;
          end;
          SERV_RECV: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            redt1.Lines.Add(spaces + 'Server [' + IntToStr(n) +
                '] receive data.'+ IntToStr(recvTimes[n]));
            inc(recvTimes[n]);
            //fillEvent(aEvent.OccurTime +aevent.GoTime, 1,
            //    aEvent.NodeNo, aEvent.GraphNodeName , SERV_RECV);
          end;
          SERV_SEND: ;
          SERV_CLOSING: ;
          SERV_CLOSE: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            redt1.Lines.Add(spaces + 'Server [' + IntToStr(n) +'] close.');
            recvTimes[n]:=0;
          end;
          CLI_INI_SOCK: begin
            n:= aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            redt1.Lines.Add(spaces + 'Client[' + IntToStr(n) + '] socket initialized.');
            fillEvent(aEvent.OccurTime +aevent.GoTime,1,n, aEvent.GraphNodeName, CLI_CONNECTING);
          end;
          CLI_CONNECTING: begin
            n:= aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            redt1.Lines.Add(spaces + 'Client['+ IntToStr(n) + '] is connecting...');
            fillEvent(aEvent.OccurTime +aevent.GoTime, getRandom(3),
                n, aEvent.GraphNodeName, SERV_ACCEPTING);
          end;
          CLI_CONNECTED: begin
            n:= aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            clientStates[n]:=CLI_CONNECTED ;
            redt1.Lines.Add(spaces + 'Client [' + IntToStr(n) + '] connected.');
            //lastTime[n]:=lastTime[n] + ;
            fillEvent(aEvent.OccurTime +aevent.GoTime, getRandom(5),
                n, aEvent.GraphNodeName, FILE_READY);

          end;
          CLI_SEND: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            redt1.Lines.Add(spaces + 'Client [' + IntToStr(n)
                +'] sending data...'+ IntToStr(sendTimes[n]));
            fillEvent(aEvent.OccurTime +aevent.GoTime , getRandom(8),
                aEvent.NodeNo, aEvent.GraphNodeName, SERV_RECV_READY );
            Inc(sendTimes[n]);
          end;
          CLI_RECV: ;
          CLI_RECV_READY :;
          CLI_CLOSE: begin
            n:= aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            clientStates[n]:=EVENT_NONE;
            redt1.Lines.Add(spaces + 'Client [' + IntToStr(n) +'] close.');
            if lastTime[n]>aEvent.OccurTime +aevent.GoTime then
              fillEvent( lastTime[n], 1, n, aEvent.GraphNodeName, SERV_CLOSE )
            else
              fillEvent(aEvent.OccurTime +aevent.GoTime, 1, n,
                  aEvent.GraphNodeName, SERV_CLOSE );
            lastTime[n]:=0;
            clientsCount:=clientsCount-1;
          end;
          FILE_READY: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;

            //redt1.Lines.Add(spaces + 'Client [' + IntToStr(n) +']: reding file...');
            //有2种可能：
            //    1. 读到文件，发送并产生下一个 FILE_READY
            //    2. 读到文件尾，关闭这个socket
            nram:=getRandom(100);
            if nram<=80 then
            begin
              //1. 读到文件，发送
              redt1.Lines.Add(spaces + 'Client [' + IntToStr(n) +']: file ready');
              fillEvent(aEvent.OccurTime +aevent.GoTime, getRandom(5),
                  n, aEvent.GraphNodeName, FILE_READ);
            end else begin
              //2. 读到文件尾，关闭这个socket
              redt1.Lines.Add(spaces + 'Client [' + IntToStr(aEvent.NodeNo) +']: eof of file.');
              fillEvent(aEvent.OccurTime +aevent.GoTime, 1,
                  n, aEvent.GraphNodeName, CLI_CLOSE );
              sendTimes[n]:=0;
            end;
          end;
          FILE_READ: begin
            n:=aEvent.NodeNo;
            for I := 0 to n do
              spaces:=spaces + spaces;
            redt1.Lines.Add(spaces + 'Client [' + IntToStr(n) +']: read file.');
            fillEvent(aEvent.OccurTime +aevent.GoTime, 1, n, aEvent.GraphNodeName, CLI_SEND);
            fillEvent(aEvent.OccurTime +aevent.GoTime, getRandom(5),
                n, aEvent.GraphNodeName, FILE_READY );
          end ;
        end;   //case
        EventTime:=aEvent.OccurTime +1;
        EventsQueue.Delete(0);
      end else begin
        //计时时间和队列时间不一致，并且client未达到最大值，随机数条件也满足
        newClient(getNoEventClient);
        //Inc(clientsCount);
      end;
    end else begin
      //对列中无元素，只可能是server listen且无client
      newClient(0);
    end;
    SendMessage(redt1.Handle, WM_VSCROLL, SB_BOTTOM,0);
    Application.ProcessMessages;
  end;
  until bSuspend;
end;

end.
