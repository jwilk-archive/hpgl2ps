%! PS-Adobe-1.0: For Apple LaserWriter
% default font is 14 pt. Helvetica
/basefont {/Helvetica findfont 14 scalefont setfont} def
/mm {72.0 mul 25.4 div} def
/M
{
    /Ymove exch def
    /Xmove exch def
    Xmove mm Ymove mm moveto
} def
/R
{
    /Yrmove exch def
    /Xrmove exch def
    Xrmove mm Yrmove mm rmoveto
} def
/D
{
    /Ydraw exch def
    /Xdraw exch def
    Xdraw mm Ydraw mm lineto
} def
/I
{
    /Yrdraw exch def
    /Xrdraw exch def
    Xrdraw mm Yrdraw mm rlineto
} def
/AA
{
    /endangle exch def
    /startangle exch def
    /radius exch def
    /Ydraw exch def
    /Xdraw exch def
    Xdraw mm Ydraw mm radius mm startangle endangle arc
} def
/AAC
{
    /endangle exch def
    /startangle exch def
    /radius exch def
    /Ydraw exch def
    /Xdraw exch def
    Xdraw mm Ydraw mm radius mm startangle endangle arcn
} def
/Font
{
    /Height exch def
    /FontName exch def
    FontName findfont Height mm scalefont setfont
} def
/DefFont
{
    /Slant exch def
    /Height exch def
    /Width exch def
    /FontName exch def
    FontName findfont [ Width mm 0 Slant mm Height mm 0 0] makefont setfont
} def
/Text
{
    /String exch def
    /Angle exch def
    /Position exch def
    /Ymove exch def
    /Xmove exch def
    Position 1 lt {/hpf 0 def /lpf 0 def} if
    Position 1 eq {/hpf 0 def /lpf 0 def} if
    Position 2 eq {/hpf 0 def /lpf 0.5 def} if
    Position 3 eq {/hpf 0 def /lpf 1 def} if
    Position 4 eq {/hpf 0.5 def /lpf 0 def} if
    Position 5 eq {/hpf 0.5 def /lpf 0.5 def} if
    Position 6 eq {/hpf 0.5 def /lpf 1 def} if
    Position 7 eq {/hpf 1 def /lpf 0 def} if
    Position 8 eq {/hpf 1 def /lpf 0.5 def} if
    Position 9 eq {/hpf 1 def /lpf 1 def} if
    Position 9 gt {/hpf 1 def /lpf 1 def} if
    /StrLen String stringwidth pop lpf mul def
    /StrHt Height mm hpf mul def
    /Xdiff StrHt Angle sin mul StrLen Angle cos mul sub def
    /Ydiff StrHt Angle cos mul StrLen Angle sin mul add def
    Xmove mm Xdiff add Ymove mm Ydiff sub moveto
    gsave
        Angle rotate
        String show
    grestore
    /PosterOnly 0 def
} def
/EllipseDict 8 dict def
EllipseDict /mtrx matrix put
/Ellipse 
{   EllipseDict begin
    /endangle exch def
    /startangle exch def
    /yradius exch def
    /xradius exch def
    /ycenter exch def
    /xcenter exch def
    /savematrix mtrx currentmatrix def
    xcenter mm ycenter mm translate
    xradius mm yradius mm div 1 scale
    newpath
        0 0 xradius mm startangle endangle arc
    stroke
    savematrix setmatrix
    end
} def
basefont
1 setlinecap
1 setlinejoin
3 setmiterlimit
90 rotate
8.83334 mm -204 mm translate
/Helvetica 4 Font
0.0125 mm setlinewidth
newpath
  66.6667 66.6667 M
  6.66667 0 I
  -13.3333 0 I
  6.66667 0 I
  0 6.66667 I
  0 -13.3333 I
stroke
66.6667 60 1 0 ( Hi There) Text
66.6667 66.6667 33.3333 33.3333 0 250 Ellipse
newpath
  133.333 66.6667 M
  6.66667 0 I
  -13.3333 0 I
  6.66667 0 I
  0 6.66667 I
  0 -13.3333 I
stroke
[5.5 mm 1 mm 0 mm 0 mm] 0 setdash
0.2 mm setlinewidth
133.333 66.6667 33.3333 33.3333 250 0 Ellipse
0.05 mm setlinewidth
newpath
  0 0 M
  253.333 0 I
  0 180 I
  -253.333 0 I
  0 -180 I
closepath
stroke
/Helvetica 2.8 4 4 DefFont
/Helvetica 20.4 40.8 4 DefFont
33.3333 133.333 1 0 (DXY-880) Text
/Helvetica 20.4 40.8 0 DefFont
/Helvetica 1.6 3.2 0 DefFont
showpage
