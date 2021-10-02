#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "src/basic_widget.hpp"
#include "src/button.hpp"
#include "src/label.hpp"
#include "src/listbox.hpp"
#include "src/multiline_edit.hpp"
#include "src/singleline_edit.hpp"

class Widget : public BasicWidget {
 public:
  Widget(const std::wstring& title)
      : BasicWidget(title, WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_GROUP,
                    CW_USEDEFAULT, CW_USEDEFAULT, 500, 500) {
    button_.Show();
  }

 private:
  Label label_ = Label(this, 0, 0, L"Текст0");
  ListBox listbox_ = ListBox(this, 100, 0, 200, 200);

  Button button_ = Button(this, 0, 20, L"Юникод", [this]() {
    MessageBoxW(0, L"Текст", L"Заголовок", MB_ICONINFORMATION | MB_OK);
    listbox_.AddLine(L"Текст1!");
  });

  SingleLineEdit edit_ = SingleLineEdit(this, 320, 0, 100);

  MultiLineEdit medit_ = MultiLineEdit(this, 320, 40, 150, 150);
};

#endif  // WIDGET_HPP_
