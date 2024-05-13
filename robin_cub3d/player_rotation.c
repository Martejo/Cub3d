
typedef struct s_player
{
	char	start_dir; // le symbole permettant de definir la direction initiale des vecteurs representant le regard du joueur (par rapport au repere orthonorme informatique) N => dirx = 0 diry = -1 ? S => dirx 0 diry 1 
	//la position du joueur sur la map2d
	double	posx; 
	double	posy;

	// on connait l'angle initial du regard du joueur gr^ace a la lettre N = -Pi/2 
	//si le regard devie, on a juste a faire varier la valeur de l'angle de vue
	//la valeur d' angle augmente quand on tourne le regard `a droite et decroit quand on le tourne `a gauche 
	//attention quand on fait un tour complet dans un sens ou dans l' autre il faut reinitialiser les valeurs d' angle (on 360 + droite = 0)
	
	int angle; //valeur d' angle entre 0 et 360
	double	dirx; // on l'obtient ewn faisant cos(notre angle)
	double	diry; // on l' obtient en faisant sin(notre angle)
}	t_player;

void init_player_angle(t_player *player, const char dir)
{
    if(dir == 'E')
        player->angle = 0;
    else if(dir == 'S')
        player->angle = 90;
    else if(dir == 'W')
        player->angle = 180;
    else if(dir == 'N')
        player->angle = 270;
    else
        exit_error(E_PLAYER_BAD_DIR)
}

// Supposons que ces fonctions soient appelées en réponse à des entrées utilisateur
void turn_left(t_player *player) {
    player->angle -= 5;  // Tourner de 5 degrés à gauche
    if (player->angle < 0) player->angle += 360;  // Gardez l'angle dans l'intervalle 0-360
}

void turn_right(t_player *player) {
    player->angle += 5;  // Tourner de 5 degrés à droite
    if (player->angle >= 360) player->angle -= 360;  // Gardez l'angle dans l'intervalle 0-360
}

void rotate_player(t_player *player) 
{
    //old anglde ne sert a rien si on utilise cette fonction apres un input de joueur ? 
    static old_angle;
    if (player->angle != old_angle)
    {
        player->dirx = cos(player->angle);
        player->diry = sin(player->angle);
        old_angle = player->angle;
    }
}

// Exemple d'utilisation :
rotate_player(&dirX, &dirY, rotation_angle);  // rotation_angle doit être en radians