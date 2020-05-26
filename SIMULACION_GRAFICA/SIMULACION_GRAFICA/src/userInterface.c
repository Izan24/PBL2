#include "general.h"
#include "userInterface.h"
#include <math.h>

int init_menu(STARTEND* twoPoints, PNODEPOINT points, BUTTON* ALL_Buttons) {

	SDL_Event mouse;
	MOUSE_POS* position = (MOUSE_POS*)malloc(sizeof(MOUSE_POS));
	static int change_yes = 0, points_yes = 0, go_yes = 0, closeRequested = 0;

	if (SDL_PollEvent(&mouse))
	{
		if (SDL_MOUSEMOTION)
		{
			if (mouse.motion.x > 0 && mouse.motion.x <= WINDOW_WIDTH)
			{
				if (mouse.motion.y > 0 && mouse.motion.y <= WINDOW_HEIGHT)
				{
					position->x = mouse.motion.x;
					position->y = mouse.motion.y;
				}
			}

			change_yes = verify_pos_mouse(ALL_Buttons[0], position);
			points_yes = verify_pos_mouse(ALL_Buttons[1], position);
			go_yes = verify_pos_mouse(ALL_Buttons[2], position);
		}
	}

	select_texture(change_yes, ALL_Buttons[0]);
	select_texture(points_yes, ALL_Buttons[1]);
	select_texture(go_yes, ALL_Buttons[2]);

	switch (mouse.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_LEFT)
		{
			if (dist_mouse_button(ALL_Buttons[0], position))
			{
				closeRequested = deploy_menu_call(ALL_Buttons, position);
			}

			if (dist_mouse_button(ALL_Buttons[1], position))
			{

				//select_points_map(&twoPoints, points);
			}

			if (dist_mouse_button(ALL_Buttons[2], position))
			{
				if (twoPoints->startP != NULL && twoPoints->endP != NULL)
				{
					//aki el A star de furkolay y isan
				}
				else
				{
					error_message(ALL_Buttons[5]);
				}
			}
		}
		break;
	case SDL_QUIT:
		return 0;
	}

	return closeRequested;
}

int deploy_menu_call(BUTTON* ALL_Buttons, MOUSE_POS* position)
{
	SDL_Event mouse; int Swap_yes = 0, exit_yes = 0, bool = 0, closeRequested = 0;
	MOUSE_POS* position1 = (MOUSE_POS*)malloc(sizeof(MOUSE_POS));

	do
	{
		if (SDL_PollEvent(&mouse))
		{
			if (SDL_MOUSEMOTION)
			{
				if (mouse.motion.x > 0 && mouse.motion.x <= WINDOW_WIDTH)
				{
					if (mouse.motion.y > 0 && mouse.motion.y <= WINDOW_HEIGHT)
					{
						position1->x = mouse.motion.x;
						position1->y = mouse.motion.y;
					}
				}

				Swap_yes = verify_pos_mouse(ALL_Buttons[3], position1);
				exit_yes = verify_pos_mouse(ALL_Buttons[4], position1);
			
			}
		}

		select_texture(Swap_yes, ALL_Buttons[3]);
		select_texture(exit_yes, ALL_Buttons[4]);
		SDL_RenderPresent(rend);

		if (mouse.type == SDL_MOUSEBUTTONDOWN)
		{
			if (dist_mouse_button(ALL_Buttons[4], position1))
			{
				printf("F");
				
			}
			if (dist_mouse_button(ALL_Buttons[0], position1))
			{
				bool = 1;
			}
			if (dist_mouse_button(ALL_Buttons[3], position1))
			{
				sdl_destroy();
				closeRequested = 1;
				bool = 1;
			}
		}

	} while (bool == 0);

	return closeRequested;
}


int dist_mouse_button(BUTTON button, MOUSE_POS* position) {

	float distance = 0; int x, y; int buleano = 0;

	x = (button.dim.x + 37);
	y = (button.dim.y + 37);
	x = x - position->x;
	y = y - position->y;
	distance = (x * x) + (y * y);
	distance = sqrt(distance);
	if (distance < button.radius)
	{
		buleano = 1;
	}
	return buleano;
}

void select_texture(int which, BUTTON button) {

	if (which == 1) {
		SDL_QueryTexture(button.grey_ver, NULL, NULL, &button.dim.w, &button.dim.h);
		SDL_RenderCopy(rend, button.grey_ver, NULL, &button.dim);
	}
	else {
		SDL_QueryTexture(button.normal_ver, NULL, NULL, &button.dim.w, &button.dim.h);
		SDL_RenderCopy(rend, button.normal_ver, NULL, &button.dim);
	}
}

int verify_pos_mouse(BUTTON button, MOUSE_POS* position) {


	if (dist_mouse_button(button, position))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void init_buttons(BUTTON* ALL_Buttons)
{
	ALL_Buttons[0].normal_ver = bg_init("Button_menu.png");
	ALL_Buttons[0].grey_ver = bg_init("Button_menu_grey.png");
	ALL_Buttons[1].normal_ver = bg_init("Button_points.png");
	ALL_Buttons[1].grey_ver = bg_init("Button_points_grey.png");
	ALL_Buttons[2].normal_ver = bg_init("Button_go.png");
	ALL_Buttons[2].grey_ver = bg_init("Button_go_grey.png");

	ALL_Buttons[3].normal_ver = bg_init("exit_button.png");
	ALL_Buttons[3].grey_ver = bg_init("exit_button_grey.png");
	ALL_Buttons[4].normal_ver = bg_init("Swap_button.png");
	ALL_Buttons[4].grey_ver = bg_init("Swap_button_grey.png");

	ALL_Buttons[5].normal_ver = bg_init("error_message.png");
}

void error_message(BUTTON Error_button)
{
	int bool = 0;
	SDL_Event mouse1;

	SDL_QueryTexture(Error_button.normal_ver, NULL, NULL, &(Error_button.dim.w), &(Error_button.dim.h));
	SDL_RenderCopy(rend, Error_button.normal_ver, NULL, &Error_button);

	do
	{
		SDL_RenderPresent(rend);
		if (SDL_PollEvent(&mouse1))
		{
			if (mouse1.type == SDL_MOUSEBUTTONDOWN)
			{
				if (SDL_BUTTON_LEFT)
				{
					bool = 1;
				}
			}
		}

	} while (bool == 0);
}

void button_set_dim(BUTTON* ALL_Buttons)
{

	ALL_Buttons[0].dim.x = 10;
	ALL_Buttons[0].dim.y = 0;
	ALL_Buttons[0].dim.w = 75;
	ALL_Buttons[0].dim.h = 75;
	ALL_Buttons[0].radius = 37;

	
	ALL_Buttons[1].dim.x = 1250;
	ALL_Buttons[1].dim.y = 600;
	ALL_Buttons[1].dim.w = 75;
	ALL_Buttons[1].dim.h = 75;
	ALL_Buttons[1].radius = 37;
	

	ALL_Buttons[2].dim.x = 1250;
	ALL_Buttons[2].dim.y = 680;
	ALL_Buttons[2].dim.w = 75;
	ALL_Buttons[2].dim.h = 75;
	ALL_Buttons[2].radius = 37;
	

	ALL_Buttons[3].dim.x = 10;
	ALL_Buttons[3].dim.y = 200;
	ALL_Buttons[3].dim.w = 75;
	ALL_Buttons[3].dim.h = 75;
	ALL_Buttons[3].radius = 37;
	

	ALL_Buttons[4].dim.x = 10;
	ALL_Buttons[4].dim.y = 100;
	ALL_Buttons[4].dim.w = 75;
	ALL_Buttons[4].dim.h = 75;
	ALL_Buttons[4].radius = 37;


	ALL_Buttons[5].dim.x = 480;
	ALL_Buttons[5].dim.y = 234;
	ALL_Buttons[5].dim.w = 75;
	ALL_Buttons[5].dim.h = 75;
	


}