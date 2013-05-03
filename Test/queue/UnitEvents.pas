unit UnitEvents;

interface

type
  NET_EVENTS=(EVENT_NONE, SERV_INI_SOCK, SERV_BIND, SERV_LISTEN, SERV_ACCEPTING,
      SERV_ACCEPTED, SERV_RECV_READY, SERV_RECV, SERV_SEND, SERV_CLOSING, SERV_CLOSE,
      CLI_INI_SOCK, CLI_CONNECTING, CLI_CONNECTED, CLI_SEND, CLI_RECV_READY, CLI_RECV,
      CLI_CLOSE,
      FILE_READY, FILE_READ, FILE_END, FILE_CLOSE,
      FD_CLR, FD_SET, FD_ZERO );


  EventRec=record
    OccurTime:Integer ;
    GoTime:Integer ;
    Event:NET_EVENTS ;
    NodeNo:Integer  ;
    GraphNodeName:string ;
  end;

implementation

end.
