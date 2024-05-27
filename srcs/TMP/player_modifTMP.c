/*static bool is_valid_move(t_grid *grid, double new_x, double new_y)
{
    int grid_x = (int)(new_x + 0.25); //attention on bloque certains murs mais on en traverse d'autres
    int grid_x2 = (int)(new_x - 0.25); //attention on bloque certains murs mais on en traverse d'autres
    int grid_y = (int)(new_y + 0.25);
    int grid_y2 = (int)(new_y - 0.25);

    if (grid_x < 0 || grid_x >= grid->width || grid_y < 0 || grid_y >= grid->height || grid_x2 < 0 || grid_x2 >= grid->width || grid_y2 < 0 || grid_y2 >= grid->height) //test
    {
        return false; // Out of bounds
    }

    if (grid->content[grid_y][grid_x] == '1' || grid->content[grid_y2][grid_x] == '1' || grid->content[grid_y][grid_x2] == '1' || grid->content[grid_y2][grid_x2] == '1') // condition en test
    {
        return false; // Collision with wall
    }
    return true;
}*/

/*static void modif_player_pos(t_key_handl key, t_player *player, t_grid *grid)
{
    double new_x = player->pos.x;
    double new_y = player->pos.y;
    double movement_perp_x = player->movement.y;
    double movement_perp_y = -player->movement.x;

    if (key.key_w == 1)
    {
        new_x += player->movement.x;
        new_y += player->movement.y;
    }
    else if (key.key_s == 1)
    {
        new_x -= player->movement.x;
        new_y -= player->movement.y;
    }
    else if (key.key_a == 1)
    {
        new_x += movement_perp_x;
        new_y += movement_perp_y;
    }
    else if (key.key_d == 1)
    {
        new_x -= movement_perp_x;
        new_y -= movement_perp_y;
    }

    if (is_valid_move(grid, new_x, new_y))
    {
        player->pos.x = new_x;
        player->pos.y = new_y;
    }
}*/
