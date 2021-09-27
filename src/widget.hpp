#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "src/basic_widget.hpp"

class Widget : public BasicWidget {
 public:
  Widget(const std::wstring& title) : BasicWidget(title) {}

 private:
  CallbackResult DestroyEvent() override {
    PostQuitMessage(0);
    return 0;
  }

  CallbackResult PaintEvent() override {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(GetHandle(), &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOWFRAME));

    EndPaint(GetHandle(), &ps);
    return 0;
  }
};

#endif  // WIDGET_HPP_
