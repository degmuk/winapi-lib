#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <functional>
#include <string>

#include "src/basic_widget.hpp"

class Button : public BasicWidget {
 public:
  using Callback = std::function<void()>;

  Button(
      BasicWidget* parent, int pos_x, int pos_y, const std::wstring& title,
      Callback callback = []() {});

  void SetCallback(Callback callback);

  void Clicked();

 private:
  Callback on_click_callback_;
};

#endif  // BUTTON_HPP_
