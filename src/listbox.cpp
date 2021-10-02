#include "src/listbox.hpp"

void ListBox::AddLine(const std::wstring& line) {
  SendMessage(GetHandle(), LB_ADDSTRING, 0,
              reinterpret_cast<LPARAM>(line.c_str()));
}

void ListBox::InsertLine(int position, const std::wstring& line) {
  SendMessage(GetHandle(), LB_INSERTSTRING, position,
              reinterpret_cast<LPARAM>(line.c_str()));
}

void ListBox::RemoveLine(int position) {
  SendMessageW(GetHandle(), LB_DELETESTRING, position, 0);
}

void ListBox::Clear() { SendMessageW(GetHandle(), LB_RESETCONTENT, 0, 0); }

int ListBox::GetCount() { return SendMessage(GetHandle(), LB_GETCOUNT, 0, 0); }

int ListBox::GetSelectedItem() {
  int res = SendMessage(GetHandle(), LB_GETCURSEL, 0, 0);
  if (res == LB_ERR) {
    return -1;
  }
  return res;
}
