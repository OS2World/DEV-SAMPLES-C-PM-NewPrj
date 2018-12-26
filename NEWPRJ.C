#include <stdio.h>
#include <string.h>


char filename[256];
char projname[256];
char *tmpptr;
FILE *outfile;
char tempicon[] =
{
	73,67,26,0,0,0,16,0,16,0,32,0,0,0,12,0,0,0,32,0,64,0,1,0,1,0,0,0,0,-1,
	-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-39,-51,-33,-1,-42,-75,-33,-1,-41,-75,-97,-1,-41,-75,95,-1,-42,
	-76,-33,-1,-39,-51,-33,-1,-33,-1,-1,-1,-33,-1,-1,-1,-33,-1,-1,-1,-1,-1,
	-1,-1,-1,-2,-1,-1,-1,-2,-1,-1,97,-70,-1,-1,111,-86,63,-1,99,-86,-33,-1,
	111,-86,-33,-1,97,-110,63,-1,127,-1,-1,-1,127,-1,-1,-1,127,-1,-1,-1,127,
	-1,-1,-1,127,-1,-1,-8,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};

void cdecl main(int argc,char **argv)

{

    printf("\nnewprj - OS/2 PM project creator.");
	 printf("\n    Written by Anthony Andersen. Compuserve 72037,2474");
	 printf("\n    Released to Public Domain. Comments are welcome.\n\n");

/***************************************************************/
    if (argc == 1 || argv[1][0] == '-' || argv[1][0] == '?')
    {
        printf("    usage:");
        printf("\n           newprj projectname");
        printf("\n");
        printf("\n    arguments are as follows:");
		 printf("\n           projectname : name for new project (no extension)");
        printf("\n");
        printf("\n    example:");
        printf("\n           newprj myproj");
        printf("\n");
        return;
    }
/***************************************************************/

	strcpy(filename,argv[1]);
	if (!(tmpptr = strstr(filename,"."))) {
		tmpptr = &filename[strlen(filename)];
	}
	*tmpptr = '\0';
	strcpy(projname,filename);

	strcat(filename,".ICO");
	outfile = fopen(filename,"wb");
	if (outfile == NULL) {
		printf("Can't create file %s\n",filename);
		return;
	}
	fwrite(tempicon,1,288,outfile);
	fclose(outfile);
	printf("Wrote file %s\n",filename);

	*tmpptr = '\0';
	strcat(filename,".MAK");

	/* create MAKefile */

	outfile = fopen(filename,"wt");
	if (outfile == NULL) {
		printf("Can't create file %s",filename);
		return;
	}
	fprintf(outfile,"#makefile for %s\n\n",projname);
	fprintf(outfile,"cp=cl /c /W3 /G2swc /Od /ALw /Zi\n\n",projname);
	fprintf(outfile,"%s.res: %s.rc %s.h %s.dlg\n",projname,projname,projname,projname);
	fprintf(outfile,"    rc -r %s.rc\n\n",projname);
	fprintf(outfile,"%s.obj: %s.c %s.h\n",projname,projname,projname);
	fprintf(outfile,"    $(cp) %s.c\n\n",projname);
	fprintf(outfile,"%s.exe: %s.obj %s.def\n",projname,projname,projname);
	fprintf(outfile,"    link @%s.lnk\n",projname);
	fprintf(outfile,"    rc %s.res\n\n",projname);
	fprintf(outfile,"%s.exe: %s.res\n",projname,projname);
	fprintf(outfile,"    rc %s.res\n\n",projname);
	fclose(outfile);
	printf("Wrote file %s\n",filename);

	*tmpptr = '\0';
	strcat(filename,".C");

	/* create C file */

	outfile = fopen(filename,"wt");
	if (outfile == NULL) {
		printf("Can't create file %s",filename);
		return;
	}
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* PROGRAM: %s.c                                                      */\n",projname);
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* DESCRIPTION:                                                       */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON ENTRY:                                                          */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON EXIT:                                                           */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"#define INCL_WIN\n");
	fprintf(outfile,"#define INCL_GPI\n");
	fprintf(outfile,"#define INCL_DOS\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"#include \"os2.h\"\n");
	fprintf(outfile,"#include \"%s.h\"\n",projname);
	fprintf(outfile,"\n");
	fprintf(outfile,"HAB    hab;\n");
	fprintf(outfile,"HMQ    hmq;\n");
	fprintf(outfile,"QMSG   qmsg;\n");
	fprintf(outfile,"HWND   %sframe;\n",projname);
	fprintf(outfile,"HWND   %sclient;\n",projname);
	fprintf(outfile,"ULONG  frameflags = FCF_STANDARD|FCF_SHELLPOSITION;\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ROUTINE: VOID cdecl main(int argc,char **argv)                     */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* DESCRIPTION:                                                       */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON ENTRY:                                                          */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON EXIT:                                                           */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"VOID cdecl main(int argc,char **argv)\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"{\n");
	fprintf(outfile,"	hab = WinInitialize(0);\n");
	fprintf(outfile,"	hmq = WinCreateMsgQueue(hab, 0);\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	WinRegisterClass(\n");
	fprintf(outfile,"		hab,               /* Anchor block handle             */\n");
	fprintf(outfile,"		\"%sclass\",         /* Name of class being registered  */\n",projname);
	fprintf(outfile,"		%swindproc,        /* Window procedure for class      */\n",projname);
	fprintf(outfile,"		CS_SIZEREDRAW,     /* Class style                     */\n");
	fprintf(outfile,"		0);                /* Extra bytes to reserve          */\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	%sframe = WinCreateStdWindow(\n",projname);
	fprintf(outfile,"		HWND_DESKTOP,      /* parent                          */\n");
	fprintf(outfile,"		WS_VISIBLE|FS_SHELLPOSITION, /* style of frame        */\n");
	fprintf(outfile,"		&frameflags,       /* Pointer to control data         */\n");
	fprintf(outfile,"		\"%sclass\",         /* Client window class name        */\n",projname);
	fprintf(outfile,"		NULL,              /* titlebar text is %s.exe         */\n",projname);
	fprintf(outfile,"		0L,                /* Style of client window          */\n");
	fprintf(outfile,"		NULL,              /* Module handle for resources     */\n");
	fprintf(outfile,"		FRAMERESID,        /* resource id                     */\n");
	fprintf(outfile,"		&%sclient);        /* Pointer to client window handle */\n",projname);
	fprintf(outfile,"\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	WinSetWindowPos(%sframe,HWND_TOP,0,0,0,0,\n",projname);
	fprintf(outfile,"					SWP_ACTIVATE|SWP_SHOW|SWP_ZORDER);\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	while (WinGetMsg(hab,&qmsg,NULL,0,0)) {\n");
	fprintf(outfile,"		WinDispatchMsg(hab,&qmsg);\n");
	fprintf(outfile,"	}\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	WinDestroyWindow(%sframe);\n",projname);
	fprintf(outfile,"	WinDestroyMsgQueue(hmq);\n");
	fprintf(outfile,"	WinTerminate(hab);\n");
	fprintf(outfile,"}\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ROUTINE: MRESULT CALLBACK %swindproc(hwnd,msg,mp1,mp2)             */\n",projname);
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* DESCRIPTION:                                                       */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON ENTRY:                                                          */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON EXIT:                                                           */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"MRESULT CALLBACK %swindproc(HWND hwnd,USHORT msg,MPARAM mp1,MPARAM mp2)\n",projname);
	fprintf(outfile,"\n");
	fprintf(outfile,"{\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	RECTL  rectl;\n");
	fprintf(outfile,"	HPS    hps;\n");
	fprintf(outfile,"	USHORT cmd;\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	switch (msg) {\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	case WM_CREATE:\n");
	fprintf(outfile,"		break;\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	case WM_PAINT:\n");
	fprintf(outfile,"		hps = WinBeginPaint(hwnd,NULL,&rectl);\n");
	fprintf(outfile,"		GpiErase(hps);\n");
	fprintf(outfile,"		WinEndPaint(hps);\n");
	fprintf(outfile,"		return (0L);\n");
	fprintf(outfile,"		break;\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	case WM_COMMAND:\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"		cmd = SHORT1FROMMP(mp1);\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"		switch (cmd) {\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"		case IDM_EXIT:\n");
	fprintf(outfile,"			WinPostMsg(hwnd,WM_CLOSE,0L,0L);\n");
	fprintf(outfile,"			break;\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"		case IDM_ABOUT:\n");
	fprintf(outfile,"			WinDlgBox(hwnd,hwnd,aboutdlgproc,NULL,IDD_ABOUT,NULL);\n");
	fprintf(outfile,"			break;\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"		}\n");
	fprintf(outfile,"	}\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"	return (WinDefWindowProc(hwnd, msg, mp1, mp2));\n");
	fprintf(outfile,"}\n");
	fprintf(outfile,"\n\n");
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ROUTINE: MRESULT CALLBACK aboutdlgproc(hwnd,msg,mp1,mp2)           */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* DESCRIPTION:                                                       */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON ENTRY:                                                          */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/* ON EXIT:                                                           */\n");
	fprintf(outfile,"/*                                                                    */\n");
	fprintf(outfile,"/**********************************************************************/\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"MRESULT CALLBACK aboutdlgproc(HWND hwnd,USHORT msg,MPARAM mp1,MPARAM mp2)\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"{\n");
	fprintf(outfile,"	return WinDefDlgProc(hwnd,msg,mp1,mp2);\n");
	fprintf(outfile,"}\n");
	fclose(outfile);
	printf("Wrote file %s\n",filename);

	*tmpptr = '\0';
	strcat(filename,".DEF");

	/* create linker DEFinition file */
	outfile = fopen(filename,"wt");
	if (outfile == NULL) {
		printf("Can't create file %s",filename);
		return;
	}
	fprintf(outfile,";linker definition file for %s\n",projname);
	fprintf(outfile,"NAME    %s     WINDOWAPI\n",projname);
	fprintf(outfile,"DESCRIPTION 'PM %s application'\n");
	fprintf(outfile,"STUB    'OS2STUB.EXE'\n");
	fclose(outfile);
	printf("Wrote file %s\n",filename);

	*tmpptr = '\0';
	strcat(filename,".RC");

	/* create Resource Compiler source file */
	outfile = fopen(filename,"wt\n");
	if (outfile == NULL) {
		printf("Can't create file %s",filename);
		return;
	}
	fprintf(outfile,"#include \"os2.h\"\n");
	fprintf(outfile,"#include \"%s.h\"\n",projname);
	fprintf(outfile,"\n");
	fprintf(outfile,"ICON FRAMERESID %s.ico\n",projname);
	fprintf(outfile,"\n");
	fprintf(outfile,"MENU FRAMERESID\n");
	fprintf(outfile,"BEGIN\n");
	fprintf(outfile,"    SUBMENU           \"~File\", 2\n");
	fprintf(outfile,"    BEGIN\n");
	fprintf(outfile,"          MENUITEM    \"~New\",            IDM_NEW, MIS_TEXT\n");
	fprintf(outfile,"          MENUITEM    \"~Open...\",        IDM_OPEN\n");
	fprintf(outfile,"          MENUITEM    \"~Save\",           IDM_SAVE\n");
	fprintf(outfile,"          MENUITEM    \"Save ~As...\",     IDM_SAVEAS\n");
	fprintf(outfile,"          MENUITEM    \"~Print\",          IDM_PRINT\n");
	fprintf(outfile,"          MENUITEM    \"\",                IDM_PRINT, MIS_SEPARATOR\n");
	fprintf(outfile,"          MENUITEM    \"E~xit %s\",     IDM_EXIT, MIS_TEXT\n",projname);
	fprintf(outfile,"    END\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"    SUBMENU           \"~Edit\", 3\n");
	fprintf(outfile,"    BEGIN\n");
	fprintf(outfile,"          MENUITEM    \"~Undo\tALT+BKSP\",   IDM_UNDO,MIS_TEXT,MIA_DISABLED\n");
	fprintf(outfile,"          MENUITEM    \"\",                  IDM_UNDO,MIS_SEPARATOR		 \n");
	fprintf(outfile,"          MENUITEM    \"Cu~t\tShift+Del\",   IDM_CUT,MIS_TEXT,MIA_DISABLED\n");
	fprintf(outfile,"          MENUITEM    \"~Copy\tCtrl+Ins\",   IDM_COPY,MIS_TEXT,MIA_DISABLED\n");
	fprintf(outfile,"          MENUITEM    \"~Paste\tShift+Ins\", IDM_PASTE,MIS_TEXT,MIA_DISABLED\n");
	fprintf(outfile,"          MENUITEM    \"C~lear\tDel\",       IDM_CLEAR,MIS_TEXT,MIA_DISABLED\n");
	fprintf(outfile,"    END\n");
	fprintf(outfile,"    SUBMENU           \"~Help\", 4\n");
	fprintf(outfile,"    BEGIN\n");
	fprintf(outfile,"          MENUITEM    \"A~bout %s...\",    IDM_ABOUT\n",projname);
	fprintf(outfile,"    END\n");
	fprintf(outfile,"END\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"ACCELTABLE FRAMERESID\n");
	fprintf(outfile,"BEGIN\n");
	fprintf(outfile,"    VK_BACKSPACE,   IDM_UNDO,  VIRTUALKEY, ALT\n");
	fprintf(outfile,"    VK_DELETE,      IDM_CUT,   VIRTUALKEY, LONEKEY\n");
	fprintf(outfile,"    VK_INSERT,      IDM_COPY,  VIRTUALKEY, CONTROL\n");
	fprintf(outfile,"    VK_INSERT,      IDM_PASTE, VIRTUALKEY, SHIFT\n");
	fprintf(outfile,"    VK_DELETE,      IDM_CLEAR, VIRTUALKEY, SHIFT\n");
	fprintf(outfile,"END\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"RCINCLUDE %s.dlg\n",projname);
	fclose(outfile);
	printf("Wrote file %s\n",filename);

	*tmpptr = '\0';
	strcat(filename,".LNK");

	/* create LiNKer input file */
	outfile = fopen(filename,"wt");
	if (outfile == NULL) {
		printf("Can't create file %s",filename);
		return;
	}
	fprintf(outfile,"%s\n",projname);
	fprintf(outfile,"%s /align:16 /CO /NOD\n",projname);
	fprintf(outfile,"%s /map\n",projname);
	fprintf(outfile,"llibce os2\n");
	fprintf(outfile,"%s.def\n",projname);
	fclose(outfile);
	printf("Wrote file %s\n",filename);

	*tmpptr = '\0';
	strcat(filename,".H");

	/* create Header file */
	outfile = fopen(filename,"wt");
	if (outfile == NULL) {
		printf("Can't create file %s",filename);
		return;
	}
	fprintf(outfile,"/* file menu items */\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"#define     IDM_NEW      100\n");
	fprintf(outfile,"#define     IDM_OPEN     101\n");
	fprintf(outfile,"#define     IDM_SAVE     102\n");
	fprintf(outfile,"#define     IDM_SAVEAS   103\n");
	fprintf(outfile,"#define     IDM_PRINT    104\n");
	fprintf(outfile,"#define     IDM_EXIT     105\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"/* edit menu items */\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"#define     IDM_UNDO     200\n");
	fprintf(outfile,"#define     IDM_CUT      201\n");
	fprintf(outfile,"#define     IDM_COPY     202\n");
	fprintf(outfile,"#define     IDM_PASTE    203\n");
	fprintf(outfile,"#define     IDM_CLEAR    204\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"/* help menu items */\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"#define     IDM_ABOUT    106\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"/* Dialog and Resource IDs */\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"#define     FRAMERESID    49\n");
	fprintf(outfile,"#define     IDD_ABOUT    101\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"/* function prototypes */\n");
	fprintf(outfile,"\n");
	fprintf(outfile,"MRESULT CALLBACK %swindproc(HWND,USHORT,MPARAM,MPARAM);\n",projname);
	fprintf(outfile,"MRESULT CALLBACK aboutdlgproc(HWND,USHORT,MPARAM,MPARAM);\n");
	fclose(outfile);
	printf("Wrote file %s\n",filename);

	*tmpptr = '\0';
	strcat(filename,".DLG");

	/* create DiaLoG file */
	outfile = fopen(filename,"wt");
	if (outfile == NULL) {
		printf("Can't create file %s",filename);
		return;
	}
	fprintf(outfile,"DLGTEMPLATE IDD_ABOUT LOADONCALL MOVEABLE DISCARDABLE \n");
	fprintf(outfile,"BEGIN\n");
	fprintf(outfile,"    DIALOG \"\", IDD_ABOUT, 29, 74, 144, 43, FS_NOBYTEALIGN | FS_DLGBORDER | \n");
	fprintf(outfile,"                WS_CLIPSIBLINGS | WS_SAVEBITS\n");
	fprintf(outfile,"    BEGIN\n");
	fprintf(outfile,"        CONTROL \"Project Creator\", 2, 33, 15, 112, 8, WC_STATIC, \n");
	fprintf(outfile,"                SS_TEXT | DT_CENTER | DT_TOP | WS_GROUP | WS_VISIBLE\n");
	fprintf(outfile,"        CONTROL \"Generic Application\", 3, 37, 26, 108, 8, WC_STATIC, SS_TEXT | \n");
	fprintf(outfile,"                DT_CENTER | DT_TOP | WS_GROUP | WS_VISIBLE\n");
	fprintf(outfile,"        CONTROL \"Version 1.0\", 4, 41, 2, 102, 8, WC_STATIC, SS_TEXT | DT_CENTER | \n");
	fprintf(outfile,"                DT_TOP | WS_GROUP | WS_VISIBLE\n");
	fprintf(outfile,"        CONTROL \"OK\", 1, 5, 2, 32, 14, WC_BUTTON, BS_PUSHBUTTON | BS_DEFAULT | \n");
	fprintf(outfile,"                WS_GROUP | WS_TABSTOP | WS_VISIBLE\n");
	fprintf(outfile,"    END\n");
	fprintf(outfile,"END\n");
	fprintf(outfile,"\n");
	fclose(outfile);
	printf("Wrote file %s\n\n",filename);
}
