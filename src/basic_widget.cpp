#include "src/basic_widget.hpp"

#include <cassert>

const std::wstring BasicWidget::kBaseClassName = L"Base class";

WNDCLASS BasicWidget::window_class_;

void BasicWidget::Init(HINSTANCE instance) {
  window_class_ = WNDCLASS{.lpfnWndProc = BasicWidget::WindowProcedure,
                           .hInstance = instance,
                           .lpszClassName = kBaseClassName.c_str()};
  RegisterClass(&window_class_);
}

bool BasicWidget::operator==(const BasicWidget& rhs) const {
  return handle_ == rhs.handle_;
}

void BasicWidget::Show() { ShowWindow(handle_, SW_SHOW); }

void BasicWidget::Hide() { ShowWindow(handle_, SW_HIDE); }

BasicWidget::BasicWidget(const std::wstring& title, int width, int height,
                         BasicWidget* parent, const std::wstring& class_name)
    : parent_(parent) {
  handle_ = CreateWindowEx(
      0, class_name.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
      CW_USEDEFAULT, width, height, parent_ != nullptr ? parent_->handle_ : 0,
      nullptr, window_class_.hInstance, this);
  assert(handle_ != nullptr);
  if (parent_ != nullptr) {
    parent_->RegisterChild(this);
  }
}

std::optional<LRESULT> BasicWidget::HandleMessage(
    [[maybe_unused]] UINT message, [[maybe_unused]] WPARAM w_param,
    [[maybe_unused]] LPARAM l_param) {
  switch (message) {
    case WM_DESTROY: {
      return DestroyEvent();
    }
    case WM_PAINT: {
      return PaintEvent();
    }
  }
  return std::nullopt;
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

LRESULT BasicWidget::WindowProcedure(HWND hwnd, UINT msg, WPARAM w_param,
                                     LPARAM l_param) {
  BasicWidget* widget = nullptr;
  if (msg == WM_CREATE) {
    auto* create_data = reinterpret_cast<CREATESTRUCT*>(l_param);
    widget = static_cast<BasicWidget*>(create_data->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(widget));
  } else {
    widget = reinterpret_cast<BasicWidget*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
  }
  if (widget != nullptr) {
    if (auto result = widget->HandleMessage(msg, w_param, l_param);
        result != std::nullopt) {
      return result.value();
    }
  }
  return DefWindowProc(hwnd, msg, w_param, l_param);
}

void BasicWidget::RegisterChild(BasicWidget* window) {
  children.insert(window);
}

void BasicWidget::UnregisterChild(BasicWidget* widget) {
  auto pos = children.find(widget);
  assert(pos != children.end());
  children.erase(pos);
}
