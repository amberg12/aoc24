#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 99999999
#define UNDEFINED 0
struct vec2 {
  size_t x, y;
};

char grid[1024][256] = {0};
size_t xlen = 0;
size_t ylen = 0;

void
debug_print (void)
{
  for (size_t i = 0; i < ylen; i++)
    printf("%s\n", grid[i]);
  puts("");
}

static long long int dist[1024][1024] = {0};
static char was_direction[1024][1024] = {0};

int
cmp_distance(const void *lhs, const void *rhs)
{
  struct vec2 lhsdref = *(struct vec2 *)lhs;
  struct vec2 rhsdref = *(struct vec2 *)rhs;
  return dist[lhsdref.y][lhsdref.x] - dist[rhsdref.y][rhsdref.x];
}

long long int
get_answer (struct vec2 starting_point)
{
  /* https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode */
  char dir = '>';
  long long int target_dist = INF;

  struct vec2 *q = malloc (sizeof *q * 1024 * 1024);
  struct vec2 *q_csr = q;
  size_t qelems = 0;
  
  for (size_t y = 0; y < ylen; y++)
    {
      for (size_t x = 0; x < xlen; x++)
	{
	  dist[y][x] = INF;
	  if (grid[y][x] != '#')
	    q[qelems++] = (struct vec2) { .x = x, .y = y };
	}
    }

  dist[starting_point.y][starting_point.x] = 0;
  was_direction[starting_point.y][starting_point.x] = dir;

  while (qelems)
    {
      qsort(q_csr, qelems, sizeof(struct vec2), cmp_distance);
      struct vec2 u = *q_csr;
      q_csr++;
      qelems--;
      
      if (grid[u.y][u.x] != 'E') grid [u.y][u.x] = 'x';
      else continue;
      dir = (was_direction[u.y][u.x] == 0) ? dir : was_direction[u.y][u.x];
      if (grid[u.y + 1][u.x] != '#')
	{
	  long long int alt = dist[u.y][u.x] + 1;
	  if (dir == '>' || dir == '<')
	    alt += 1000;
	  if (alt < dist[u.y + 1][u.x])
	    {
	      dist[u.y + 1][u.x] = alt;
	      was_direction[u.y + 1][u.x] = 'v';
	    }
	  
	  if (grid[u.y + 1][u.x] == 'E')
	    if (alt < target_dist) target_dist = alt;
	}

      if (grid[u.y - 1][u.x] != '#') {
	long long int alt = dist[u.y][u.x] + 1;
	if (dir == '>' || dir == '<')
	  alt += 1000;

	if (alt < dist[u.y - 1][u.x])
	  {
	    dist[u.y - 1][u.x] = alt;
	    was_direction[u.y - 1][u.x] = '^';
	  }
	if (grid[u.y - 1][u.x] == 'E')
	  if (alt < target_dist) target_dist = alt;
      }

      if (grid[u.y][u.x + 1] != '#') {
	long long int alt = dist[u.y][u.x] + 1;
	if (dir == '^' || dir == 'v')
	  alt += 1000;

	if (alt < dist[u.y][u.x + 1])
	  {
	    dist[u.y][u.x + 1] = alt;
	    was_direction[u.y][u.x + 1] = '>';
	  }
	if (grid[u.y][u.x + 1] == 'E')
	  if (alt < target_dist) target_dist = alt;
      }

      if (grid[u.y][u.x - 1] != '#') {
	long long int alt = dist[u.y][u.x] + 1;
	if (dir == '^' || dir == 'v')
	  alt += 1000;

	if (alt < dist[u.y][u.x - 1])
	  {
	    dist[u.y][u.x - 1] = alt;
	    was_direction[u.y][u.x - 1] = '<';
	  }
	if (grid[u.y][u.x - 1] == 'E')
	  if (alt < target_dist) target_dist = alt;
      }
    }
  return target_dist;
}

int
main (void)
{
  char scanbuf[256] = {0};
  struct vec2 start;
  while (fgets (scanbuf, sizeof scanbuf, stdin))
    {
      char *cursor = scanbuf;
      xlen = 0;
      while (*cursor != '\n')
	{
	  grid[ylen][xlen] = *cursor;
	  if (*cursor == 'S')
	    start = (struct vec2) { .x = xlen, .y = ylen };
	  cursor++;
	  xlen++;
	}
      ylen++;
    }
  long long int sol = get_answer (start);
  printf("%lld\n", sol);
}
