#include "src/edit.hpp"

int Edit::GetTextLength() const { return GetWindowTextLength(GetHandle()); }

std::wstring Edit::GetText() const {
  std::wstring result(GetTextLength(), L'\0');
  GetWindowText(GetHandle(), result.data(), result.size());
  return result;
}

void Edit::SetText(const std::wstring& text) {
  SetWindowText(GetHandle(), text.data());
}

void Edit::ClearText() { SetText(L""); }

Edit::Edit(BasicWidget* parent, int pos_x, int pos_y, int width, int height,
           int style, int ex_style)
    : BasicWidget(L"", style | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_LEFT,
                  pos_x, pos_y, width, height, parent, L"Edit",
                  ex_style | WS_EX_CLIENTEDGE) {}
