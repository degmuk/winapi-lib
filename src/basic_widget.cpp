#include "src/basic_widget.hpp"

#include <array>
#include <cassert>

#include "src/application.hpp"
#include "src/button.hpp"

const std::wstring BasicWidget::kBaseClassName = L"Base class";

WNDCLASS BasicWidget::window_class_;

void BasicWidget::Init(HINSTANCE instance) {
  window_class_ = WNDCLASS{
      .style = CS_HREDRAW | CS_VREDRAW,
      .lpfnWndProc = BasicWidget::WindowProcedure,
      .hInstance = instance,
      .hCursor = LoadCursor(nullptr, IDC_ARROW),
      .hbrBackground = GetSysColorBrush(COLOR_3DFACE),
      .lpszClassName = kBaseClassName.c_str(),
  };
  RegisterClass(&window_class_);
}

bool BasicWidget::operator==(const BasicWidget& rhs) const {
  return handle_ == rhs.handle_;
}

void BasicWidget::Show() { ShowWindow(handle_, SW_SHOW); }

void BasicWidget::Hide() { ShowWindow(handle_, SW_HIDE); }

POINT BasicWidget::GetPosition() const {
  RECT rect;
  GetWindowRect(handle_, &rect);
  POINT res{rect.left, rect.top};
  if (parent_ != nullptr) {
    ScreenToClient(parent_->handle_, &res);
  }
  return res;
}

SIZE BasicWidget::GetSize() const {
  RECT rect;
  GetWindowRect(handle_, &rect);
  return SIZE{rect.right - rect.left, rect.bottom - rect.top};
}

std::wstring BasicWidget::GetTitle() const {
  std::array<wchar_t, 1000> buf{};
  GetWindowText(handle_, buf.data(), buf.size());
  return buf.data();
}

void BasicWidget::SetPosition(const POINT& pos) const {
  SIZE size = GetSize();
  MoveWindow(handle_, pos.x, pos.y, size.cx, size.cy, TRUE);
}

void BasicWidget::SetSize(const SIZE& size) const {
  POINT pos = GetPosition();
  MoveWindow(handle_, pos.x, pos.y, size.cx, size.cy, TRUE);
}

void BasicWidget::SetTitle(std::wstring& title) const {
  SetWindowTextW(handle_, title.c_str());
}

BasicWidget::BasicWidget(const std::wstring& title, LONG style, int pos_x,
                         int pos_y, int width, int height, BasicWidget* parent,
                         const std::wstring& class_name, int ex_style)
    : parent_(parent) {
  auto* app = Application::GetInstance();
  if (parent != nullptr && (style & WS_CHILDWINDOW) == 0) {
    style |= WS_CHILD;
  }
  handle_ = CreateWindowEx(ex_style, class_name.c_str(), title.c_str(), style,
                           pos_x, pos_y, width, height,
                           parent_ != nullptr ? parent_->handle_ : 0, nullptr,
                           app->GetHInstance(), this);
  assert(handle_ != nullptr);
  RegisterHandle();
  if (parent_ != nullptr) {
    parent_->RegisterChild(this);
  }
}

BasicWidget::~BasicWidget() {
  if (parent_ != nullptr) {
    parent_->UnregisterChild(this);
  }
  while (!children.empty()) {
    delete *children.begin();
  }
  DestroyWindow(handle_);
}

BasicWidget::CallbackResult BasicWidget::DestroyEvent() { return std::nullopt; }

BasicWidget::CallbackResult BasicWidget::PaintEvent() { return std::nullopt; }

BasicWidget::CallbackResult BasicWidget::CommandEvent(
    [[maybe_unused]] WPARAM w_param, [[maybe_unused]] LPARAM l_param) {
  switch (HIWORD(w_param)) {
    case BN_CLICKED: {
      HWND button_handle = reinterpret_cast<HWND>(l_param);
      Button* button = dynamic_cast<Button*>(GetThisFromHandle(button_handle));
      assert(button != nullptr);
      assert(children.contains(button));
      button->Clicked();
      return 0;
    }
  }
  return std::nullopt;
}

SIZE BasicWidget::GetTextSize(const std::wstring& text) {
  HDC dc = GetDC(handle_);
  SIZE size;
  GetTextExtentPoint32W(dc, text.c_str(), static_cast<int>(text.size()), &size);
  ReleaseDC(handle_, dc);
  return size;
}

LRESULT BasicWidget::WindowProcedure(HWND hwnd, UINT msg, WPARAM w_param,
                                     LPARAM l_param) {
  BasicWidget* widget = GetThisFromHandle(hwnd);
  if (widget != nullptr) {
    if (auto result = widget->HandleMessage(msg, w_param, l_param);
        result != std::nullopt) {
      return result.value();
    }
  }
  return DefWindowProc(hwnd, msg, w_param, l_param);
}

BasicWidget* BasicWidget::GetThisFromHandle(HWND handle) {
  return reinterpret_cast<BasicWidget*>(
      GetWindowLongPtr(handle, GWLP_USERDATA));
}

void BasicWidget::RegisterHandle() {
  SetWindowLongPtr(handle_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

BasicWidget::CallbackResult BasicWidget::HandleMessage(
    [[maybe_unused]] UINT message, [[maybe_unused]] WPARAM w_param,
    [[maybe_unused]] LPARAM l_param) {
  switch (message) {
    case WM_DESTROY: {
      if (parent_ == nullptr) {
        PostQuitMessage(0);
      }
      return DestroyEvent();
    }
    case WM_PAINT: {
      return PaintEvent();
    }
    case WM_COMMAND: {
      return CommandEvent(w_param, l_param);
    }
  }
  return std::nullopt;
}

void BasicWidget::RegisterChild(BasicWidget* window) {
  children.insert(window);
}

void BasicWidget::UnregisterChild(BasicWidget* widget) {
  auto pos = children.find(widget);
  assert(pos != children.end());
  children.erase(pos);
}
