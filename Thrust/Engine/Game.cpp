/****************************************************************************************** 
 *	Chili DirectX Framework Version 14.03.22											  *	
 *	Game.cpp																			  *
 *	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "Game.h"
#include "Polyclosed.h"
#include "Mat3.h"
#define FPS(x) 1000.f / x


Game::Game(HWND hWnd, KeyboardServer& kServer, MouseServer& mServer)
: gfx(hWnd),
audio(hWnd),
kbd(kServer),
mouse(mServer),
viewport(gfx, { 0, D3DGraphics::SCREENHEIGHT - 1, 0, D3DGraphics::SCREENWIDTH - 1 }),
camera(viewport, viewport.GetWidth(), viewport.GetHeight()),
ship("shipd.dxf", { -2026,226 }),
map("map.dxf"),
timePrev(timer.GetTimeMilli())
{
}

Game::~Game()
{
}

void Game::Go()
{
	UpdateTime();
	HandleInput();
	
	//don't update simulation more than x times/second
	auto step = FPS(60);
	while (timeLag >= step){
		UpdateModel();
		timeLag -= step;
	}

	Render();
}

inline void Game::UpdateTime(){
	auto timeCurrent = timer.GetTimeMilli();
	auto elapsed = timeCurrent - timePrev;
	timePrev = timeCurrent;
	timeLag += elapsed;
}

void Game::Render(){
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void test(){
	
	Vec2 v = { 2, 3 };

	Mat3 sc = Mat3::Scale(2);
	Mat3 tr = Mat3::Translation({1,1});
	
	Mat3 cm = sc * tr;

	Vec2 r1 = cm * v;

	Vec2 r2 = tr * sc * v;

}

void Game::HandleInput(){
	auto key = kbd.ReadKey();
	switch (key.GetCode())
	{

	case VK_F1:
		if (key.IsPress())
		{
			ship.Reset();
		}
		break;
	case VK_LEFT:
		if (key.IsPress())
		{
			ship.Spin(-1.f);
		}
		else if (key.IsRelease()){
			ship.StopSpinnig(-1.f);
		}
		break;

	case VK_RIGHT:
		if (key.IsPress())
		{
			ship.Spin(1.f);
		}
		else if (key.IsRelease()){
			ship.StopSpinnig(1.f);
		}
		break;

	case VK_UP:
		if (key.IsPress())
		{
			ship.Thrust();
		}
		else if (key.IsRelease()){
			ship.StopThrusting();
		}
		break;
	}
	//test();
	/*switch (mouse.ReadMouse().GetType())
	{
	case MouseEvent::WheelUp:
	scale *= 1.1;
	break;
	case MouseEvent::WheelDown:
	scale /= 1.1;
	break;
	}*/
}

void Game::UpdateModel( )
{
	ship.Update();
}

void Game::ComposeFrame()
{
	gfx.DrawRect(viewport.getClip(), RED);
	ship.FocusOn(camera);
	camera.Draw(ship.getDrawable());
	camera.Draw(map.getDrawable());
}
