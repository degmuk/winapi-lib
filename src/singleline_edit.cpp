#include "src/singleline_edit.hpp"

SingleLineEdit::SingleLineEdit(BasicWidget* parent, int pos_x, int pos_y,
                               int width)
    : Edit(parent, pos_x, pos_y, width, CW_USEDEFAULT, ES_AUTOHSCROLL) {
  SIZE size = GetTextSize(L"a");
  size.cx = width;
  size.cy += 10;
  SetSize(size);
}
