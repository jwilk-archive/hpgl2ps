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
10.5 mm -204 mm translate
/Helvetica 4 Font
/Helvetica 1.35 3.75 0 DefFont
/Helvetica 1.35 3.75 0 DefFont
[] 0 setdash
newpath
  25 25 M
  50 25 D
  50 50 D
  25 50 D
  25 25 D
  -2.5 0 I
  0 -2.5 I
  2.5 0 I
  0 2.5 I
closepath
stroke
newpath
  0 0 M
  270 0 D
  270 192 D
  0 192 D
  0 0 D
closepath
stroke
[2.46447 mm 1.84835 mm 1.84835 mm 1.84835 mm] 0 setdash
newpath
  100 35 M
  100 0 I
stroke
[3.6967 mm 1.23223 mm 1.84835 mm 1.23223 mm] 0 setdash
newpath
  100 32.5 M
  100 0 I
stroke
[4.92894 mm 0.924175 mm 1.23223 mm 0.924175 mm] 0 setdash
newpath
  100 30 M
  100 0 I
stroke
[6.16117 mm 1.23223 mm 0.616117 mm 1.23223 mm] 0 setdash
newpath
  100 27.5 M
  100 0 I
stroke
[6.77729 mm 1.23223 mm 0 mm 0 mm] 0 setdash
newpath
  100 25 M
  100 0 I
stroke
[6.16117 mm 1.84835 mm 0 mm 0 mm] 0 setdash
newpath
  100 22.5 M
  100 0 I
stroke
[] 0 setdash
newpath
  100 20 M 100 20 D
stroke
newpath
  200 20 M 200 20 D
stroke
[1.84835 mm 4.31282 mm 1.84835 mm 0 mm] 0 setdash
newpath
  100 17.5 M
  100 0 I
stroke
[2.46447 mm 3.08058 mm 2.46447 mm 0 mm] 0 setdash
newpath
  100 15 M
  100 0 I
stroke
[3.08058 mm 2.15641 mm 0.616117 mm 2.15641 mm] 0 setdash
newpath
  100 12.5 M
  100 0 I
stroke
[3.08058 mm 1.84835 mm 1.84835 mm 1.84835 mm] 0 setdash
newpath
  100 10 M
  100 0 I
stroke
[2.46447 mm 1.54029 mm 2.46447 mm 1.54029 mm] 0 setdash
newpath
  100 7.5 M
  100 0 I
stroke
[2.15641 mm 1.84835 mm 2.15641 mm 1.84835 mm] 0 setdash
newpath
  100 5 M
  100 0 I
stroke
50 100 1 0 (  --   0deg --) Text
60.6313 100 1 45 (  --  45deg --) Text
68.1487 107.517 1 90 (  --  90deg --) Text
68.1487 118.149 1 135 (  -- 135deg --) Text
60.6313 125.666 1 180 (  -- 180deg --) Text
50 125.666 1 -135 (  -- 225deg --) Text
42.4826 118.149 1 -90 (  -- 270deg --) Text
42.4826 107.517 1 -45 (  -- 315deg --) Text
/Helvetica 1.35 3.75 3.75 DefFont
100 100 1 0 ( SLANT of 45deg) Text
/Helvetica 1.35 3.75 -3.75 DefFont
100 90 1 0 ( SLANT of -45deg) Text
/Helvetica 1.35 3.75 0 DefFont
/Helvetica 4.86 4.5 0 DefFont
50 150 1 0 ( Size is relative) Text
/Helvetica 2.7 1.9 0 DefFont
50 137.5 1 0 ( DEFAULT sizes) Text
/Helvetica 8 10 0 DefFont
50 125 1 0 (LARGE size (w=8mm, h=10mm)) Text
[] 0 setdash
225 25 12.5 12.5 0 360 Ellipse
225 25 10 10 0 360 Ellipse
225 25 7.5 7.5 0 360 Ellipse
225 25 5 5 0 360 Ellipse
225 25 2.5 2.5 0 360 Ellipse
225 25 1.25 1.25 0 360 Ellipse
/Helvetica 1.35 3.75 0 DefFont
225 25 5 0 (+) Text
250 25 5 0 (+) Text
250 37.5 5 0 (%) Text
250 12.5 5 0 (%) Text
showpage
