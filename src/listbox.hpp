#ifndef LISTBOX_HPP_
#define LISTBOX_HPP_

#include "src/basic_widget.hpp"

class ListBox : public BasicWidget {
 public:
  ListBox(BasicWidget* parent, int pos_x = CW_USEDEFAULT,
          int pos_y = CW_USEDEFAULT, int width = CW_USEDEFAULT,
          int height = CW_USEDEFAULT)
      : BasicWidget(L"", WS_VISIBLE | WS_TABSTOP, pos_x, pos_y, width, height,
                    parent, L"ListBox", WS_EX_CLIENTEDGE) {}

  void AddLine(const std::wstring& line);
  void InsertLine(int position, const std::wstring& line);
  void RemoveLine(int position);
  void Clear();

  int GetCount();
  int GetSelectedItem();
};

#endif  // LISTBOX_HPP_
