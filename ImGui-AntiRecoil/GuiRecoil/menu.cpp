#include "menu.h"

// ImGuiのComboで使用する
const char* InputName[] = { "SendInput", "mouse_event" };
const char* TypeName[] = { "Normal", "Shake", "Circle" };

// ImGuiのメニュー用
void Menu::m_Menu()
{
    // ImGuiのウィンドウの設定 / 作成等
    ImGui::SetNextWindowPos(ImVec2(-1, 0));
    ImGui::SetNextWindowSize(ImVec2(Width - 14, Height - 37)); // なんかズレるので少し調整
    ImGui::Begin(skCrypt("(removed)"), (bool*)NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    
    // チェックボックス
    ImGui::Checkbox(skCrypt("AntiRecoil"), &g.AntiRecoil);
    ImGui::Checkbox(skCrypt("Randomize"), &g.Random);
    ImGui::Checkbox(skCrypt("Sound"), &g.Sound);

    // 改行と横線みたいなの
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    // Sliderとかの幅 (開始)
    ImGui::PushItemWidth(150.f);

    ImGui::Text(skCrypt("[+] Recoil"));
    // ドロップダウンのリストから選択するやつ
    ImGui::Combo(skCrypt("Type"), &g.Type, TypeName, IM_ARRAYSIZE(TypeName));
    // Sliderとかの幅 (終了)
    ImGui::PopItemWidth();
    
    ImGui::NewLine();
    ImGui::PushItemWidth(225.f);

    if (!g.Random)
    {
        ImGui::SliderInt(skCrypt("##recoil"), &g.Recoil, 1, 30); ImGui::SameLine();
        ImGui::Text(skCrypt("Recoil"));
        switch (g.Type)
        {
        case 0:
            break;
        case 1:
            ImGui::SliderInt(skCrypt("##Downward"), &g.RecoilUnder, 0, 30); ImGui::SameLine();
            ImGui::Text(skCrypt("Downward"));
            break;
        case 2:
            ImGui::SliderInt(skCrypt("##Downward"), &g.RecoilUnder, 0, 30); ImGui::SameLine();
            ImGui::Text(skCrypt("Downward"));
            break;
        default:
            break;
        }
    }
    else
    {
        // ここら辺、変数が違っても文字列が同じだとなんか同期されちゃったような覚えがある。注意
        ImGui::SliderInt(skCrypt("##MinValue"), &g.MinValue, 1, 5); ImGui::SameLine();
        ImGui::Text(skCrypt("MinValue"));

        ImGui::SliderInt(skCrypt("##MaxValue"), &g.MaxValue, 6, 30); ImGui::SameLine();
        ImGui::Text(skCrypt("MaxValue"));

        switch (g.Type)
        {
        case 0:
            break;
        case 1:
            ImGui::SliderInt(skCrypt("##Downward"), &g.RecoilUnder, 0, 30); ImGui::SameLine();
            ImGui::Text(skCrypt("Downward"));
            break;
        case 2:
            ImGui::SliderInt(skCrypt("##Downward"), &g.RecoilUnder, 0, 30); ImGui::SameLine();
            ImGui::Text(skCrypt("Downward"));
            break;
        default:
            break;
        }
    }

    ImGui::SliderInt(skCrypt("##Sleep"), &g.SleepTime, 1, 150); ImGui::SameLine();
    ImGui::Text(skCrypt("SleepTime"));

    ImGui::PopItemWidth();

    ImGui::SetCursorPosY(300);
    ImGui::Text(skCrypt("[+] Setting"));
    ImGui::BeginChild(skCrypt("##SettingW"), ImVec2(75, 130));

    ImGui::NewLine();

    static int select = 1;
    if (ImGui::Button(skCrypt("KeyBinder"), ImVec2(75, 30)))
        select = 1;
    if (ImGui::Button(skCrypt("Recoil"), ImVec2(75, 30)))
        select = 2;
    if (ImGui::Button(skCrypt("Menu"), ImVec2(75, 30)))
        select = 3;

    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(105, 300));
    ImGui::BeginChild(skCrypt("##Other"), ImVec2(350, 147));
    switch (select)
    {
    case 1:
        ImGui::Text(skCrypt("[+] RecoilKey"));

        if (g.BindState)
            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), skCrypt("Press any Key!"));
        else
            ImGui::Text(skCrypt(" "));

        if (ImGui::Button("1st Key", ImVec2(100, 30)))
        {
            g.BindId = 1;
            g.KeyBindButton = true;
        }

        ImGui::SameLine();

        if (ImGui::Button("2nd Key", ImVec2(100, 30)))
        {
            g.BindId = 2;
            g.KeyBindButton = true;
        }

        // KeyNamesからg.RecoilKey1st(割り当てたキー)番目のやつを出力する
        ImGui::Text("1st : %s", KeyNames[g.RecoilKey1st], g.RecoilKey1st);
        ImGui::Text("2nd : %s", KeyNames[g.RecoilKey2nd], g.RecoilKey2nd);
        ImGui::NewLine();
        break;
    case 2:
        ImGui::PushItemWidth(150.f);

        ImGui::Text(skCrypt("[+] Recoil Setting"));

        if (g.BindState)
            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), skCrypt("Press any Key!"));
        else
            ImGui::Text(skCrypt(" "));

        if (ImGui::Button("Toggle Key", ImVec2(100, 30)))
        {
            g.BindId = 3;
            g.KeyBindButton = true;
        }

        ImGui::Text("Key : %s", KeyNames[g.ToggleKey]);

        ImGui::NewLine();

        ImGui::Combo(skCrypt("Input Type"), &g.InputStyle, InputName, IM_ARRAYSIZE(InputName));

        ImGui::PopItemWidth();
        break;
    case 3:
        ImGui::PushItemWidth(115.f);

        // Window Hide
        ImGui::Text(skCrypt("[+] Window HIDE Key"));

        if (g.BindState)
            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), skCrypt("Press any Key!"));
        else
            ImGui::Text(skCrypt(" "));

        if (ImGui::Button("Hide Key", ImVec2(100, 30)))
        {
            g.BindId = 4;
            g.KeyBindButton = true;
        }

        ImGui::Text("Key : %s", KeyNames[g.HideKey]);

        ImGui::NewLine();

        ImGui::PopItemWidth();
        break;
    default:
        break;
    }

    ImGui::EndChild();

    ImGui::NewLine();

    ImGui::SetCursorPosY(450);
    ImGui::Text(skCrypt("[+] Config"));
    if (ImGui::Button(skCrypt("Save"), ImVec2(125, 35)))
    {
        // 削除されました
    }
    ImGui::SameLine();
    if (ImGui::Button(skCrypt("Load"), ImVec2(125, 35)))
    {
        // 削除されました
    }

    ImGui::End();
}

// ImGuiのスタイル。色も変更可能
void Menu::LoadStyle()
{
    // Style
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.f;
    style.FrameBorderSize = 0.f;
    style.ChildBorderSize = 1.f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.ChildRounding = 4.f;
    style.FrameRounding = 2.f;
    style.GrabMinSize = 6;
}
