#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "src/basic_widget.hpp"
#include "src/button.hpp"

class Widget : public BasicWidget {
 public:
  Widget(const std::wstring& title) : BasicWidget(title) { button_.Show(); }

 private:
  Button button_ =
      Button(this, 100, 100, L"Hello ZAWARUOD TOKIWA TOMARE", []() {
        MessageBoxW(0, L"Hello!", L"Message", MB_ICONINFORMATION | MB_OK);
      });
  CallbackResult PaintEvent() override {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(GetHandle(), &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOWFRAME));

    EndPaint(GetHandle(), &ps);
    return 0;
  }
};

#endif  // WIDGET_HPP_
