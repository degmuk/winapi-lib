#ifndef BASIC_WIDGET_HPP_
#define BASIC_WIDGET_HPP_

#include <windows.h>

#include <optional>
#include <string>
#include <unordered_set>

class BasicWidget {
 public:
  static void Init(HINSTANCE instance);

  BasicWidget(const BasicWidget&) = delete;
  BasicWidget(BasicWidget&&) = delete;

  BasicWidget& operator=(const BasicWidget&) = delete;
  BasicWidget& operator=(BasicWidget&&) = delete;

  bool operator==(const BasicWidget& rhs) const;

  void Show();
  void Hide();

 protected:
  using CallbackResult = std::optional<LRESULT>;

  HWND GetHandle() { return handle_; }

  static const std::wstring kBaseClassName;

  BasicWidget(const std::wstring& title, int width = CW_USEDEFAULT,
              int height = CW_USEDEFAULT, BasicWidget* parent = nullptr,
              const std::wstring& class_name = kBaseClassName);

  virtual ~BasicWidget();

  virtual CallbackResult DestroyEvent() { return std::nullopt; }
  virtual CallbackResult PaintEvent() { return std::nullopt; }

 private:
  std::optional<LRESULT> HandleMessage(UINT message, WPARAM w_param,
                                       LPARAM l_param);

  static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM w_param,
                                 LPARAM l_param);
  static WNDCLASS window_class_;

  void RegisterChild(BasicWidget* window);
  void UnregisterChild(BasicWidget* widget);

  BasicWidget* parent_;
  std::unordered_set<BasicWidget*> children;
  HWND handle_ = nullptr;
};

#endif  // BASIC_WIDGET_HPP_
