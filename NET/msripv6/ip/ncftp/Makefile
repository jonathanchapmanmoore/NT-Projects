CC=cl.exe -nologo
LINK=link.exe -nologo

!ifdef DEBUG
CFLAGS= -Od -Z7 -D_DEBUG -D_CONSOLE -DWIN32 -DMSRIPv6 -I. -I..\pdcurses -I..\msripv6\inc -I$(NTMAKEENV)
LINKFLAGS= -nologo -debug -pdb:none -subsystem:console -libpath:..\msripv6\wship6\obj\i386\checked
!else
CFLAGS= -Od -DNDEBUG -DWIN32 -DMSRIPv6 -I. -I..\pdcurses -I..\msripv6\inc -I$(NTMAKEENV)
LINKFLAGS= -nologo -release -subsystem:console -libpath:..\msripv6\wship6\obj\i386\free
!endif

ENTRYPOINT=

LIBS=..\pdcurses\obj\pdcurses.lib user32.lib wsock32.lib wship6.lib

OBJS =  bookmark.obj\
	cmdline.obj\
	cmdlist.obj\
	cmds.obj\
	complete.obj\
	cpp.obj\
	datesize.obj\
	ftp.obj\
	get.obj\
	getopt.obj\
	glob.obj\
	hostwin.obj\
	lgets.obj\
	linelist.obj\
	list.obj\
	macro.obj\
	main.obj\
	makeargv.obj\
	open.obj\
	prefs.obj\
	progress.obj\
	put.obj\
	rcmd.obj\
	sio.obj\
	strn.obj\
	tips.obj\
	util.obj\
	wgets.obj\
	win.obj\
	win32.obj\
	xfer.obj

all: ncftp.exe

ncftp.exe: $(OBJS)
	$(LINK) $(LINKFLAGS) @<<
	   $(OBJS) -out:ncftp.exe $(LIBS)
<<

config.h: Config.h.w32
	copy Config.h.w32 config.h

sys.h: win32.h Util.h Main.h Cmds.h Open.h Cmdline.h DateSize.h Prefs.h FTP.h Getopt.h Xfer.h Tips.h Version.h config.h
	touch sys.h


bookmark.obj: bookmark.c sys.h util.h bookmark.h ftp.h

cmdline.obj: cmdline.c sys.h Util.h Cmdline.h Cmds.h Main.h MakeArgv.h Open.h

cmdlist.obj: cmdlist.c Curses.h Util.h Main.h Open.h Cmds.h Glob.h List.h Get.h Put.h Hostwin.h Prefs.h Cmdline.h

cmds.obj: cmds.c sys.h Util.h RCmd.h Cmds.h Cmdline.h List.h MakeArgv.h Macro.h Main.h DateSize.h Open.h Glob.h Getopt.h FTP.h Cpp.h Prefs.h Tips.h Version.h 

complete.obj: complete.c sys.h LineList.h Cmdline.h Complete.h Prefs.h Util.h List.h

cpp.obj: cpp.c sys.h Curses.h Util.h RCmd.h Cpp.h

datesize.obj: datesize.c sys.h Util.h RCmd.h Cmds.h Xfer.h List.h DateSize.h

ftp.obj: ftp.c sys.h Util.h FTP.h RCmd.h

get.obj: get.c Util.h RCmd.h Xfer.h Cmds.h Glob.h Get.h DateSize.h List.h Getopt.h sys.h

getopt.obj: getopt.c sys.h util.h getopt.h

glob.obj: glob.c sys.h Util.h RCmd.h Glob.h Xfer.h List.h Main.h

hostwin.obj: hostwin.c sys.h curses.h Util.h Cmds.h Open.h Hostwin.h

lgets.obj: lgets.c sys.h util.h lgets.h

list.obj: list.c sys.h Util.h RCmd.h Xfer.h Cmds.h List.h Glob.h

linelist.obj: linelist.c sys.h

macro.obj: macro.c sys.h Util.h Macro.h Cmds.h Cmdline.h MakeArgv.h

main.obj: main.c sys.h

makeargv.obj: makeargv.c sys.h util.h makeargv.h

open.obj: open.c sys.h Open.h Util.h GetPass.h Cmds.h RCmd.h FTP.h Get.h Getopt.h Macro.h Hostwin.h Main.h

prefs.obj: prefs.c sys.h curses.h wgets.h Util.h Cmds.h Progress.h Hostwin.h Prefs.h RCmd.h Main.h

progress.obj: progress.c sys.h Util.h Cmds.h Xfer.h Progress.h GetPass.h Main.h curses.h

put.obj: put.c sys.h Util.h RCmd.h Xfer.h Cmds.h Get.h Getopt.h Glob.h Put.h

rcmd.obj: rcmd.c sys.h Util.h RCmd.h Open.h Main.h Xfer.h FTP.h

sio.obj: sio.c sys.h sio.h

strn.obj: strn.c sys.h strn.h

tips.obj: tips.c sys.h util.h tips.h

util.obj: util.c sys.h Util.h Main.h Curses.h

wgets.obj: wgets.c sys.h util.h curses.h

win.obj: win.c sys.h Util.h Main.h Version.h RCmd.h LGets.h GetPass.h

win32.obj: win32.c win32.h

xfer.obj: xfer.c sys.h Util.h Main.h Xfer.h RCmd.h FTP.h Progress.h Sio.h

######
# Maintainance Targets
######

clean:
	-del *.obj
	-del *.tr2
	-del *.exe
	-del *.td2
