#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include <cstdlib>




int random_range(int min, int max){
	return (std::rand() % (max - min) + min);
}

int random_range(int range[2]){
	return random_range(range[0], range[1]);
}




int * get_random_integer_array(int range[][2], int integer_count){
	int * new_arr = new int[integer_count];

	while(integer_count--) new_arr[integer_count] = random_range(range[integer_count]);

	return new_arr;
}




int ** get_random_integer_matrix(int range[][2], int array_count, int array_integer_count){

	int ** new_random_point_list{ new int *[array_count] };

	while(array_count--) new_random_point_list[array_count] = get_random_integer_array(range, array_integer_count);

	return new_random_point_list;
}




double distance(int p1[2], int p2[2]){

	int x{p1[0] - p2[0]};
	int y{p1[1] - p2[1]};
	
	return x * x + y * y;
}




int main(int argc, char ** argv){

	std::srand(std::time(0));

	int WINDOW_WIDTH{std::atoi(argv[1])}, WINDOW_LENGTH{std::atoi(argv[2])};
	
	int POINT_COUNT{std::atoi(argv[3])};
	int DRAW_CENTERS{std::atoi(argv[4])};
	int POINT_RADIUS{std::atoi(argv[5])};

	int point_coords_range[2][2] = {{0, WINDOW_WIDTH}, {0, WINDOW_LENGTH}};
	int point_colors_range[3][2] = {{0, 255}, {0, 255}, {0, 255}};

	int ** point_list   = get_random_integer_matrix(point_coords_range, POINT_COUNT, 2); 
	int ** point_colors = get_random_integer_matrix(point_colors_range, POINT_COUNT+1, 3);

	point_colors[POINT_COUNT][0] = 0;
	point_colors[POINT_COUNT][1] = 0;
	point_colors[POINT_COUNT][2] = 0;

	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_LENGTH, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	int x, y;
	int RGB_COEFFICIENT{255/POINT_COUNT};

	int curr_point[2], nearest_point;
	double min_distance, curr_distance;

	for(x = 0; x < WINDOW_WIDTH; ++x){
		for(y = 0; y < WINDOW_LENGTH; ++y){

			curr_point[0] = x;
			curr_point[1] = y;

			nearest_point = 0;

			for(int i{}, min_distance = WINDOW_WIDTH * WINDOW_LENGTH; i < POINT_COUNT; ++i){
				
				curr_distance = distance(point_list[i], curr_point);
				
				if(DRAW_CENTERS && curr_distance < POINT_RADIUS) nearest_point = POINT_COUNT;
				else if(curr_distance < min_distance){
					min_distance = curr_distance;
					nearest_point = i;
				}
			}

			SDL_SetRenderDrawColor(renderer, point_colors[nearest_point][0], point_colors[nearest_point][1], point_colors[nearest_point][2], 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}


	SDL_RenderPresent(renderer);

	while(1){
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
