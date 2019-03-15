unit stackOperations;

interface

type
  PNode = ^TNode;
  TNode = record
    Data: integer;
    prev: PNode;
  end;

var
  head, p: PNode;

procedure push(x: integer);
procedure pop;
procedure view_stack;
function peek: integer;
implementation

procedure push(x: integer);
begin
  new(p);
  p^.data := x;
  p^.prev := head;
  head := p;
end;

procedure pop;
begin
  if head = nil then exit;
  p := head;
  head := p^.prev;
  dispose(p);
end;

procedure view_stack;
begin
  p := head;
  while p <> nil do
  begin
    write(p^.data, ' ');
    p := p^.prev;
  end;
  p := head;
  writeln;
end;

function peek: integer;
begin
  if head = nil then exit;
  peek := head^.data;
end;
end.