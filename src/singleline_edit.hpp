#ifndef SINGLELINE_EDIT_HPP_
#define SINGLELINE_EDIT_HPP_

#include "src/edit.hpp"

class SingleLineEdit : public Edit {
 public:
  SingleLineEdit(BasicWidget* parent, int pos_x = CW_USEDEFAULT,
                 int pos_y = CW_USEDEFAULT, int width = CW_USEDEFAULT);
};

#endif  // SINGLELINE_EDIT_HPP_
