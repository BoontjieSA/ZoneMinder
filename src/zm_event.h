//
// ZoneMinder Core Interfaces, $Date$, $Revision$
// Copyright (C) 2003  Philip Coombes
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 

#ifndef ZM_EVENT_H
#define ZM_EVENT_H

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
//#include <math.h>
#include <time.h>
//#include <signal.h>
//#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <sys/time.h>
//#include <sys/mman.h>
//#include <sys/ioctl.h>
#include <mysql/mysql.h>

#include "zm.h"
#include "zm_image.h"

class Monitor;

//
// Class describing events, i.e. captured periods of activity.
//
class Event
{
protected:
	int				id;
	Monitor			*monitor;
	struct timeval	start_time;
	struct timeval	end_time;
	int				start_frame_id;
	int				end_frame_id;
	int				frames;
	int				alarm_frames;
	unsigned int	tot_score;
	unsigned int	max_score;
	char			path[PATH_MAX];

public:
	Event( Monitor *p_monitor, struct timeval p_start_time );
	~Event();

	int Id() const { return( id ); }
	int Frames() const { return( frames ); }
	int AlarmFrames() const { return( alarm_frames ); }

	void AddFrame( struct timeval timestamp, const Image *image, const Image *alarm_frame=NULL, unsigned int score=0 );

	static void StreamEvent( const char *path, int event_id, unsigned long refresh=100, FILE *fd=stdout );
};

#endif // ZM_EVENT_H