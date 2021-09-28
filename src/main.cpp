#include "src/application.hpp"
#include "src/widget.hpp"

int main() {
  Widget widget(L"Library demo");
  widget.Show();
  Application::Run();
}
