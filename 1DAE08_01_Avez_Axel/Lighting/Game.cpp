#include "pch.h"
#include <iostream>
#include <cassert>
#include <sstream>
#include "Game.h"
#include "utils.h"
#include "Vector2f.h"

Game::Game( const Window& window )
	:m_Window{ window }
{	 
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	TestVector2fStruct();
}

void Game::Cleanup( )
{

}

void Game::Update( float elapsedSec )
{

}

void Game::Draw( ) const
{
	utils::ClearBackground( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		//std::cout << "Right arrow key released\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		//std::cout << "Left mouse button released\n";
		//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		break;
	}
	case SDL_BUTTON_RIGHT:
		//std::cout << "Right mouse button released\n";
		break;
	case SDL_BUTTON_MIDDLE:
		//std::cout << "Middle mouse button released\n";
		break;
	}
}



void Game::TestVector2fStruct()
{
	// Initialize
	Vector2f v1{ 2.0f, 3.0f };
	Vector2f v2{ 6.0f, 7.0f };
	Vector2f v1Copy{};
	Vector2f v2Copy{};
	Vector2f v1Res{ };
	Vector2f v2Res{ };
	Vector2f opRes{};
	Vector2f expectedRes{};
	float factor1{};
	float factor2{};
	int testCntr{};

	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f = -Vector2f\n";
	//v1Copy.Set(v1.x, v1.y);
	//v1Res.Set(-v1.x, -v1.y);
	//opRes = -v1; // The operation
	//assert(opRes.Equals(v1Res));
	//assert(v1.Equals(v1Copy));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f = +Vector2f\n";
	//v1Copy.Set(v1.x, v1.y);
	//v1Res.Set(v1.x, v1.y);
	//opRes = +v1; // The operation
	//assert(opRes.Equals(v1Res));
	//assert(v1.Equals(v1Copy));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f *= float\n";
	//factor1 = rand() % 10 + 1.f;
	//v1Copy.Set(v1.x, v1.y);
	//v1Res.Set(v1Copy.x *= factor1, v1Copy.y *= factor1);
	//v1 *= factor1; // The operation
	//assert(v1.Equals(v1Res));

	//factor1 = rand() % 5 + 1.f;
	//factor2 = rand() % 5 + 6.f;
	//v1Copy.Set(v1.x, v1.y);
	//v1Res.Set((v1Copy.x *= factor1) *= factor2, (v1Copy.y *= factor1) *= factor2);
	//(v1 *= factor1) *= factor2; // The operation, a reference should be returned
	//assert(v1.Equals(v1Res));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f /= float\n";
	//factor1 = float(rand() % 10 + 1);
	//v1Copy.Set(v1.x, v1.y);
	//v1Res.Set(v1Copy.x /= factor1, v1Copy.y /= factor1);
	//v1 /= factor1; // The operation
	//assert(v1.Equals(v1Res));
	//v1Copy.Set(v1.x, v1.y);
	//v1Res.Set((v1Copy.x /= factor1) /= factor2, (v1Copy.y /= factor1) /= factor2);
	//(v1 /= factor1) /= factor2; // A reference should be returned
	//assert(v1.Equals(v1Res));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f = float * Vector2f\n";
	//factor1 = rand() % 10 + 1.f;
	//v1.Set(5.0f, 3.0f);
	//v1Copy.Set(v1.x, v1.y);
	//expectedRes.Set(factor1 * v1Copy.x, factor1 * v1Copy.y);
	//opRes = factor1 * v1; // The operation
	//assert(opRes.Equals(expectedRes));
	//assert(v1.Equals(v1Copy));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f = Vector2f  * float\n";
	//factor1 = float(rand() % 10 + 1);
	//v1Copy.Set(v1.x, v1.y);
	//expectedRes.Set(v1Copy.x * factor1, v1Copy.y  * factor1);
	//opRes = v1 * factor1; // The operation
	//assert(opRes.Equals(expectedRes));
	//assert(v1.Equals(v1Copy));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f = Vector2f  / float\n";
	//factor1 = float(rand() % 10 + 1);
	//v1Copy.Set(v1.x, v1.y);
	//expectedRes.Set(v1Copy.x / factor1, v1Copy.y / factor1);
	//opRes = v1 / factor1; // The operation
	//assert(opRes.Equals(expectedRes));
	//assert(v1.Equals(v1Copy));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f += Vector2f\n";
	//v1Res.Set(v1.x, v1.y);
	//v2Res.Set(v2.x, v2.y);
	//v1Res.x += v2Res.x;
	//v1Res.y += v2Res.y;
	//v1 += v2; // The operation
	//assert(v1.Equals(v1Res));
	//assert(v2.Equals(v2Res));
	//v1Res.x += v2Res.x += v2Res.x;
	//v1Res.y += v2Res.y += v2Res.y;
	//v1 += v2 += v2; // The cascading operation
	//assert(v1.Equals(v1Res));
	//assert(v2.Equals(v2Res));
	//(v1Res.x += v2Res.x) += v2Res.x;
	//(v1Res.y += v2Res.y) += v2Res.y;
	//(v1 += v2) += v2; // A reference is returned
	//assert(v1.Equals(v1Res));
	//assert(v2.Equals(v2Res));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f -= Vector2f\n";
	//v1Res.Set(v1.x, v1.y);
	//v2Res.Set(v2.x, v2.y);
	//v1Res.x -= v2Res.x;
	//v1Res.y -= v2Res.y;
	//v1 -= v2; // The operation
	//assert(v1.Equals(v1Res));
	//assert(v2.Equals(v2Res));
	//v1Res.x -= v2Res.x -= v2Res.x;
	//v1Res.y -= v2Res.y -= v2Res.y;
	//v1 -= v2 -= v2; // The cascading operation
	//assert(v1.Equals(v1Res));
	//assert(v2.Equals(v2Res));
	//(v1Res.x -= v2Res.x) -= v2Res.x;
	//(v1Res.y -= v2Res.y) -= v2Res.y;
	//(v1 -= v2) -= v2; // A reference is returned
	//assert(v1.Equals(v1Res));
	//assert(v2.Equals(v2Res));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f = Vector2f + Vector2f\n";
	//expectedRes.Set(v1.x + v2.x, v1.y + v2.y);
	//v1Copy.Set(v1.x, v1.y);
	//v2Copy.Set(v2.x, v2.y);
	//opRes = v1 + v2; // The operation
	//assert(opRes.Equals(expectedRes));
	//assert(v1.Equals(v1Copy));
	//assert(v2.Equals(v2Copy));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f = Vector2f - Vector2f\n";
	//expectedRes.Set(v1.x - v2.x, v1.y - v2.y);
	//v1Copy.Set(v1.x, v1.y);
	//v2Copy.Set(v2.x, v2.y);
	//opRes = v1 - v2; // The operation
	//assert(opRes.Equals(expectedRes));
	//assert(v1.Equals(v1Copy));
	//assert(v2.Equals(v2Copy));
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f == Vector2f\n";
	//assert(v1 == v1);
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: Vector2f != Vector2f\n";
	//v1Copy.Set(v1.x, v1.y);
	//v1 *= 2.0f;
	//assert(v1Copy != v1);
	//std::cout << "ok\n";


	//++testCntr;
	//std::cout << "\n==> " << testCntr << ". Test of: std::ostream << Vector2f\n";
	//std::stringstream testStream;
	//testStream << v1; // The operation
	//std::string v1String = v1.ToString();
	//std::string opString{ testStream.str() };
	//std::string::size_type foundPos = opString.find(v1String);
	//assert(foundPos != std::string::npos);
	//std::cout << v1 << std::endl; // The operation in cascade
	//std::cout << "ok\n";
}
