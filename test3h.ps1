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
0.3 mm setlinewidth
/Helvetica 4.536 5.7 0 DefFont
6.25 0 1 90 (DSA 602 DIGITIZING SIGNAL ANALYZER) Text
0.05 mm setlinewidth
[] 0 setdash
newpath
  152.5 19.375 M
  153.125 19.5312 D
  153.125 19.6875 D
  152.5 19.8438 D
0.025 mm setlinewidth
stroke
newpath
  191.875 21.25 M
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 0.9 R
  0 -0.9 I
  -15.625 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  1.25 0 R
  -1.25 0 I
  0 15.625 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -0.9 R
  0 0.9 I
  15.625 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
  -1.25 0 R
  1.25 0 I
  0 -15.625 I
stroke
newpath
  113.75 21.25 M
  0 3.125 I
  0.625 0 R
  -0.625 0 I
  -0.625 0 R
  0.625 0 I
  0 3.125 I
  0.625 0 R
  -0.625 0 I
  -0.625 0 R
  0.625 0 I
  0 3.125 I
  0.625 0 R
  -0.625 0 I
  -0.625 0 R
  0.625 0 I
  0 3.125 I
  0.625 0 R
  -0.625 0 I
  -0.625 0 R
  0.625 0 I
  0 3.125 I
stroke
newpath
  35.625 99.375 M
  3.125 0 I
  0 0.45 R
  0 -0.45 I
  0 -0.45 R
  0 0.45 I
  3.125 0 I
  0 0.45 R
  0 -0.45 I
  0 -0.45 R
  0 0.45 I
  3.125 0 I
  0 0.45 R
  0 -0.45 I
  0 -0.45 R
  0 0.45 I
  3.125 0 I
  0 0.45 R
  0 -0.45 I
  0 -0.45 R
  0 0.45 I
  3.125 0 I
0.3 mm setlinewidth
/Helvetica 4.86 4.89 0 DefFont
stroke
213.125 108.438 1 90 (200) Text
0.25 mm setlinewidth
newpath
  213.125 116.639 M
  -0.305625 0.42525 I
stroke
newpath
  211.291 117.064 M
  1.52813 2.67186e-07 I
  0.305625 0.6075 I
  7.39204e-09 0.6075 I
  -0.305625 0.6075 I
stroke
newpath
  211.291 118.886 M
  1.83375 3.20623e-07 I
stroke
0.3 mm setlinewidth
213.125 119.433 1 90 (s   ) Text
0.05 mm setlinewidth
/Helvetica 4.86 4.89 0 DefFont
newpath
  147.812 16.875 M
  -2.1875 4.6875 I
  0 -3.125 I
  0.9375 0.9375 I
  1.25 0 I
  -2.1875 2.1875 I
0.3 mm setlinewidth
stroke
newpath
  113.75 19.6875 M
  -0.625 -0.625 I
  1.25 0 I
  -0.625 0.625 I
  0 -1.5625 I
  0.3125 -0.3125 I
  2.5 0 I
  1.5625 -0.9375 I
stroke
newpath
  118.125 15.625 M
  -1.875 0.9375 I
  0 2.5 I
  1.875 -0.9375 I
stroke
0.0125 mm setlinewidth
showpage
