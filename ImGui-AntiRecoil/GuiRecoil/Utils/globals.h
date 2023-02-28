#pragma once

// ƒOƒ[ƒoƒ‹•Ï”‚ğ‚±‚±‚Å‚Ü‚Æ‚ß‚ÄŠÇ—‚·‚é
struct global
{
	// System
	bool Active = false;

	// Recoil
	bool AntiRecoil = false;
	bool Random = false;
	bool Sound = false;
	int InputStyle = 0;
	int Type = 0;
	int RecoilKey1st = 0;
	int RecoilKey2nd = 0;
	int ToggleKey = 0;
	int Recoil = 1;
	int RecoilUnder = 1;
	int SleepTime = 1;
	int MinValue = 1;
	int MaxValue = 6;

	// KeyBinder
	bool KeyBindButton = false;
	int BindId = 0;
	bool BindState = false;

	// Window
	int HideKey = 0;
};

extern global g;