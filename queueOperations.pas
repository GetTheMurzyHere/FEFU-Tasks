unit queueOperations;
//вторник 13:30
interface

type
  PNode = ^TNode;
  TNode = record
    data: integer;
    next: PNode;
  end;

var
  head, tail: PNode;
  number: integer;

procedure push(x: integer);
procedure pop;
procedure viewQueue;

implementation

procedure push;
var
  newElementPoint: PNode;
begin
  new(newElementPoint);
  newElementPoint^.data := x;
  newElementPoint^.next := nil;
  if tail <> nil then tail^.next := newElementPoint;
  tail := newElementPoint;
  if head = nil then head := tail;
end;

procedure pop;
var
  top: PNode;
begin
  if head = nil then 
  begin
    writeln('В очереди нет элементов!');
    exit;
  end;
  top := head;
  head := top^.next;
  dispose(top);
end;

procedure viewQueue;
var
  currentPoint: PNode;
begin
  currentPoint := head;
  while currentPoint <> nil do
  begin
    write(currentPoint^.data, ' ');
    currentPoint := currentPoint^.next;
  end;
  writeln;
end;
end.