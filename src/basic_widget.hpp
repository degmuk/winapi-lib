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

  POINT GetPosition() const;
  SIZE GetSize() const;
  std::wstring GetTitle() const;

  void SetPosition(const POINT& pos) const;
  void SetSize(const SIZE& size) const;
  void SetTitle(std::wstring& title) const;

 protected:
  using CallbackResult = std::optional<LRESULT>;

  HWND GetHandle() { return handle_; }

  static const std::wstring kBaseClassName;

  BasicWidget(const std::wstring& title, LONG style, int pos_x = CW_USEDEFAULT,
              int pos_y = CW_USEDEFAULT, int width = CW_USEDEFAULT,
              int height = CW_USEDEFAULT, BasicWidget* parent = nullptr,
              const std::wstring& class_name = kBaseClassName);

  virtual ~BasicWidget();

  virtual CallbackResult DestroyEvent();
  virtual CallbackResult PaintEvent();
  virtual CallbackResult CommandEvent([[maybe_unused]] WPARAM w_param,
                                      [[maybe_unused]] LPARAM l_param);

  SIZE GetTextSize(const std::wstring& text);

 private:
  static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM w_param,
                                 LPARAM l_param);

  static BasicWidget* GetThisFromHandle(HWND handle);

  static WNDCLASS window_class_;

  CallbackResult HandleMessage(UINT message, WPARAM w_param, LPARAM l_param);

  void RegisterHandle();

  void RegisterChild(BasicWidget* window);
  void UnregisterChild(BasicWidget* widget);

  BasicWidget* parent_;
  std::unordered_set<BasicWidget*> children;
  HWND handle_ = 0;
};

#endif  // BASIC_WIDGET_HPP_
