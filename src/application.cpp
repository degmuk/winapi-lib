#include "src/application.hpp"

#include "src/widget.hpp"

Application* Application::g_instance_ = nullptr;

Application* Application::GetInstance() {
  if (g_instance_ == nullptr) {
    g_instance_ = new Application();
  }
  return g_instance_;
}

void Application::Init(HINSTANCE instance, int cmd_show) {
  instance_ = instance;
  cmd_show_ = cmd_show;
  BasicWidget::Init(instance);
}

int Application::GetCmdShow() const { return cmd_show_; }

HINSTANCE Application::GetHInstance() const { return instance_; }

void Application::Run() {
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

int WINAPI wWinMain(HINSTANCE hInstance,
                    [[maybe_unused]] HINSTANCE hPrevInstance,
                    [[maybe_unused]] LPWSTR lpCmdLine, int nShowCmd) {
  Application* app = Application::GetInstance();
  app->Init(hInstance, nShowCmd);
  return main();
}
