#include "src/multiline_edit.hpp"

MultiLineEdit::MultiLineEdit(BasicWidget* parent, int pos_x, int pos_y,
                             int width, int height)
    : Edit(parent, pos_x, pos_y, width, height,
           ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE) {}
