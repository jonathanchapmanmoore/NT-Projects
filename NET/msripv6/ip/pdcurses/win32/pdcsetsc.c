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
#define	INCLUDE_WINDOWS_H
#include <curses.h>

#ifdef PDCDEBUG
char *rcsid_PDCsetsc  = "$Id$";
#endif

extern HANDLE hConOut;

/*man-start*********************************************************************

  PDC_set_80x25()	- force a known screen state: 80x25 text mode.

  PDCurses Description:
 	This is a private PDCurses function.

 	Forces the appropriate 80x25 alpha mode given the display adapter.

 	Since we currently do not support changing the virtual console size,
 	this routine is a NOP under Flexos.

  PDCurses Return Value:
 	This function returns OK upon success otherwise ERR is returned.

  PDCurses Errors:
 	No errors are defined for this routine.

  Portability:
 	PDCurses	int	PDC_set_80x25( void );

**man-end**********************************************************************/

int	PDC_set_80x25(void)
{

#ifdef PDCDEBUG
	if (trace_on) PDC_debug("PDC_set_80x25() - called\n");
#endif

	return(OK);
}

/*man-start*********************************************************************

  PDC_set_cursor_mode()	- Set the cursor start and stop scan lines.

  PDCurses Description:
 	Sets the cursor type to begin in scan line startrow and end in
 	scan line endrow.  Both values should be 0-31.

  PDCurses Return Value:
 	This function returns OK on success and ERR on error.

  PDCurses Errors:
 	No errors are defined for this function.

  Portability:
 	PDCurses	int PDC_set_cursor_mode( int startrow, int endrow );

**man-end**********************************************************************/

int	PDC_set_cursor_mode( int startrow, int endrow )
{

#ifdef PDCDEBUG
	if (trace_on) PDC_debug("PDC_set_cursor_mode() - called: startrow %d endrow %d\n",startrow,endrow);
#endif

	return(OK);
}

/*man-start*********************************************************************

  PDC_set_font()	- sets the current font size

  PDCurses Description:
 	This is a private PDCurses function.

 	This routine sets the current font size, if the adapter allows
 	such a change.

  PDCurses Return Value:
 	This function returns OK upon success otherwise ERR is returned.

  PDCurses Errors:
 	It is an error to attempt to change the font size on a "bogus"
 	adapter.  The reason for this is that we have a known video
 	adapter identity problem.  e.g. Two adapters report the same
 	identifying characteristics.

 	It is also an error to attempt to change the size of the Flexos
 	console (as there is currently no support for that).

  Portability:
 	PDCurses	int	PDC_set_font( int size );

**man-end**********************************************************************/

int	PDC_set_font(int size)
{

#ifdef PDCDEBUG
	if (trace_on) PDC_debug("PDC_set_font() - called\n");
#endif

	return(OK);
}

/*man-start*********************************************************************

  PDC_set_rows()	- sets the physical number of rows on screen

  PDCurses Description:
 	This is a private PDCurses function.

 	This routine attempts to set the number of rows on the physical
 	screen to the passed value.

  PDCurses Return Value:
 	This function returns OK upon success otherwise ERR is returned.

  PDCurses Errors:
 	It is an error to attempt to change the screen size on a "bogus"
 	adapter.  The reason for this is that we have a known video
 	adapter identity problem.  e.g. Two adapters report the same
 	identifying characteristics.

 	It is also an error to attempt to change the size of the Flexos
 	console (as there is currently no support for that).

  Portability:
 	PDCurses	int	PDC_set_rows( int rows );

**man-end**********************************************************************/

int	PDC_set_rows(int rows)
{

#ifdef PDCDEBUG
	if (trace_on) PDC_debug("PDC_set_rows() - called\n");
#endif

	return(0);
}

/*man-start*********************************************************************

  PDC_set_scrn_mode()	- Set BIOS Video Mode

  PDCurses Description:
 	Sets the BIOS Video Mode Number ONLY if it is different from
 	the current video mode.  This routine is for DOS systems only.

  PDCurses Return Value:
 	This function returns OK on success and ERR on error.

  PDCurses Errors:
 	No errors are defined for this function.

  Portability:
 	PDCurses	int PDC_set_scrn_mode( int new_mode );

**man-end**********************************************************************/

int	PDC_set_scrn_mode(int new_mode)
{

#ifdef PDCDEBUG
	if (trace_on) PDC_debug("PDC_set_scrn_mode() - called\n");
#endif

	return(OK); /* this is N/A */
}
/***********************************************************************/
#ifdef HAVE_PROTO
int	PDC_curs_set(int visibility)
#else
int	PDC_curs_set(visibility)
int visibility;
#endif
/***********************************************************************/
{
 CONSOLE_CURSOR_INFO cci;
 int ret_vis=0;
 DWORD rc=0;

#ifdef PDCDEBUG
	if (trace_on) PDC_debug("PDC_curs_set() - called: visibility=%d\n",visibility);
#endif

	ret_vis = SP->visibility;
	SP->visibility = visibility;

	if (GetConsoleCursorInfo(hConOut,&cci) == FALSE)
		rc = GetLastError();

	switch(visibility)
	{
		case 0:                 /* invisible */
			cci.bVisible = FALSE;
			cci.dwSize = 1;
			break;
		case 2:                 /* highly visible */
			cci.bVisible = TRUE;
			cci.dwSize = 90;
			break;
		default:                /* normal visibility */
			cci.bVisible = TRUE;
			cci.dwSize = 13;
			break;
	}

	if (SetConsoleCursorInfo(hConOut,&cci) == FALSE)
		rc = GetLastError();

	return(ret_vis);
}
