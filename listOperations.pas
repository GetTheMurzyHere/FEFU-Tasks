unit listOperations;

interface

procedure init;
function isEmpty: boolean; 
procedure pushBegin(x: integer);
procedure pushMidBefore(dataBefore: integer; dataPush: integer);
procedure pushMidAfter(dataAfter: integer; dataPush: integer);
procedure pushEnd(x: integer);
procedure pop(dataPop: integer);
procedure free;
procedure viewList;

implementation
// 1 2 3 4
type
  PNode = ^TNode;
  TNode = record
    next: PNode;
    data: integer;
  end;

var
  head: PNode;

procedure init;
begin
  head := nil;
end;

function isEmpty: boolean; 
begin
  isEmpty := (head = nil);
end;

procedure pushBegin;
var
  currentPoint: PNode;
begin
  new(currentPoint);
  currentPoint^.data := x;
  currentPoint^.next := head;
  head := currentPoint;
end;

procedure pushMidBefore;
var
  currentPoint, prevPoint, newCeil: PNode;
begin
  prevPoint := head;
  currentPoint := head^.next;
  while currentPoint^.data <> dataBefore do
  begin
    currentPoint := currentPoint^.next;
    prevPoint := prevPoint^.next;
    if currentPoint = nil then exit;
  end;
  new(newCeil);
  newCeil^.next := prevPoint^.next;
  newCeil^.data := dataPush;
  prevPoint^.next := newCeil;
end;

procedure pushMidAfter;
var
  currentPoint, prevPoint, newCeil: PNode;
begin
  prevPoint := head;
  currentPoint := head^.next;
  while prevPoint^.data <> dataAfter do
  begin
    currentPoint := currentPoint^.next;
    prevPoint := prevPoint^.next;
    if prevPoint = nil then exit;
  end;
  new(newCeil);
  newCeil^.next := prevPoint^.next;
  newCeil^.data := dataPush;
  prevPoint^.next := newCeil;
end;

procedure pushEnd(x: integer);
var
  currentPoint, newCeil: PNode;
begin
  currentPoint := head;
  while currentPoint^.next <> nil do currentPoint := currentPoint^.next;
  new(newCeil);
  newCeil^.data := x;
  currentPoint^.next := newCeil;
end;
//1 2 3 4 
procedure pop;
var
  currentPoint, prevPoint: PNode;
begin
  if head = nil then
  begin
    writeln('Список пуст, удаление невозможно!');
    exit;
  end;
  if head^.data = dataPop then
  begin
    currentPoint := head;
    head := head^.next;
    dispose(currentPoint);
    exit;
  end;
  currentPoint := head^.next;
  prevPoint := head;
  while currentPoint^.data <> dataPop do
  begin
    currentPoint := currentPoint^.next;
    prevPoint := prevPoint^.next;
    if currentPoint = nil then 
    begin
      writeln('Элемента ', dataPop, ' не существует в данном списке!');
      exit;
    end;
  end;
  prevPoint^.next := currentPoint^.next;
  dispose(currentPoint);
end;

procedure free;
var
  currentPoint, DelPoint: PNode;
begin
  currentPoint := head;
  while currentPoint <> nil do 
  begin
    DelPoint := currentPoint;
    currentPoint := currentPoint^.next;
    Dispose(DelPoint);
  end;
  init;
end;

procedure viewList;
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