#include <stdio.h>
#include <stddef.h>

#define ROOMX 101
#define ROOMY 103
#define ROOMX_H (ROOMX / 2)
#define ROOMY_H (ROOMY / 2)

struct robot {
  unsigned int x, y;
  int vx, vy;
};

struct robot robots[1024] = {0};
size_t robot_count = 0;

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

  for (int s = 0; s < 100; s++)
    {
      for (int i = 0; i < robot_count; i++)
	{
	  robots[i].x = (robots[i].x + robots[i].vx + ROOMX) % ROOMX;
	  robots[i].y = (robots[i].y + robots[i].vy + ROOMY) % ROOMY;
	}
    }

  long long int q1 = 0;
  long long int q2 = 0;
  long long int q3 = 0;
  long long int q4 = 0;
    for (int i = 0; i < robot_count; i++)
    {
      if (robots[i].x < ROOMX_H && robots[i].y < ROOMY_H)
	{
	  q1++;
	}
      else if (robots[i].x < ROOMX_H && robots[i].y > ROOMY_H)
	{
	  q2++;
	}
      else if (robots[i].x > ROOMX_H && robots[i].y < ROOMY_H)
	{
	  q3++;
	}
      else if (robots[i].x > ROOMX_H && robots[i].y > ROOMY_H)
	{
	  q4++;
	}
    }
  long long int sol = q1 * q2 * q3 * q4;
      
  printf("%lld %lld %lld %lld %lld\n", q1, q2, q3, q4, sol);
}
