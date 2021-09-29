#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "src/basic_widget.hpp"
#include "src/button.hpp"
#include "src/label.hpp"
#include "src/listbox.hpp"

class Widget : public BasicWidget {
 public:
  Widget(const std::wstring& title)
      : BasicWidget(title, WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_GROUP,
                    CW_USEDEFAULT, CW_USEDEFAULT, 500, 500) {
    button_.Show();
  }

 private:
  Label label_ = Label(this, 0, 0, L"Fuck ты");
  ListBox listbox_ = ListBox(this, 100, 0, 200, 200);

  Button button_ = Button(this, 0, 20, L"Юникод", [this]() {
    MessageBoxW(0, L"Текст", L"Заголовок", MB_ICONINFORMATION | MB_OK);
    listbox_.AddLine(L"Fuck you!");
  });
};

#endif  // WIDGET_HPP_
