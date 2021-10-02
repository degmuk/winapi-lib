#ifndef LABEL_HPP_
#define LABEL_HPP_

#include <string>

#include "src/basic_widget.hpp"

class Label : public BasicWidget {
 public:
  Label(BasicWidget* parent, int pos_x, int pos_y, const std::wstring& text);
};

#endif  // LABEL_HPP_
