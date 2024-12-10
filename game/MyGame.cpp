#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) : 
		spring(750, 150, "spring.bmp", CColor::Blue(), 0),
		marker(750, 300, "marker.bmp", CColor::Blue(), 0)
{
	k = 1;
	d = 1;
	spring.SetPivot(750, 0);
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	// user input
	if (IsKeyDown(SDLK_DOWN))
	{
		marker.SetVelocity(0, 0);
		marker.Move(0, 1);
	}
	else
	if (IsKeyDown(SDLK_UP))
	{
		marker.SetVelocity(0, 0);
		marker.Move(0, 1);
	}
	else
	{
		// Implementation of the Hooke's Law
		float y = marker.GetY() - 300;
		marker.Accelerate(0, -k * y);
		marker.SetSpeed(marker.GetSpeed() * d);
	}
	marker.Update(t);

	// animate the spring
	spring.SetSize(64, marker.GetY());

	// create trace
	trace.push_back(new CSpriteOval(marker.GetLeft(), marker.GetY(), 6, CColor::Red(192), t));
	trace.back()->SetVelocity(-300, 0);

	// update the trace
	for each (CSprite *pSprite in trace)
	{
		pSprite->Update(t);
		if (pSprite->GetX() < -5)
			pSprite->Delete();
	}
	trace.remove_if(deleted);
}

void CMyGame::OnDraw(CGraphics* g)
{
	*g << font(14) << top;
	*g << "Spring coefficient k = " << k << endl;
	*g << "Damp coefficient   d = " << d << endl;
	*g << bottom;
	*g << "K / D / Shift to modify coefficients" << endl;
	*g << "UP and DOWN arrows to move the spring" << endl;
	
	for each (CSprite *pSprite in trace)
		pSprite->Draw(g);
	spring.Draw(g);
	marker.Draw(g);
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	StartGame();	// this allows to start the game immediately
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();

	if (sym == SDLK_k && (mod & KMOD_SHIFT) == 0)
		k += 0.1f;
	if (sym == SDLK_k && (mod & KMOD_SHIFT) != 0)
		k -= 0.1f;
	if (sym == SDLK_d && (mod & KMOD_SHIFT) == 0)
		d += 0.001f;
	if (sym == SDLK_d && (mod & KMOD_SHIFT) != 0)
		d -= 0.001f;
	d = min(d, 1); d = max(d, 0); k = max(k, 0);
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
