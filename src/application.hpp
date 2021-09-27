#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <windows.h>

class Application {
 public:
  static Application* GetInstance();

  static void Run();

  Application(const Application&) = delete;
  Application(Application&&) = delete;

  ~Application() { g_instance_ = nullptr; }

  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;

  void Init(HINSTANCE instance, int cmd_show);
  HINSTANCE GetHInstance() const;
  int GetCmdShow() const;

 private:
  static constexpr wchar_t kBaseClassName[] = L"Base class";
  static Application* g_instance_;

  Application() = default;

  HINSTANCE instance_;
  int cmd_show_;
};

int main();

#endif  // APPLICATION_HPP_
