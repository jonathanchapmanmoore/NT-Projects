/*
***************************************************************************
* This file comprises part of PDCurses. PDCurses is Public Domain software.
* You may use this code for whatever purposes you desire. This software
* is provided AS IS with NO WARRANTY whatsoever.
* Should this software be used in another application, an acknowledgement
* that PDCurses code is used would be appreciated, but is not mandatory.
*
* Any changes which you make to this software which may improve or enhance
* it, should be forwarded to the current maintainer for the benefit of 
* other users.
*
* The only restriction placed on this code is that no distribution of
* modified PDCurses code be made under the PDCurses name, by anyone
* other than the current maintainer.
* 
* See the file maintain.er for details of the current maintainer.
***************************************************************************
*/
#define	CURSES_LIBRARY	1
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <curses.h>

#ifdef PDCDEBUG
char *rcsid_PDCprint  = "$Id$";
#endif

/*man-start*********************************************************************

  PDC_print()	- Provides primitive access to the BIOS printer functions

  PDCurses Description:
 	This is a private PDCurses routine.

 	Implements write/init/read printer services at the BIOS level.

 	This provides the basic support that PDCurses needs to dump the
 	contents of windows or pads to the printer attached to the BIOS
 	printer port.

  PDCurses Return Value:
 	See the BIOS INT 0x17 specifications.

  PDCurses Errors:
 	See the BIOS INT 0x17 specifications.

  Portability:
 	PDCurses	int PDC_print( int cmd, int byte, int port );

**man-end**********************************************************************/

/***********************************************************************/
#ifdef HAVE_PROTO
int	PDC_print(int cmd, int byte, int port)
#else
int	PDC_print(cmd,byte,port)
int cmd;
int byte;
int port;
#endif
/***********************************************************************/
{
	int	status = 0;

#ifdef PDCDEBUG
	if (trace_on) PDC_debug("PDC_print() - called\n");
#endif

	regs.h.ah = (unsigned char)cmd;
	regs.h.al = (unsigned char)byte;
# ifdef WATCOMC
	regs.w.dx = (unsigned int)port;
# else
	regs.x.dx = (unsigned int)port;
# endif
	int86(0x17, &regs, &regs);
	status = regs.h.ah;
	return (status);

}
