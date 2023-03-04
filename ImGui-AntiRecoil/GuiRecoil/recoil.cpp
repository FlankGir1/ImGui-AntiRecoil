#include "recoil.h"

int rdm = 0;

bool IsKeyDown(int VK)
{
	return (GetAsyncKeyState(VK) & 0x8000) != 0;
}

int GenerateValue(int Min, int Max)
{
	int v1 = 0;
	v1 = rand() % Max + Min;

	return v1;
}

void mouse_move(int x, int y)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
}

void Recoil::RecoilMain()
{
	// 2nd key
	if (g.RecoilKey2nd != 0)
	{
		switch (g.InputStyle)
		{
		case 0:
			if (g.AntiRecoil)
			{
				switch (g.Type)
				{
				case 0:
					while (IsKeyDown(g.RecoilKey1st) && IsKeyDown(g.RecoilKey2nd))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_move(0, g.Recoil);
						Sleep(g.SleepTime);
					}
					break;
				case 1:
					while (IsKeyDown(g.RecoilKey1st) && IsKeyDown(g.RecoilKey2nd))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_move(g.Recoil, -g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(-g.Recoil, g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(0, g.RecoilUnder);
						Sleep(g.SleepTime);
					}
					break;
				case 2:
					while (IsKeyDown(g.RecoilKey1st) && IsKeyDown(g.RecoilKey2nd))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_move(-g.Recoil, g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(g.Recoil, g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(g.Recoil, -g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(-g.Recoil, -g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(0, g.RecoilUnder);
						Sleep(g.SleepTime);
					}
					break;
				default:
					break;
				}
			}
			break;
		case 1:
			if (g.AntiRecoil)
			{
				switch (g.Type)
				{
				case 0:
					while (IsKeyDown(g.RecoilKey1st) && IsKeyDown(g.RecoilKey2nd))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_event(MOUSEEVENTF_MOVE, 0, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
					}
					break;
				case 1:
					while (IsKeyDown(g.RecoilKey1st) && IsKeyDown(g.RecoilKey2nd))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_event(MOUSEEVENTF_MOVE, g.Recoil, -g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, -g.Recoil, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, 0, g.RecoilUnder, NULL, NULL);
						Sleep(g.SleepTime);
					}
					break;
				case 2:
					while (IsKeyDown(g.RecoilKey1st) && IsKeyDown(g.RecoilKey2nd))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_event(MOUSEEVENTF_MOVE, -g.Recoil, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, g.Recoil, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, g.Recoil, -g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, -g.Recoil, -g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, 0, g.RecoilUnder, NULL, NULL);
						Sleep(g.SleepTime);
					}
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	// 1st key only
	else
	{
		switch (g.InputStyle)
		{
		case 0:
			if (g.AntiRecoil)
			{
				switch (g.Type)
				{
				case 0:
					while (IsKeyDown(g.RecoilKey1st))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_move(0, g.Recoil);
						Sleep(g.SleepTime);
					}
					break;
				case 1:
					while (IsKeyDown(g.RecoilKey1st))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_move(g.Recoil, -g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(-g.Recoil, g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(0, g.RecoilUnder);
						Sleep(g.SleepTime);
					}
					break;
				case 2:
					while (IsKeyDown(g.RecoilKey1st))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_move(-g.Recoil, g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(g.Recoil, g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(g.Recoil, -g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(-g.Recoil, -g.Recoil);
						Sleep(g.SleepTime);
						mouse_move(0, g.RecoilUnder);
						Sleep(g.SleepTime);
					}
					break;
				default:
					break;
				}
			}
			break;
		case 1:
			if (g.AntiRecoil)
			{
				switch (g.Type)
				{
				case 0:
					while (IsKeyDown(g.RecoilKey1st))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_event(MOUSEEVENTF_MOVE, 0, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
					}
					break;
				case 1:
					while (IsKeyDown(g.RecoilKey1st))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_event(MOUSEEVENTF_MOVE, g.Recoil, -g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, -g.Recoil, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, 0, g.RecoilUnder, NULL, NULL);
						Sleep(g.SleepTime);
					}
					break;
				case 2:
					while (IsKeyDown(g.RecoilKey1st))
					{
						if (g.Random)
							g.Recoil = GenerateValue(g.MinValue, g.MaxValue);

						mouse_event(MOUSEEVENTF_MOVE, -g.Recoil, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, g.Recoil, g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, g.Recoil, -g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, -g.Recoil, -g.Recoil, NULL, NULL);
						Sleep(g.SleepTime);
						mouse_event(MOUSEEVENTF_MOVE, 0, g.RecoilUnder, NULL, NULL);
						Sleep(g.SleepTime);
					}
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	// AntiRecoil Toggle
	static bool AntiRecoilToggle = false;
	if (IsKeyDown(g.ToggleKey) && !AntiRecoilToggle)
	{
		g.AntiRecoil = !g.AntiRecoil;
		AntiRecoilToggle = true;
	}
	else if (!IsKeyDown(g.ToggleKey) && AntiRecoilToggle)
	{
		AntiRecoilToggle = false;
		// Toggle Sound
		if (g.Sound && !g.AntiRecoil)
			Beep(440, 100);
		else if (g.Sound && g.AntiRecoil)
			Beep(880, 100);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(5));
}
