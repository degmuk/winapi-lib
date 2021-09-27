#ifndef UNICODE
#define UNICODE
#define _UNICODE
#endif

#include <windows.h>

#include "src/application.hpp"
#include "src/widget.hpp"

int main() {
  Widget widget(L"Library demo");
  widget.Show();
  Application::Run();
}
