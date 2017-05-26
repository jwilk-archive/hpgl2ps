ps_macros()
{
    printf("%%! PS-Adobe-1.0: For Apple LaserWriter\n");
    printf("%% default font is 10 pt. Helvetica\n");
    printf("/basefont {/Helvetica findfont 10 scalefont setfont} def\n");

    printf("/mm {72.27 mul 25.4 div} def\n");	/* Specify millimeters */

    printf("/M\n");				/* Move macro */
    printf("{\n");
    printf("    /Ymove exch def\n");
    printf("    /Xmove exch def\n");
    printf("    Xmove mm Ymove mm moveto\n");
    printf("} def\n");

    printf("/R\n");				/* Relative move macro */
    printf("{\n");
    printf("    /Yrmove exch def\n");
    printf("    /Xrmove exch def\n");
    printf("    Xrmove mm Yrmove mm rmoveto\n");
    printf("} def\n");

    printf("/D\n");				/* Draw macro */
    printf("{\n");
    printf("    /Ydraw exch def\n");
    printf("    /Xdraw exch def\n");
    printf("    Xdraw mm Ydraw mm lineto\n");
    printf("} def\n");

    printf("/I\n");				/* Relative draw  macro */
    printf("{\n");
    printf("    /Yrdraw exch def\n");
    printf("    /Xrdraw exch def\n");
    printf("    Xrdraw mm Yrdraw mm rlineto\n");
    printf("} def\n");
    /*
     *		Procedure to change font and size of font
     *		---->   font size Font    <----
     */
    printf("/Font\n");
    printf("{\n");
    printf("    /Height exch def\n");
    printf("    /FontName exch def\n");
    printf("    FontName findfont Height mm scalefont setfont\n");
    printf("} def\n");
    /*
     *		Procedure to change font, width, slant and height
     *		---->   font width height slant DefFont    <----
     *
     *	Note: slant = height * tan( slant_angle )
     */
    printf("/DefFont\n");
    printf("{\n");
    printf("    /Slant exch def\n");
    printf("    /Height exch def\n");
    printf("    /Width exch def\n");
    printf("    /FontName exch def\n");
    printf("    FontName findfont [ Width mm 0 Slant mm Height mm 0 0] makefont setfont\n");
    printf("} def\n");
    /*
     *		General Text Layout Procedure
     *		---->   x y pos_num angle (text) Text    <----
     */
    printf("/Text\n");
    printf("{\n");
    printf("    /String exch def\n");
    printf("    /Angle exch def\n");
    printf("    /Position exch def\n");
    printf("    /Ymove exch def\n");
    printf("    /Xmove exch def\n");
    printf("    Position 1 lt {/hpf 0 def /lpf 0 def} if\n");
    printf("    Position 1 eq {/hpf 0 def /lpf 0 def} if\n");
    printf("    Position 2 eq {/hpf 0 def /lpf 0.5 def} if\n");
    printf("    Position 3 eq {/hpf 0 def /lpf 1 def} if\n");
    printf("    Position 4 eq {/hpf 0.5 def /lpf 0 def} if\n");
    printf("    Position 5 eq {/hpf 0.5 def /lpf 0.5 def} if\n");
    printf("    Position 6 eq {/hpf 0.5 def /lpf 1 def} if\n");
    printf("    Position 7 eq {/hpf 1 def /lpf 0 def} if\n");
    printf("    Position 8 eq {/hpf 1 def /lpf 0.5 def} if\n");
    printf("    Position 9 eq {/hpf 1 def /lpf 1 def} if\n");
    printf("    Position 9 gt {/hpf 1 def /lpf 1 def} if\n");
    printf("    /StrLen String stringwidth pop lpf mul def\n");
    printf("    /StrHt Height mm hpf mul def\n");
    printf("    /Xdiff StrHt Angle sin mul StrLen Angle cos mul sub def\n");
    printf("    /Ydiff StrHt Angle cos mul StrLen Angle sin mul add def\n");
    printf("    Xmove mm Xdiff add Ymove mm Ydiff sub moveto\n");
    printf("    gsave\n");
    printf("        Angle rotate\n");
    printf("        String show\n");
    printf("    grestore\n");
    printf("    /PosterOnly 0 def\n");
    printf("} def\n");
    /*
     *		Ellipse and Circle procedure.
     *  ---->   xcen ycen xrad yrad start_angle end_angle Ellipse   <----
     */
    printf("/EllipseDict 8 dict def\n");
    printf("EllipseDict /mtrx matrix put\n");
    printf("/Ellipse \n");
    printf("{   EllipseDict begin\n");
    printf("    /endangle exch def\n");
    printf("    /startangle exch def\n");
    printf("    /yradius exch def\n");
    printf("    /xradius exch def\n");
    printf("    /ycenter exch def\n");
    printf("    /xcenter exch def\n");
    printf("    /savematrix mtrx currentmatrix def\n");
    printf("    xcenter mm ycenter mm translate\n");
    printf("    xradius mm yradius mm div 1 scale\n");
    printf("    newpath\n");
    printf("        0 0 xradius mm startangle endangle arc\n");
    printf("    stroke\n");
    printf("    savematrix setmatrix\n");
    printf("    end\n");
    printf("} def\n");

    printf("basefont\n");		/* Set the default font */
    printf("1 setlinecap\n");		/* Use round caps */
    printf("1 setlinejoin\n");		/* Use round joins */
    printf("3 setmiterlimit\n");	/* Bevel small angle miters */
}
