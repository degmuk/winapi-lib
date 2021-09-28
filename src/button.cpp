#include "src/button.hpp"

#include <utility>

Button::Button(BasicWidget* parent, int pos_x, int pos_y,
               const std::wstring& title, Callback callback)
    : BasicWidget(title, pos_x, pos_y, 1, 1, parent, L"Button"),
      on_click_callback_(std::move(callback)) {
  SIZE size = GetTextSize(title);
  size.cx += 16;
  size.cy += 8;
  SetSize(size);
}

void Button::SetCallback(Callback callback) {
  on_click_callback_ = std::move(callback);
}

void Button::Clicked() { on_click_callback_(); }
