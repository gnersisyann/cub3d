#ifndef CUB3D_H
#define CUB3D_H

typedef struct s_data {
  void *mlx;
  void *win;
  int map_fd;
  char *map_path;
  char *north_texture;
  char *south_texture;
  char *west_texture;
  char *east_texture;
  int floor_color;
  int ceiling_color;
  int player_x;
  int player_y;
  int player_direction;
} t_data;

#endif