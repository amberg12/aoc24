/*
  I didn't come up with the automated idea for finding the christmas tree
  myself.  Online I saw someone mention that a low entropy means a tree,
  so I took that to mean a particularly low variance.
 */

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#define ROOMX 101
#define ROOMY 103

struct robot {
  unsigned int x, y;
  int vx, vy;
};

struct robot robots[1024] = {0};
size_t robot_count = 0;

char display_grid[256][256] = {0};

int
main (int argc, char **argv)
{
  struct robot *this_robot = robots;
  while (fscanf (stdin, "p=%u,%u v=%d,%d\n",
		 &this_robot->x,
		 &this_robot->y,
		 &this_robot->vx,
		 &this_robot->vy) == 4)
    {
      this_robot++;
      robot_count++;
    }

  long long int sol = 0;
  while (true)
    {
      double this_var_x = 0;
      double this_var_y = 0;
      double avg_x = 0;
      double avg_y = 0;
      for (int i = 0; i < robot_count; i++)
	{
	  robots[i].x = (robots[i].x + robots[i].vx + ROOMX) % ROOMX;
	  robots[i].y = (robots[i].y + robots[i].vy + ROOMY) % ROOMY;
	  avg_x += robots[i].x;
	  avg_y += robots[i].y;
	}
      avg_x /= robot_count;
      avg_y /= robot_count;
      for (int i = 0; i < robot_count; i++)
	{
	  this_var_x += (robots[i].x - avg_x) * (robots[i].x - avg_x);
	  this_var_y += (robots[i].y - avg_y) * (robots[i].y - avg_y);
	}
      this_var_x /= robot_count;
      this_var_y /= robot_count;
      sol++;
      printf("%lld: %lf %lf\n", sol, this_var_x, this_var_y);
      if (this_var_x < 650 && this_var_y < 650) break;
    }
  
  printf ("%lld", sol);
}
