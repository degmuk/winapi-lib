#ifndef EDIT_HPP_
#define EDIT_HPP_

#include "src/basic_widget.hpp"

class Edit : public BasicWidget {
 public:
  int GetTextLength() const;
  std::wstring GetText() const;

  void SetText(const std::wstring& text);
  void ClearText();

 protected:
  Edit(BasicWidget* parent, int pos_x = CW_USEDEFAULT,
       int pos_y = CW_USEDEFAULT, int width = CW_USEDEFAULT,
       int height = CW_USEDEFAULT, int style = 0, int ex_style = 0);
};

#endif  // EDIT_HPP_
