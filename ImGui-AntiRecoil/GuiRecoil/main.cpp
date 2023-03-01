#include "menu.h"

// 各クラスから関数を呼び出したいので
Recoil r;
Menu m;

// アプリケーション自体のウィンドウ
HWND hwnd = NULL;

// recoil.cppで定義されているのをここmain.cppでも使えるようにする
extern bool IsKeyDown(int VK);

bool ShowMenu = true;

// 本体は下の方にあるけどあらかじめ宣言しておく
void Check();
void KeyBinder();

// スレッド用関数
void RecoiLoop()
{
    while (g.Active)
    {
        r.RecoilMain();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    ExitThread(0);
}

// このプログラムのメイン
// int main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ImGui Example DX11がベース
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, L"Nz", L"Window", NULL };

    // 既に実行されていないかチェック
    HWND cw = FindWindow(wc.lpszClassName, wc.lpszMenuName);
    if (cw)
    {
        MessageBox(NULL, L"実行中のアプリケーションが存在します", L"警告", MB_TOPMOST | MB_OK);
        return 0;
    }

    // アプリケーションのウィンドウを作成
    RegisterClassExW(&wc);
    hwnd = CreateWindow(wc.lpszClassName, wc.lpszMenuName, WS_SYSMENU | WS_MINIMIZEBOX, 100, 100, Width, Height, NULL, NULL, wc.hInstance, NULL);

    // Init D3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }
    
    // Update window
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;

    // ImGuiのスタイルのロード
    m.LoadStyle();

    // バックグラウンドの色。そこまで関係ない
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // スレッドの作成
    g.Active = true;
    CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)RecoiLoop, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyBinder, NULL, 0, NULL);

    // Menu Loop
    while (g.Active)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                g.Active = false;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 自身のウィンドウを表示/非表示にするやつ
        static bool tmp = false;
        if (IsKeyDown(g.HideKey) && IsKeyDown(g.HideKey) && !tmp)
        {
            ShowMenu = !ShowMenu;
            tmp = true;
        }
        else if (!IsKeyDown(g.HideKey) && !IsKeyDown(g.HideKey) && tmp)
        {
            tmp = false;
        }

        // もし"ShowMenu == true"だったら自身のウィンドウとメニューを表示
        if (ShowMenu)
        {
            ShowWindow(hwnd, SW_SHOW);
            m.m_Menu();
        } 
        else
        {
            ShowWindow(hwnd, SW_HIDE);
        }

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// GetAsyncKeyStateを0x87回ループしてどのキーが入力されているかチェックし、それを割り当て
void KeyBinder()
{
    while (g.Active)
    {
        // メニュー側でKeyBindのボタンが押されたら
        if (g.KeyBindButton)
        {
            // 無限ループ
            while (true)
            {
                // メニュー用。trueの間メニューで"Press any Key!"が表示される。
                g.BindState = true;

                for (int i = 0; i < 0x87; i++)
                {
                    // キーが押されたら
                    if (IsKeyDown(i))
                    {
                        // 押されたキーがEscapeだったら
                        if (i == 27)
                        {
                            // 各対応するキーを"NONE"にする
                            switch (g.BindId) // 押されたボタンごとに違うのでそれで判定
                            {
                            case 1:
                                g.RecoilKey1st = 0;
                                break;
                            case 2:
                                g.RecoilKey2nd = 0;
                                break;
                            case 3:
                                g.ToggleKey = 0;
                                break;
                            case 4:
                                g.HideKey = 0;
                                break;
                            default:
                                break;
                            }

                            // 終了
                            g.BindId = 0;
                            g.BindState = false;
                            g.KeyBindButton = false;

                            break;
                        }
                        // Escape以外だったら
                        else
                        {
                            // 押されたキーを変数にバインドする
                            switch (g.BindId)
                            {
                            case 1:
                                g.RecoilKey1st = i;
                                break;
                            case 2:
                                g.RecoilKey2nd = i;
                                break;
                            case 3:
                                g.ToggleKey = i;
                                break;
                            case 4:
                                g.HideKey = i;
                                break;
                            default:
                                break;
                            }

                            // 終了
                            g.BindId = 0;
                            g.BindState = false;
                            g.KeyBindButton = false;

                            break;
                        }
                    }
                }

                // 割り当てが完了したらループから抜ける
                if (!g.BindState)
                    break;
            }
        }
        else
        {
            // CPUリソース削減用。これがないとRyzen9 5900XでもCPUを12%くらい使う。
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // キーの重複がないか、その他変数の値が異常ではないか等
        Check();
    }

    ExitThread(0);
}

// 脳筋VALUE CHECKER
void Check()
{
    // ボタンで変数をいじれるようにしていた時の名残。いらないかもしれない
    if (g.Recoil < 1)
        g.Recoil = 1;
    else if (g.Recoil > 30)
        g.Recoil = 30;
    else if (g.RecoilUnder < 0)
        g.RecoilUnder = 0;
    else if (g.RecoilUnder > 30)
        g.RecoilUnder = 30;
    else if (g.SleepTime < 1)
        g.SleepTime = 1;
    else if (g.SleepTime > 150)
        g.SleepTime = 150;
    else if (g.MinValue < 1)
        g.MinValue = 1;
    else if (g.MinValue > 5)
        g.MinValue = 5;
    else if (g.MaxValue < 6)
        g.MaxValue = 6;
    else if (g.MaxValue > 30)
        g.MaxValue = 30;

    // 割り当てたキーが重複していないか
    if (g.RecoilKey1st == g.RecoilKey2nd)
        g.RecoilKey2nd = 0;
    
    // 1stキーに何も割り当てられていなかったら2ndにも割り当てない
    if (g.RecoilKey1st == 0)
        g.RecoilKey2nd = 0;

    // Hide Keyにマウスの1と2を割り当てられないようにする
    if (g.HideKey == 1 || g.HideKey == 2)
        g.HideKey = 0;
    
    // Toggle Keyにも。
    if (g.ToggleKey == 1 || g.ToggleKey == 2)
        g.ToggleKey = 0;
}
