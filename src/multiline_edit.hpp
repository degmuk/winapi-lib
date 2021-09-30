#ifndef MULTILINE_EDIT_HPP_
#define MULTILINE_EDIT_HPP_

#include "src/edit.hpp"

class MultiLineEdit : public Edit {
 public:
  MultiLineEdit(BasicWidget* parent, int pos_x = CW_USEDEFAULT,
                int pos_y = CW_USEDEFAULT, int width = CW_USEDEFAULT,
                int height = CW_USEDEFAULT);
};

#endif  // MULTILINE_EDIT_HPP_
