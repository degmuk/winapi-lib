#include "src/label.hpp"

Label::Label(BasicWidget* parent, int pos_x, int pos_y,
             const std::wstring& text)
    : BasicWidget(text, WS_VISIBLE, pos_x, pos_y, 1, 1, parent, L"Static") {
  SIZE size = GetTextSize(text);
  size.cx += 2;
  size.cy += 2;
  SetSize(size);
}
