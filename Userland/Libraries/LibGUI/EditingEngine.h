/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Noncopyable.h>
#include <LibGUI/Event.h>
#include <LibGUI/TextDocument.h>

namespace GUI {

enum CursorWidth {
    NARROW,
    WIDE
};

class EditingEngine {
    AK_MAKE_NONCOPYABLE(EditingEngine);
    AK_MAKE_NONMOVABLE(EditingEngine);

public:
    virtual ~EditingEngine();

    virtual CursorWidth cursor_width() const { return NARROW; }

    void attach(TextEditor& editor);
    void detach();

    virtual bool on_key(const KeyEvent& event);

protected:
    EditingEngine() { }

    WeakPtr<TextEditor> m_editor;

    void move_one_left(const KeyEvent& event);
    void move_one_right(const KeyEvent& event);
    void move_one_up(const KeyEvent& event);
    void move_one_down(const KeyEvent& event);
    void move_to_previous_span(const KeyEvent& event);
    void move_to_next_span(const KeyEvent& event);
    void move_to_line_beginning(const KeyEvent& event);
    void move_to_line_end(const KeyEvent& event);
    void move_page_up(const KeyEvent& event);
    void move_page_down(const KeyEvent& event);
    void move_to_first_line();
    void move_to_last_line();
    TextPosition find_beginning_of_next_word();
    void move_to_beginning_of_next_word();
    TextPosition find_end_of_next_word();
    void move_to_end_of_next_word();
    TextPosition find_end_of_previous_word();
    void move_to_end_of_previous_word();
    TextPosition find_beginning_of_previous_word();
    void move_to_beginning_of_previous_word();

    void move_up(const KeyEvent& event, double page_height_factor);
    void move_down(const KeyEvent& event, double page_height_factor);

    void get_selection_line_boundaries(size_t& first_line, size_t& last_line);

    void delete_line();
    void delete_char();

private:
    void move_selected_lines_up();
    void move_selected_lines_down();
};

}
