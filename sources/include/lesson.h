#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <vector>

using namespace std;

namespace schedule_api {
    class Lesson {
    public:
        Lesson(): _subject_name{}, _lesson_type{}, _professor{}, _room{}, _additions{} {}

        Lesson(string subject_name, string lesson_type, string professor, string room):
                _subject_name{move(subject_name)}, _lesson_type{move(lesson_type)},
                _professor{move(professor)}, _room{move(room)}, _additions{} {}

        Lesson(Lesson &&lesson) noexcept {
            _subject_name = lesson._subject_name;
            _lesson_type = lesson._lesson_type;
            _professor = lesson._professor;
            _room = lesson._room;
            _additions = move(lesson._additions);
        }

        Lesson &operator=(Lesson &&lesson) noexcept {
            _subject_name = lesson._subject_name;
            _lesson_type = lesson._lesson_type;
            _professor = lesson._professor;
            _room = lesson._room;
            _additions = lesson._additions;

            return *this;
        }

        const string &get_subject_name() const {
            return _subject_name;
        }

        void set_subject_name(const string &subject_name) {
            _subject_name = subject_name;
        }

        const string &get_lesson_type() const {
            return _lesson_type;
        }

        void set_lesson_type(const string &lesson_type) {
            _lesson_type = lesson_type;
        }

        const string &get_professor() const {
            return _professor;
        }

        void set_professor(const string &professor) {
            _professor = professor;
        }

        void add_addition(const string &addition) {
            _additions.push_back(const_cast<string &>(addition));
        }

        const vector<string> &get_additions() const {
            return _additions;
        }

        friend ostream &operator<<(ostream &os, const Lesson &lesson) {
            os << "Lesson: {\n\tsubject: \"" << lesson._subject_name << "\",\n\ttype: \"" << lesson._lesson_type
               << "\",\n\tprofessor: \"" << lesson._professor << "\",\n\troom: \"" << lesson._room << "\",\n\tadditions: [";
            string addition_repr;
            for (int i = 0; i < lesson._additions.size(); i++) {
                addition_repr += "\n\t\t\"" + lesson._additions[i] + (i != lesson._additions.size() - 1 ? "\"," : "\"");
            }
            os << addition_repr << "\n\t]\n}";
            return os;
        }

    private:
        string _subject_name;
        string _lesson_type;
        string _professor;
        string _room;
        vector<string> _additions;
    };
}
