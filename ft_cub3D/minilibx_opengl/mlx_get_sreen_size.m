#import <AppKit/NSScreen.h>

void	mlx_get_screen_size(int *w, int *h)
{
	NSRect screen_frame = [[NSScreen mainScreen] frame];
	*w = (int)screen_frame.size.height;
	*h = (int)screen_frame.size.width;
}
