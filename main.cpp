/*
 * main.cpp
 *
 *  Created on: 16 juil. 2014
 *      Author: mickael
 */

#include <iostream>
#include "SDLView.h"

int main(int argc, char *argv[])
{
	//TODO unused params
	(void)argc;(void)argv;

	int exit_status = EXIT_FAILURE;

	std::cout << "Hello World !" << std::endl;
	try{
		SDLView mainFrame;
		exit_status = mainFrame.Launch_event_loop();
	} catch (int exception) {
		switch(exception){
		case SDL_ERROR:
			SDLView::Print_sdl_err();
			break;
		default:
			std::cerr << "Unknown exception" << std::endl;
			break;
		}
		exit_status = EXIT_FAILURE;
	}
	return exit_status;
}


