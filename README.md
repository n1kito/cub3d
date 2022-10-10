<h1 align="center">cub3d 🧟🔫</h1>
<p align="center">
<img src="img/wolfenstein.gif" width="200px" alt="wolfenstein gif"><br />
Our work on the 42Born2Code <b>cub3d</b> project.<br /><br />
</p>

>  This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

[![mjallada's 42 minishell Score](https://badge42.vercel.app/api/v2/cl4dwkra3004009maahzpjn6g/project/2635687)](https://github.com/JaeSeoKim/badge42)

# TODO

- [ ] Map needs error when no starting position
- [ ] Map file should only accept one map

# Research

## Raycasting theory

### Radians

For this project we are working with **radians** as opposed to degrees, which are the unit most of us as most familiar with.

Here are some measurements using radians:  
$180° = π radians$  
$360° = 2π radians$

**To convert degrees to radians:** $$α_{rad} = α_{deg} * \frac{π}{180}$$
**To convert radians to degrees:** $$α_{deg} = α_{rad} * \frac{180}{π}$$  

In `cub3d`, we need to decide on a Field Of View (`FOV`) for the player and store it somewhere.  
If we decide to use a field of view of 60°, we can store it in radians by doing the following:

```int  fov_angle = 60 * (π / 180);```

# Process

Variables that we will need to store:  
`fov_angle`: angle for the field of view of the player (ex: `60`)  
`map_row_count` & `map_col_count`: number of rows and colums in the map  
`tile_size`: size of one "square" on the map (ex: `32`)  
`ray_count`: how many rays are present in the `fov_angle` (should be = `window width`)  
`ray_angle`: size of one ray in radians (= `fov_angle` / `ray_count`)
`minimp

## Parsing

**How to check that the map is closed**
- For each charcter of the map, we check if it's on the edge (if one of its neigbors is NULL) and if so that it's a `1`. `P` or `0` should never neighbor an empty char.

## Error Handling

<details><summary><i>(+ click to open)</i></summary>

> Check for leaks for every one of these possible errors.

---
- **General checks**
  - [x] The program should not crash if launched with no environment using `env -i` or `env --unset=PATH`
    - `env -i` is handled when I check the return value of `mlx_init()`
    - `env --unset=PATH`, turns out the `PATH` variable is never used by the MinilibX.
---
- **Map file checking**
  - [x] The map filename has the .ber extension.
  - [x] The map filename starts with a `.` (wrong for me, according to the subject that states maps should be named `*.ber`) 
  - [x] The "map" argument is a folder not a file.
  - [x] The map filename has several extensions (`map.coucou.ber`) (I accept this)
  - [x] The map file is empty.
  - [x] The map file does not exist.
  - [x] No access to map file (`chmod 0`).
---
</details>

# Resources

- [Pikuma's course: Raycasting Engine Programming](https://pikuma.com/courses/raycasting-engine-tutorial-algorithm-javascript) ⭐⭐ 
