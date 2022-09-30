#include "test_runner.h"
#include "profile.h"

#include <string>
#include <list>

using namespace std;

class Editor
{
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor();
    void Left();
    void Right();
    void Insert(char token);
    void Cut(size_t tokens = 1);
    void Copy(size_t tokens = 1);
    void Paste();
    string GetText() const;

private:
    list<char> text;
    list<char> buffer;
    list<char>::iterator cursor;
};

Editor::Editor() : cursor(text.end()) {}

void Editor::Left()
{
    if (cursor != text.begin())
    {
        cursor--;
    }
}

void Editor::Right()
{
    if (cursor != text.end())
    {
        cursor++;
    }
}

void Editor::Insert(char token)
{
    text.insert(cursor, token);
}

void Editor::Cut(size_t tokens)
{
    list<char>::iterator temp = cursor;
    for (size_t i = tokens; i > 0; i--)
    {
        temp++;

        if (temp == text.end())
        {
            break;
        }
    }

    buffer.assign(cursor, temp);
    cursor = text.erase(cursor, temp);
}

void Editor::Copy(size_t tokens)
{
    list<char>::iterator temp = cursor;
    for (size_t i = tokens; i > 0; i--)
    {
        temp++;

        if (temp == text.end())
        {
            break;
        }
    }

    buffer.assign(cursor, temp);
}

void Editor::Paste()
{
    text.insert(cursor, buffer.begin(), buffer.end());
}

string Editor::GetText() const
{
    return {text.begin(), text.end()};
}

// --- --- --- --- --- --- --- --- ---

// class Editor {
// public:
//   Editor()
//     : pos(text.end()) {
//   }

//   void Left() {
//     pos = Advance(pos, -1);
//   }

//   void Right() {
//     pos = Advance(pos, 1);
//   }

//   void Insert(char token) {
//     text.insert(pos, token);
//   }

//   void Cut(size_t tokens = 1) {
//     auto pos2 = Advance(pos, tokens);
//     buffer.assign(pos, pos2);
//     pos = text.erase(pos, pos2);
//   }

//   void Copy(size_t tokens = 1) {
//     auto pos2 = Advance(pos, tokens);
//     buffer.assign(pos, pos2);
//   }

//   void Paste() {
//     text.insert(pos, buffer.begin(), buffer.end());
//   }

//   string GetText() const {
//     return {text.begin(), text.end()};
//   }

// private:
//   using Iterator = list<char>::iterator;
//   list<char> text;
//   list<char> buffer;
//   Iterator pos;

//   Iterator Advance(Iterator it, int steps) const {
//     while (steps > 0 && it != text.end()) {
//       ++it;
//       --steps;
//     }
//     while (steps < 0 && it != text.begin()) {
//       --it;
//       ++steps;
//     }
//     return it;
//   }
// };

// --- --- --- --- --- --- --- --- ---

void TypeText(Editor &editor, const string &text)
{
    for (char c : text)
    {
        editor.Insert(c);
    }
}

void TestEditing()
{
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i)
        {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i)
        {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse()
{
    Editor editor;

    const string text = "esreveR";
    for (char c : text)
    {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText()
{
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer()
{
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}