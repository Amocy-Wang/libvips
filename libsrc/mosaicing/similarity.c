/* @(#) im_similarity_area() ... similarity transform. Like affine, but
 * @(#) rotate/scale only.
 * @(#)
 * @(#) int im_similarity_area(in, out, a, b, dx, dy, w, h, x, y)
 * @(#) IMAGE *in, *out;
 * @(#) double a, b, dx, dy;
 * @(#) int w, h, x, y;
 * @(#)
 * @(#) Forward transform
 * @(#) X = a * x - b * y + dx
 * @(#) Y = b * x + a * y + dy
 * @(#)
 * @(#) x and y are the coordinates in input image.  
 * @(#) X and Y are the coordinates in output image.
 * @(#) (0,0) is the upper left corner.
 * @(#)
 * @(#) a and b DO NOT correspond to scale and angle directly
 * @(#)
 * @(#) scale = sqrt(a*a + b*b) , angle = arctan(a/b)
 * @(#)
 * @(#) im_similarity_area() returns 0 on success and -1 on error
 * @(#)  
 *
 * 3/3/98 JC
 *	- redone as wrapper for im_affine(), compatibility only
 * 8/4/04
 *	- transform rounding redone as part of the new im_embed thing
 */

/*

    This file is part of VIPS.
    
    VIPS is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 */

/*

    These files are distributed with VIPS - http://www.vips.ecs.soton.ac.uk

 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /*HAVE_CONFIG_H*/
#include <vips/intl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <vips/vips.h>

#include "transform.h"
#include "merge.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif /*WITH_DMALLOC*/

int 
im_similarity_area( IMAGE *in, IMAGE *out, 
	double a, double b, double dx, double dy, 
	int ox, int oy, int ow, int oh )
{
	Transformation trn;

	trn.oarea.left = ox;
	trn.oarea.top = oy;
	trn.oarea.width = ow;
	trn.oarea.height = oh;
	trn.iarea.left = 0;
	trn.iarea.top = 0;
	trn.iarea.width = in->Xsize;
	trn.iarea.height = in->Ysize;
	trn.a = a;
	trn.b = -b;
	trn.c = b;
	trn.d = a;
	trn.dx = dx;
	trn.dy = dy;

	return( im__affine( in, out, &trn ) );
}

/* Output the rect holding all our input PELs.
 */
int 
im_similarity( IMAGE *in, IMAGE *out, 
	double a, double b, double dx, double dy )
{	
	Transformation trn;

	trn.iarea.left = 0;
	trn.iarea.top = 0;
	trn.iarea.width = in->Xsize;
	trn.iarea.height = in->Ysize;
	trn.a = a;
	trn.b = -b;
	trn.c = b;
	trn.d = a;
	trn.dx = dx;
	trn.dy = dy;
	im__transform_set_area( &trn );

	if( im__affine( in, out, &trn ) )
		return( -1 );

	return( 0 );
}
